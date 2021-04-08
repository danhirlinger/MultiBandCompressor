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
    lowC.prepare(spec);
    midC.prepare(spec);
    hiC.prepare(spec);
    lowBuffer.setSize(spec.numChannels,spec.maximumBlockSize);
    midBuffer.setSize(spec.numChannels,spec.maximumBlockSize);
    hiBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
    finalBuffer.setSize(spec.numChannels,spec.maximumBlockSize);
    
};

void MultiBandComp::processBlock(juce::AudioBuffer<float> &buffer, float Fs){
    int c = buffer.getNumChannels();
    
    splitBlock(buffer,Fs,c);
    
    processBand(c);
    
    rebuildBlock(buffer, c);
    
    // take finalBuffer value and copy into the inputted buffer
    dsp::AudioBlock<float> finalBlock (finalBuffer);
    float gain_linear = pow(10.f, *gain/20.f); // convert from dB to linear
    finalBlock.multiplyBy(gain_linear);
    finalBlock.copyTo(buffer);
};

void MultiBandComp::splitBlock(juce::AudioBuffer<float> &buffer, float Fs, int c){
    
// duplicate original buffer into buffer bands
    for (int n = 0; n < c; n++){
        lowBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
        midBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
        hiBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
    }

// filter each buffer based on the interface parameters
    setBQParameters(Fs, lowMidF, midHiF);
    BQLow.processBlock(lowBuffer);
    BQLow1.processBlock(lowBuffer);
    // THIS IS WHERE THE ISSUE LIES.... i can't daisy-chain for some reason...
    // maybe the two instances will work??
    
    setBQParameters(Fs, lowMidF, midHiF);
    BQMid.processBlock(midBuffer);
    BQMid1.processBlock(midBuffer);
    
    setBQParameters(Fs, lowMidF, midHiF);
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

    // combine together processed bands into an audioBlock
    for (int channel = 0; channel < c; channel++) {
        finalBuffer.copyFrom(channel, 0, lowBuffer, channel, 0, bufferLength);
        finalBuffer.addFrom(channel, 0, midBuffer, channel, 0, bufferLength);
        finalBuffer.addFrom(channel, 0, hiBuffer, channel, 0, bufferLength);
    }
};

void MultiBandComp::setBQParameters(double newFs, double newLMFreq, double newMHFreq){
    // filter the incoming buffer based on the other input parameters
    
        bqFLow = newLMFreq;
        BQLow.setFs(newFs);
        BQLow1.setFs(newFs);
        BQLow.setFreq(bqFLow);
        BQLow1.setFreq(bqFLow);
        BQLow.setFilterType(Biquad::LPF);
        BQLow1.setFilterType(Biquad::LPF);

        bqFHi = newMHFreq;
        BQHi.setFs(newFs);
        BQHi1.setFs(newFs);
        BQHi.setFreq(bqFHi);
        BQHi1.setFreq(bqFHi);
        BQHi.setFilterType(Biquad::BPF1);
        BQHi1.setFilterType(Biquad::BPF1);

        // need to establish a "center" frequency for BPF
        bqFMid = ((newLMFreq + newMHFreq) / 2.f);
        BQMid.setFs(newFs);
        BQMid1.setFs(newFs);
        BQMid.setFreq(bqFMid);
        BQMid1.setFreq(bqFMid);
        BQMid.setFilterType(Biquad::HPF);
        BQMid1.setFilterType(Biquad::HPF);
};

float MultiBandComp::getMeterVal(juce::AudioBuffer<float> &buffer, int c, int n){
    
// get meter value for specific channel, sample
// function called in PluginProcessor.cpp
    float x = buffer.getReadPointer(c)[n];
    meterVal = vuAnalysis.processSample(x,c);
    return meterVal;
};

