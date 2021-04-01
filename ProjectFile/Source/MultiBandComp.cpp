/*
  ==============================================================================

    MultiBand.cpp
    Created: 16 Feb 2021 9:28:14am
    Author:  Dan Hirlinger

  ==============================================================================
*/

#include "MultiBandComp.h"

MultiBandComp::MultiBandComp(){
};

void MultiBandComp::prepare (const juce::dsp::ProcessSpec& spec){
    lowC.prepare(spec);
    midC.prepare(spec);
    hiC.prepare(spec);
};

void MultiBandComp::prepareMBC(juce::AudioBuffer<float> &buffer, int c){
    bufferLength = buffer.getNumSamples();
    lowBuffer.setSize(c, bufferLength);
    midBuffer.setSize(c, bufferLength);
    hiBuffer.setSize(c, bufferLength);
};

void MultiBandComp::processBlock(juce::AudioBuffer<float> &buffer, float Fs){
    int c = buffer.getNumChannels();
    
    splitBlock(buffer,Fs,c);
    
    processBand(c);
    
    rebuildBlock(buffer, c);
    
    // take finalBuffer value and copy into the inputted buffer
    dsp::AudioBlock<float> finalBlock (finalBuffer);
    finalBlock.multiplyBy(gain);
    finalBlock.copyTo(buffer);
    
//    for (int channel = 0; channel < c; ++channel){
//        for (int n = 0; n < buffer.getNumSamples(); n++){
//            lowMeterVal = getMeterVal(lowBuffer, channel, n, bufferLength);
//            midMeterVal = getMeterVal(midBuffer, channel, n, b ufferLength);
//            hiMeterVal  = getMeterVal(hiBuffer, channel, n, bufferLength);
//            gainMeterVal = getMeterVal(buffer, channel, n, bufferLength);
//        }
//    }
};

void MultiBandComp::splitBlock(juce::AudioBuffer<float> &buffer, float Fs, int c){
    
// duplicate original buffer into buffer bands
    for (int n = 0; n < c; n++){
        lowBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
        midBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
        hiBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
    }

// filter each buffer based on the interface parameters
    setBQParameters(Fs, lowMidF, midHiF, Biquad::LPF);
    BQLow.processBlock(lowBuffer);
    BQLow.processBlock(lowBuffer);
    
    setBQParameters(Fs, lowMidF, midHiF, Biquad::BPF1);
    BQMid.processBlock(midBuffer);
    BQMid.processBlock(midBuffer);
    
    setBQParameters(Fs, lowMidF, midHiF, Biquad::HPF);
    BQHi.processBlock(hiBuffer);
    BQHi.processBlock(hiBuffer);
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

//    int newDestPosition = finalBuffer.getNumSamples();
    int newBufferSize = finalBuffer.getNumSamples() + lowBuffer.getNumSamples();
    finalBuffer.setSize(lowBuffer.getNumChannels(), newBufferSize);
    
    // combine together processed bands into an audioBlock
    for (int channel = 0; channel < c; channel++) {
//        lowBuffer.addFrom(channel, 0, midBuffer, channel, 0, bufferLength);
//        lowBuffer.addFrom(channel, 0, hiBuffer, channel, 0, bufferLength);
//        finalBuffer.copyFrom(channel, 0, lowBuffer, channel, 0, lowBuffer.getNumSamples());
        finalBuffer.copyFrom(channel, 0, lowBuffer, channel, 0, bufferLength);
        finalBuffer.addFrom(channel, 0, midBuffer, channel, 0, bufferLength);
        finalBuffer.addFrom(channel, 0, hiBuffer, channel, 0, bufferLength);
    }
//    // take finalBuffer value and copy into the inputted buffer
//    dsp::AudioBlock<float> finalBlock (finalBuffer);
//    finalBlock.copyTo(buffer);
//    buffer.applyGain(0, buffer.getNumSamples(), signalGain);
};

void MultiBandComp::setBQParameters(double newFs, double newLMFreq, double newMHFreq, Biquad::FilterType filterTypeParam){
    // filter the incoming buffer based on the other input parameters
    
    if (filterTypeParam == Biquad::LPF){
        bqFLow = newLMFreq;
        BQLow.setFs(newFs);
        BQLow.setFreq(bqFLow);
        BQLow.setFilterType(filterTypeParam);
    } else if (filterTypeParam == Biquad::HPF){
        bqFHi = newMHFreq;
        BQHi.setFs(newFs);
        BQHi.setFreq(bqFHi);
        BQHi.setFilterType(filterTypeParam);
    } else if (filterTypeParam == Biquad::BPF1){
        // need to establish a "center" frequency for BPF
        bqFMid = ((newLMFreq + newMHFreq) / 2.f);
        BQMid.setFs(newFs);
        BQMid.setFreq(bqFMid);
        BQMid.setFilterType(filterTypeParam);
    }
};

float MultiBandComp::getMeterVal(juce::AudioBuffer<float> &buffer, int c, int n){
    
// get meter value for specific channel, sample
// function called in PluginProcessor.cpp
    float x = buffer.getReadPointer(c)[n];
    meterVal = vuAnalysis.processSample(x,c);
    return meterVal;
};


