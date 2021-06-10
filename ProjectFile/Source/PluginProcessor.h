/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VUAnalysis.h"
#include "MultiBandComp.h"

//==============================================================================
/**
*/
class MultiBandCompressorAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MultiBandCompressorAudioProcessor();
    ~MultiBandCompressorAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float lowMeterVal;
    float midMeterVal;
    float hiMeterVal;
    float gainMeterVal;
    float inMeterVal;
    
    VUAnalysis VU;
    
    MultiBandComp MBC;
    
    AudioProcessorValueTreeState MBCstate;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    
    float tLowSmooth = MBC.tLow;
    float raLowSmooth = MBC.raLow;
    float aLowSmooth = MBC.aLow;
    float reLowSmooth = MBC.reLow;
    
    float tMidSmooth = MBC.tMid;
    float raMidSmooth = MBC.raMid;
    float aMidSmooth = MBC.aMid;
    float reMidSmooth = MBC.reMid;
    
    float tHiSmooth = MBC.tHi;
    float raHiSmooth = MBC.raHi;
    float aHiSmooth = MBC.aHi;
    float reHiSmooth = MBC.reHi;
    
    float gainSmooth = MBC.gain;
    float dryWetSmooth = MBC.dryWet;
    float lowMidFSmooth = MBC.lowMidF;
    float midHiFSmooth = MBC.midHiF;
    
private:
    
    dsp::ProcessSpec spec;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiBandCompressorAudioProcessor)
};
