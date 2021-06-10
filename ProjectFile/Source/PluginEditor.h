/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SimpleMeter.h"
#include "LEDMeter.h"
#include "KnobSmallBlack.h"
#include "KnobSmallBlack_2.h"

//==============================================================================
/**
*/
class MultiBandCompressorAudioProcessorEditor  : public AudioProcessorEditor,
                                                 public Slider::Listener,
                                                 public Timer,
                                                 public TextEditor::Listener

{
public:
    MultiBandCompressorAudioProcessorEditor (MultiBandCompressorAudioProcessor&);
    ~MultiBandCompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider * slider) override;
    void timerCallback() override;
    
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultiBandCompressorAudioProcessor& audioProcessor;
    
    KnobSmallBlack smallKnob1;
    KnobSmallBlack smallKnob2;
    KnobSmallBlack_2 smallKnob3;
    
    
    // Low knobs
    Slider threshLow;
    Slider ratioLow;
    Slider attackLow;
    Slider releaseLow;
    
    // Mid knobs
    Slider threshMid;
    Slider ratioMid;
    Slider attackMid;
    Slider releaseMid;
    
    // Hi knobs
    Slider threshHi;
    Slider ratioHi;
    Slider attackHi;
    Slider releaseHi;
    
    // Overall knobs
    Slider signalGain;
    Slider dryWet;
    
    // Design classes
    LookAndFeel_V4 lowHiKnobColor;
    LookAndFeel_V4 midKnobColor;
    LookAndFeel_V4 overallKnobsColor;
    LookAndFeel_V4 fValsColor;
    
    Colour primaryColor = Colours::maroon;
    Colour secondaryColor = Colours::burlywood;
    Colour tertiaryColor = Colours::black;
    
    // Frequency parameter text boxes
    
    // Make these just text boxes? // ---------------------------------------------------------------------------------------------------
    Slider lowMidF; // freq dividing low's and mid's
    Slider midHiF; // freq dividing mid's and high's
    
    // Meters
    SimpleMeter lowMeter;
    SimpleMeter midMeter;
    SimpleMeter hiMeter;
    SimpleMeter gainMeter;
    SimpleMeter inMeter;
    
//    LEDMeter gainMeter2;
//    LEDMeter inMeter2;
    
    MultiBandComp MBC;
    
public:
    
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiBandCompressorAudioProcessorEditor)
};


