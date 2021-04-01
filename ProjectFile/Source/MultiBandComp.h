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
    
    void prepare (const juce::dsp::ProcessSpec& spec);
    
    void prepareMBC(juce::AudioBuffer<float> &buffer, int c);

    void processBlock(juce::AudioBuffer<float> &buffer, float Fs); // process Audio Block
    
    void splitBlock(juce::AudioBuffer<float> &buffer, float Fs, int c); // split block into the specific bands
    void processBand(juce::AudioBuffer<float> &buffer); // process band based on respective compressor parameters
    void rebuildBlock(juce::AudioBuffer<float> &buffer, int c); // combine together processed bands
    void setBQParameters(double newFs, double newLMFreq, double newMHFreq, Biquad::FilterType filterTypeParam); // set the filters parameters of the particular band
    
    float getMeterVal(juce::AudioBuffer<float> &buffer, int c, int n, const int N); // go through block by sample to obtain meter values
   
    
    float threshLow = 6.f;
    float ratioLow = 1.f; // Q
    float attackLow = 1.f;
    float releaseLow = 1.f;
    
    // Mid knobs
    float threshMid = 6.f;
    float ratioMid = 1.f; // Q
    float attackMid = 1.f;
    float releaseMid = 1.f;
    
    // Hi knobs
    float threshHi = 6.f;
    float ratioHi = 1.f; // Q
    float attackHi = 1.f;
    float releaseHi = 1.f;
    
    // Overall knobs
    float signalGain = -10.0f;
    float lowMidF; // freq dividing low's and mid's
    float midHiF; // freq dividing mid's and high's
    
    float lowMeterVal;
    float midMeterVal;
    float hiMeterVal;
    float gainMeterVal;
    
private:
    
    float meterVal;
    
    VUAnalysis vuAnalysis;

    dsp::Compressor<float> lowC;
    dsp::Compressor<float> midC;
    dsp::Compressor<float> hiC;
    
    Biquad BQLow; float bqFLow;
    Biquad BQMid; float bqFMid;
    Biquad BQHi; float bqFHi;
    
    int bufferLength;
    
    juce::AudioBuffer<float> lowBuffer;
    juce::AudioBuffer<float> midBuffer;
    juce::AudioBuffer<float> hiBuffer;
    juce::AudioBuffer<float> finalBuffer;

};
