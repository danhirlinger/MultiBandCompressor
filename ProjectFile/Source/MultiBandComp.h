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
    
    void prepareMBC(juce::AudioBuffer<float> &buffer, int c);

    void processBlock(juce::AudioBuffer<float> &buffer, float Fs); // process Audio Block
    
    void splitBlock(juce::AudioBuffer<float> &buffer, float Fs, int c); // split block into the specific bands
    
    void processBand(juce::AudioBuffer<float> &buffer, float t, float ratio, float a, float rel); // process band based on respective compressor parameters
    void rebuildBlock(); // combine together processed bands
    
    float getMeterVals(juce::AudioBuffer<float> &buffer, int c, int n, const int N); // go through block by sample to obtain meter values
    
    void setBQParameters(double newFs, double newLMFreq, double newMHFreq, Biquad::FilterType filterTypeParam); // set the filters parameters of the particular band
    void setCParameters(float newT, float newRatio, float newA, float newRel);
    
    
private:
    
    float meterVals;
    
    VUAnalysis vuAnalysis;
    
    dsp::Compressor<float> COMP;
    
    Biquad BQ;
    float Q = 0.707;
    float lowMidF; // freq dividing low's and mid's
    float midHiF; // freq dividing mid's and high's
    float biquadFreq; // value dependent upon filter type
    
    // Low knobs
    float threshLow;
    float ratioLow; // Q
    float kneeLow;
    float attackLow;
    float releaseLow;
    
    // Mid knobs
    float threshMid;
    float ratioMid; // Q
    float kneeMid;
    float attackMid;
    float releaseMid;
    
    // Hi knobs
    float threshHi;
    float ratioHi; // Q
    float kneeHi;
    float attackHi;
    float releaseHi;
    
    // Overall knobs
    float signalGain;

    int bufferLength;
    
    juce::AudioBuffer<float> lowBuffer;
    juce::AudioBuffer<float> midBuffer;
    juce::AudioBuffer<float> hiBuffer;
    
    

};
