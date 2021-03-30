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
    
    void processBand(juce::AudioBuffer<float> &buffer, int c, float t, float ratio, float a, float rel); // process band based on respective compressor parameters
    void rebuildBlock(int c); // combine together processed bands
    
    void getMeterVals(juce::AudioBuffer<float> &buffer, int c, const int N); // go through block by sample to obtain meter values
    
    void setBQParameters(double newFs, double newLMFreq, double newMHFreq, Biquad::FilterType filterTypeParam); // set the filters parameters of the particular band
    void setCParameters(float newT, float newRatio, float newA, float newRel);
    
    float threshLow = 1.f;
    float ratioLow = 1.f; // Q
//    float kneeLow;
    float attackLow = 1.f;
    float releaseLow = 1.f;
    
    // Mid knobs
    float threshMid = 1.f;
    float ratioMid = 1.f; // Q
//    float kneeMid;
    float attackMid = 1.f;
    float releaseMid = 1.f;
    
    // Hi knobs
    float threshHi = 1.f;
    float ratioHi = 1.f; // Q
//    float kneeHi;
    float attackHi = 1.f;
    float releaseHi = 1.f;
    
    float lowMidF; // freq dividing low's and mid's
    float midHiF; // freq dividing mid's and high's
    
private:
    
    float meterVals;
    
    VUAnalysis vuAnalysis;
    
    dsp::Compressor<float> COMP;
    
    Biquad BQ;
    float Q = 0.707;

    float biquadFreq; // value dependent upon filter type
    
    // Low knobs
    
    
    // Overall knobs
    float signalGain;

    int bufferLength;
    
    juce::AudioBuffer<float> lowBuffer;
    juce::AudioBuffer<float> midBuffer;
    juce::AudioBuffer<float> hiBuffer;
    juce::AudioBuffer<float> finalBuffer;

};
