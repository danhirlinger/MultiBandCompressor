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

    void processBlock(juce::AudioBuffer<float> &buffer, float Fs); // process Audio Block
    
    void splitBlock(juce::AudioBuffer<float> &buffer, float Fs, int c); // split block into the specific bands
    void processBand(int c); // process band based on respective compressor parameters
    void rebuildBlock(juce::AudioBuffer<float> &buffer, int c); // combine together processed bands
    void finalBlock(juce::AudioBuffer<float> &buffer, int c);
    void setBQParameters(double newFs, int newLMFreq, int newMHFreq); // set the filters parameters of the particular band
    
    float getMeterVal(juce::AudioBuffer<float> &buffer, int c, int n); // go through block by sample to obtain meter values
    
    // Low knobs
    float tLow = 0.f;
    float raLow = 1.f;
    float aLow = 1.f;
    float reLow = 1.f;
    // Mid knobs
    float tMid = 0.f;
    float raMid = 1.f;
    float aMid = 1.f;
    float reMid = 1.f;
    // Hi knobs
    float tHi = 0.f;
    float raHi = 1.f;
    float aHi = 1.f;
    float reHi = 1.f;
    
    // Overall knobs
    float gain = 0.f; // gain in dB; max +12db/1; min -12dB/-1
    int lowMidF = 500; // freq dividing low's and mid's
    int midHiF = 2000; // freq dividing mid's and high's
    double dryWet = 0.5f; // 0 = dry, 1 = wet
    
    AudioBuffer<float> initialBuffer;
    AudioBuffer<float> lowBuffer;
    AudioBuffer<float> midBuffer;
    AudioBuffer<float> hiBuffer;
    AudioBuffer<float> finalBuffer;
    
private:
    
    float meterVal;
    
    VUAnalysis vuAnalysis;

    dsp::Compressor<float> lowC;
    dsp::Compressor<float> midC;
    dsp::Compressor<float> hiC;
    
    dsp::DryWetMixer<float> DryWet;
    
    Biquad BQLow; Biquad BQLow1; int bqFLow;
    Biquad BQMid; Biquad BQMid1; float bqFMid;
    Biquad BQHi; Biquad BQHi1; int bqFHi;
    
    int bufferLength;
};
