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
class MultiBandCompressorAudioProcessorEditor  : public AudioProcessorEditor,
                                                 public Slider::Listener,
                                                 public Timer

{
public:
    MultiBandCompressorAudioProcessorEditor (MultiBandCompressorAudioProcessor&);
    ~MultiBandCompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider * slider) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultiBandCompressorAudioProcessor& audioProcessor;
    
    // Low knobs
    Slider threshLow;
    Slider ratioLow;
    Slider kneeLow;
    Slider attackLow;
    Slider releaseLow;
    
    // Mid knobs
    Slider threshMid;
    Slider ratioMid;
    Slider kneeMid;
    Slider attackMid;
    Slider releaseMid;
    
    // Hi knobs
    Slider threshHi;
    Slider ratioHi;
    Slider kneeHi;
    Slider attackHi;
    Slider releaseHi;
    
    // Overall knobs
    Slider signalGain;
    
    // Design classes
    LookAndFeel_V4 lowHiKnobColor;
    LookAndFeel_V4 midKnobColor;
    LookAndFeel_V4 midKnobTextColor;
    LookAndFeel_V4 lowHiTextBoxColor;
    LookAndFeel_V4 midTextBoxColor;
    LookAndFeel_V4 fValsColor;
    
    
    // Frequency parameter text boxes
    Slider lowMidF; // freq dividing low's and mid's
    Slider midHiF; // freq dividing mid's and high's
    
    // Meters
    SimpleMeter lowMeter;
    SimpleMeter midMeter;
    SimpleMeter hiMeter;
    
    SimpleMeter gainMeter;

    void timerCallback() override;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiBandCompressorAudioProcessorEditor)
};


