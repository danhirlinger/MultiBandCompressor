/*
  ==============================================================================

    MultiBand.cpp
    Created: 16 Feb 2021 9:28:14am
    Author:  Dan Hirlinger

  ==============================================================================
*/

#include "MultiBandComp.h"

MultiBandComp::MultiBandComp(){
}

void MultiBandComp::prepare (const juce::dsp::ProcessSpec& spec){
    reset();
    
    mbcSpec = spec;

    // prepare compressors
    lowC.prepare(mbcSpec);
    midC.prepare(mbcSpec);
    hiC.prepare(mbcSpec);
    
    // prepare all buffers
    initialBuffer.setSize(mbcSpec.numChannels, mbcSpec.maximumBlockSize);
    lowBuffer.setSize(mbcSpec.numChannels,mbcSpec.maximumBlockSize);
    midBuffer.setSize(mbcSpec.numChannels,mbcSpec.maximumBlockSize);
    hiBuffer.setSize(mbcSpec.numChannels, mbcSpec.maximumBlockSize);
    finalBuffer.setSize(mbcSpec.numChannels,mbcSpec.maximumBlockSize);
    
    // prepare biquad filters
    BQLow.setFilterType(Biquad::LPF);
    BQLow1.setFilterType(Biquad::LPF);
    BQMid.setFilterType(Biquad::BPF1);
    BQMid1.setFilterType(Biquad::BPF1);
    BQHi.setFilterType(Biquad::HPF);
    BQHi1.setFilterType(Biquad::HPF);
    
    // prepare dry/wet mixer
    DryWet.prepare(mbcSpec);
    DryWet.setMixingRule(juce::dsp::DryWetMixingRule::balanced);
    DryWet.setWetLatency(3);
};

void MultiBandComp::processBlock(juce::AudioBuffer<float> &buffer, float Fs){
    clearBuffers();
    prepareBuffers(buffer);
    int c = buffer.getNumChannels();
    DryWet.pushDrySamples(buffer);
    bufferLength = buffer.getNumSamples();
    
    for (int n = 0; n < c; n++){
        initialBuffer.copyFrom(n,0,buffer,n,0,bufferLength);
    }
    
    splitBlock(initialBuffer,Fs,c);
    processBand(c);
    rebuildBlock(initialBuffer, c);
    finalBlock(finalBuffer,c);

    for (int n = 0; n < c; n++){
        buffer.copyFrom(n, 0, finalBuffer, n, 0, bufferLength);
    }
};

void MultiBandComp::splitBlock(juce::AudioBuffer<float> &buffer, float Fs, int c){
// duplicate original buffer into buffer bands
    for (int n = 0; n < c; n++){
        lowBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
        midBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
        hiBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
    }

// filter each buffer
    setBQParameters(Fs, lowMidF, midHiF);
    
    BQLow.processBlock(lowBuffer);
    BQLow1.processBlock(lowBuffer);
    
    BQMid.processBlock(midBuffer);
    BQMid1.processBlock(midBuffer);
    
    BQHi.processBlock(hiBuffer);
    BQHi1.processBlock(hiBuffer);
}

void MultiBandComp::processBand(int c){
    
// set compressor values for each band's compressor
    lowC.setRatio(raLow);
    lowC.setAttack(aLow);
    lowC.setRelease(reLow);
    lowC.setThreshold(tLow);
    
    midC.setRatio(raMid);
    midC.setAttack(aMid);
    midC.setRelease(reMid);
    midC.setThreshold(tMid);
    
    hiC.setRatio(raHi);
    hiC.setAttack(aHi);
    hiC.setRelease(reHi);
    hiC.setThreshold(tHi);

// process the compression for each band
    dsp::AudioBlock<float> lowBlock (lowBuffer);
    lowC.process(dsp::ProcessContextReplacing<float> (lowBlock));
    lowBlock.copyTo(lowBuffer);
    
    dsp::AudioBlock<float> midBlock (midBuffer);
    midC.process(dsp::ProcessContextReplacing<float> (midBlock));
    midBlock.copyTo(midBuffer);
    
    dsp::AudioBlock<float> hiBlock (hiBuffer);
    hiC.process(dsp::ProcessContextReplacing<float> (hiBlock));
    hiBlock.copyTo(hiBuffer);
};

void MultiBandComp::rebuildBlock(juce::AudioBuffer<float> &buffer, int c){
    // combine together processed bands into one audioBlock
    for (int channel = 0; channel < c; channel++) {
        finalBuffer.copyFrom(channel, 0, lowBuffer, channel, 0, bufferLength);
        finalBuffer.addFrom(channel, 0, midBuffer, channel, 0, bufferLength);
        finalBuffer.addFrom(channel, 0, hiBuffer, channel, 0, bufferLength);
    }
};

void MultiBandComp::finalBlock(juce::AudioBuffer<float> &buffer, int c){
    // take finalBuffer value and copy into the inputted buffer
    dsp::AudioBlock<float> finalBlock (buffer);
    float gain_linear = pow(10.f, gain/20.f); // convert from dB to linear
    finalBlock.multiplyBy(gain_linear);
    DryWet.mixWetSamples(finalBlock);
    finalBlock.copyTo(finalBuffer);
    
    DryWet.setWetMixProportion(dryWet);
};

void MultiBandComp::setBQParameters(double newFs, int newLMFreq, int newMHFreq){
    // set parameters of the biquad filters
        bqFLow = newLMFreq;
        BQLow.setFs(newFs);
        BQLow1.setFs(newFs);
        BQLow.setFreq(bqFLow);
        BQLow1.setFreq(bqFLow);

        bqFHi = newMHFreq;
        BQHi.setFs(newFs);
        BQHi1.setFs(newFs);
        BQHi.setFreq(bqFHi);
        BQHi1.setFreq(bqFHi);

        // need to establish a "center" frequency for BPF
        bqFMid = (((float)newLMFreq + (float)newMHFreq) / 2.f);
        BQMid.setFs(newFs);
        BQMid1.setFs(newFs);
        BQMid.setFreq(bqFMid);
        BQMid1.setFreq(bqFMid);

};

float MultiBandComp::getMeterVal(juce::AudioBuffer<float> &buffer, int c, int n){
    
// get meter value for specific channel, sample
// function called in PluginProcessor.cpp
    float x = buffer.getReadPointer(c)[n];
    meterVal = vuAnalysis.processSample(x,c);
    return meterVal;
};


void MultiBandComp::reset(){
    lowC.reset();
    midC.reset();
    hiC.reset();
    DryWet.reset();
    
    clearBuffers();
}

void MultiBandComp::clearBuffers(){
    lowBuffer.clear();
    midBuffer.clear();
    hiBuffer.clear();
    initialBuffer.clear();
    finalBuffer.clear();
}

void MultiBandComp::prepareBuffers(AudioBuffer<float> &buffer){
    int size = buffer.getNumSamples();
    initialBuffer.setSize(mbcSpec.numChannels, size);
    lowBuffer.setSize(mbcSpec.numChannels,size);
    midBuffer.setSize(mbcSpec.numChannels,size);
    hiBuffer.setSize(mbcSpec.numChannels, size);
    finalBuffer.setSize(mbcSpec.numChannels,size);
}
