/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SimpleMeter.h"

//==============================================================================
/**
*/
class MultiBandCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                 public juce::Slider::Listener,
                                                 public juce::Timer

{
public:
    MultiBandCompressorAudioProcessorEditor (MultiBandCompressorAudioProcessor&);
    ~MultiBandCompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider * slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultiBandCompressorAudioProcessor& audioProcessor;
    
    // Low knobs
    juce::Slider threshLow;
    juce::Slider ratioLow;
    juce::Slider kneeLow;
    juce::Slider attackLow;
    juce::Slider releaseLow;
    
    // Mid knobs
    juce::Slider threshMid;
    juce::Slider ratioMid;
    juce::Slider kneeMid;
    juce::Slider attackMid;
    juce::Slider releaseMid;
    
    // Hi knobs
    juce::Slider threshHi;
    juce::Slider ratioHi;
    juce::Slider kneeHi;
    juce::Slider attackHi;
    juce::Slider releaseHi;
    
    // Overall knobs
    juce::Slider signalGain;
    
    // Design classes
    juce::LookAndFeel_V4 lowHiKnobColor;
    juce::LookAndFeel_V4 midKnobColor;
    
    // Frequency parameter text boxes
    juce::Slider lowMidF; // freq dividing low's and mid's
    juce::Slider midHiF; // freq dividing mid's and high's
    
    // Meters
    SimpleMeter lowMeter;
    SimpleMeter midMeter;
    SimpleMeter hiMeter;
    
    SimpleMeter gainMeter;

    void timerCallback() override;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiBandCompressorAudioProcessorEditor)
};
