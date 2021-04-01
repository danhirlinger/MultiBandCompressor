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
};

void MultiBandComp::prepareMBC(juce::AudioBuffer<float> &buffer, int c){
    bufferLength = buffer.getNumSamples();
    lowBuffer.setSize(c, bufferLength);
    midBuffer.setSize(c, bufferLength);
    hiBuffer.setSize(c, bufferLength);
}

void MultiBandComp::processBlock(juce::AudioBuffer<float> &buffer, float Fs){
    int c = buffer.getNumChannels();
    
    // run splitBlock() to get individual buffers of L,M,H
    splitBlock(buffer,Fs,c);

    // process each band based on compression values
//    processBand(lowBuffer, threshLow, ratioLow, attackLow, releaseLow);
//    processBand(midBuffer, threshMid, ratioMid, attackMid, releaseMid);
//    processBand(hiBuffer, threshHi, ratioHi, attackHi, releaseHi);
    processBand(buffer);
    
    // getMeterVals() for each band
//    lowMeterVal = getMeterVals(lowBuffer, c, bufferLength);
//    midMeterVal = getMeterVals(midBuffer, c, bufferLength);
//    hiMeterVal = getMeterVals(hiBuffer, c, bufferLength);
    
    rebuildBlock(c);

    buffer.copyFrom(c-c, 0, finalBuffer, c-c, 0, buffer.getNumSamples());
    
    buffer.applyGain(0, buffer.getNumSamples(), signalGain);

    
    
    // getMeterVals(); for final processed signal
//    gainMeterVal = getMeterVals(finalBuffer, c, bufferLength);
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
    BQ.processBlock(lowBuffer);
    
    setBQParameters(Fs, lowMidF, midHiF, Biquad::BPF1);
    BQ.processBlock(midBuffer);
    BQ.processBlock(midBuffer);
    
    setBQParameters(Fs, lowMidF, midHiF, Biquad::HPF);
    BQ.processBlock(hiBuffer);
    BQ.processBlock(hiBuffer);
}

void MultiBandComp::processBand(juce::AudioBuffer<float> &buffer){
    
    // process bands based on respective compressor parameters
    // dsp::Compressor
    lowC.setRatio(ratioLow);
    lowC.setAttack(attackLow);
    lowC.setRelease(releaseLow);
    lowC.setThreshold(threshLow);
    
    midC.setRatio(ratioMid);
    midC.setAttack(attackMid);
    midC.setRelease(releaseMid);
    midC.setThreshold(threshMid);
    
    hiC.setRatio(ratioHi);
    hiC.setAttack(attackHi);
    hiC.setRelease(releaseHi);
    hiC.setThreshold(threshHi);

    
    int c = buffer.getNumChannels();
    
//    for (int channel = 0; channel < c; channel++) {
////        for (int n = 0; n < bufferLength; n++) {
//            float x = buffer.getSample(channel, n);
//            COMP.processSample(channel, x);
//            // having error with JUCE DSP.....
//        }
        
//        dsp::AudioBlock<float> block (buffer);
//        COMP.process(dsp::ProcessContextReplacing<float>(block));
//        block.copyTo(buffer);
        dsp::AudioBlock<float> lowBlock (lowBuffer);
        lowC.process(dsp::ProcessContextReplacing<float> (lowBlock));
        lowBlock.copyTo(lowBuffer);
        
        dsp::AudioBlock<float> midBlock (midBuffer);
        midC.process(dsp::ProcessContextReplacing<float> (midBlock));
        midBlock.copyTo(midBuffer);
        
        dsp::AudioBlock<float> hiBlock (hiBuffer);
        hiC.process(dsp::ProcessContextReplacing<float> (hiBlock));
        hiBlock.copyTo(hiBuffer);
//    }
}

void MultiBandComp::rebuildBlock(int c){

    int newDestPosition = finalBuffer.getNumSamples();
    int newBufferSize = finalBuffer.getNumSamples() + lowBuffer.getNumSamples();
    finalBuffer.setSize(lowBuffer.getNumChannels(), newBufferSize);
    
    // combine together processed bands into an audioBlock
    for (int channel = 0; channel < c; channel++) {
        lowBuffer.addFrom(channel, 0, midBuffer, channel, 0, bufferLength);
        lowBuffer.addFrom(channel, 0, hiBuffer, channel, 0, bufferLength);
        finalBuffer.copyFrom(channel, 0, lowBuffer, channel, 0, lowBuffer.getNumSamples());
    }
}

float MultiBandComp::getMeterVals(juce::AudioBuffer<float> &buffer, int c, int n, const int N){
    
//    for (int channel = 0; channel < c; channel++){
//        for (int n = 0; n < N; n++){
            float x = buffer.getReadPointer(c)[n];
            meterVals = vuAnalysis.processSample(x,c);
//        }
//    }
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
