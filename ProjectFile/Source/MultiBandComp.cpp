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

void MultiBandComp::prepareMBC(juce::AudioBuffer<float> &buffer, int c){
    bufferLength = buffer.getNumSamples();
    lowBuffer.setSize(c, bufferLength);
    midBuffer.setSize(c, bufferLength);
    hiBuffer.setSize(c, bufferLength);

}
void MultiBandComp::processBlock(juce::AudioBuffer<float> &buffer, float Fs){
    // pass in buffer
    int c = buffer.getNumChannels();
    // run splitBlock() to get individual buffers of L,M,H
    splitBlock(buffer,Fs,c);

    // processBand() L
    // processBand() M
    // processBand() H
    
    processBand(lowBuffer, c, threshLow, ratioLow, attackLow, releaseLow);
    processBand(midBuffer, c, threshMid, ratioMid, attackMid, releaseMid);
    processBand(hiBuffer, c, threshHi, ratioHi, attackHi, releaseHi);
    
    // getMeterVals(); for each band
    getMeterVals(lowBuffer, c, bufferLength);
    getMeterVals(midBuffer, c, bufferLength);
    getMeterVals(hiBuffer, c, bufferLength);
    
    // rebuildBlock();
    
    // getMeterVals(); for final processed signal
}

void MultiBandComp::splitBlock(juce::AudioBuffer<float> &buffer, float Fs, int c){
    
    // take buffer and split based on input parameters
    // use functions from Biquad

    for (int n = 0; n < c; n++){
        lowBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
        midBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
        hiBuffer.copyFrom(n, 0, buffer, n, 0, bufferLength);
    }
    
    setBQParameters(Fs, lowMidF, midHiF, Biquad::LPF);
    BQ.processBlock(lowBuffer);
    
    setBQParameters(Fs, lowMidF, midHiF, Biquad::BPF1);
    BQ.processBlock(midBuffer);
    
    setBQParameters(Fs, lowMidF, midHiF, Biquad::HPF);
    BQ.processBlock(hiBuffer);
}

void MultiBandComp::processBand(juce::AudioBuffer<float> &buffer, int c, float t, float ratio, float a, float rel){
    
    // process band based on respective compressor parameters
    // dsp::Compressor
    
    COMP.setRatio(ratio);
    COMP.setAttack(a);
    COMP.setRelease(rel);
    COMP.setThreshold(t);
    
    for (int channel = 0; channel < c; channel++) {
        for (int n = 0; n < bufferLength; n++) {
            COMP.processSample(channel, buffer.getSample(channel, n));
            // having error with JUCE DSP.....
        }
    }
}

void MultiBandComp::rebuildBlock(int c){

    // combine together processed bands into an audioBlock
    
    // add together by sample?
    for (int channel = 0; channel < c; channel++) {
        lowBuffer.addFrom(channel, 0, midBuffer, channel, 0, bufferLength);
        lowBuffer.addFrom(channel, 0, hiBuffer, channel, 0, bufferLength);
        finalBuffer.copyFrom(channel, 0, lowBuffer, channel, 0, bufferLength);
    }
    
    
    
    // buffer.addFrom() to merge buffers together
    // then buffer.copyFrom(), using processed buffer as source buffer
}

float MultiBandComp::getMeterVals(juce::AudioBuffer<float> &buffer, int c, const int N){
    
    for (int n = 0; n < N; n++){
        float x = buffer.getReadPointer(c)[n];
        meterVals = vuAnalysis.processSample(x,c);
    }
    return meterVals;
}

void MultiBandComp::setBQParameters(double newFs, double newLMFreq, double newMHFreq, Biquad::FilterType filterTypeParam){
    BQ.setFs(newFs);
    if (filterTypeParam == Biquad::LPF){
        biquadFreq = newLMFreq;
        BQ.setFreq(biquadFreq);
        BQ.setFilterType(filterTypeParam);
    } else if (filterTypeParam == Biquad::HPF){
        biquadFreq = newMHFreq;
        BQ.setFreq(biquadFreq);
        BQ.setFilterType(filterTypeParam);
    } else if (filterTypeParam == Biquad::BPF1){
        // need to establish a "center" frequency for BPF
        biquadFreq = (newLMFreq + newMHFreq) / 2.f;
        BQ.setFreq(biquadFreq);
        BQ.setFilterType(filterTypeParam);
    }
    

}

void setCParameters(float newT, float newRatio, float newA, float newRel){
    
    // do i need this?? i don't think so...
    // or just put the variables through processBand()....
    // using dsp::compressor to set the values...
    
}
