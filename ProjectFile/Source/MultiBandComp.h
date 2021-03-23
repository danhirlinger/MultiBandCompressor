/*
  ==============================================================================

    MultiBand.h
    Created: 16 Feb 2021 9:28:14am
    Author:  Dan Hirlinger

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "VUAnalysis.h"
#include "Biquad.h"


class MultiBandComp{
    
public:
    MultiBandComp();
    void processBlock(juce::AudioBuffer<float> &buffer); // process Audio Block
    
    void splitBlock(); // split block into a specific band; include input of LPF,HPF,BPF??
    
    void processBand(); // process band based on respective compressor parameters
    
    float getMeterVals(juce::AudioBuffer<float> &buffer, int c, int n, const int N); // go through block by sample to obtain meter values
    
    void rebuildBlock(); // combine together processed bands
    
private:
    
    float meterVals;
    
    VUAnalysis vuAnalysis;
    
    dsp::Compressor<float> COMP;
};
