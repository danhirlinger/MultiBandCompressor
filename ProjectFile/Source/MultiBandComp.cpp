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


void MultiBandComp::processBlock(juce::AudioBuffer<float> buffer, float Fs){
    // pass in buffer
    
    // run splitBlock() to get individual buffers of L,M,H
    
    
    // processBand() L
    // processBand() M
    // processBand() H
    
    // getMeterVals(); for each band
    
    // rebuildBlock();
    
    // getMeterVals(); for final processed signal
    
}

void MultiBandComp::splitBlock(juce::AudioBuffer<float> buffer, float Fs){
    
    // take buffer and split based on input parameters
    // use functions from Biquad
    
    
    setParameters(Fs, lowMidF, midHiF, Biquad::LPF);
    
    BQ.processBlock(buffer);
    // need this to write into a variable, not just process ???????
    setParameters(Fs, lowMidF, midHiF, Biquad::BPF1);
    // processBlock()
    setParameters(Fs, lowMidF, midHiF, Biquad::HPF);
    // processBlock()
    
}

void MultiBandComp::processBand(float t, float ratio, float a, float rel){
    
    // process band based on respective compressor parameters
    // dsp::Compressor
}

void MultiBandComp::rebuildBlock(){

    // combine together processed bands into an audioBlock
}

float MultiBandComp::getMeterVals(juce::AudioBuffer<float> buffer, int c, int n, const int N){
    
//    for (int n = 0; n < N; n++){
        float x = buffer.getReadPointer(c)[n];
        meterVals = vuAnalysis.processSample(x,c);
        return meterVals;
//    }
    
    
}

void MultiBandComp::setParameters(double newFs, double newLMFreq, double newMHFreq, Biquad::FilterType filterTypeParam){
    BQ.setFs(newFs);
    if (filterTypeParam == Biquad::LPF){
        biquadFreq = newLMFreq;
        BQ.setFilterType(filterTypeParam);
    } else if (filterTypeParam == Biquad::HPF){
        biquadFreq = newMHFreq;
        BQ.setFilterType(filterTypeParam);
    } else if (filterTypeParam == Biquad::BPF1){
        // need to establish a "center" frequency for BPF
        biquadFreq = (newLMFreq + newMHFreq) / 2.f;
        BQ.setFilterType(filterTypeParam);
    }
}
