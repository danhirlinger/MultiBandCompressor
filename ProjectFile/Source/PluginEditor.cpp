/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
MultiBandCompressorAudioProcessorEditor::MultiBandCompressorAudioProcessorEditor (MultiBandCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize(500, 625);
    
    lowHiKnobColor.setColour (juce::Slider::thumbColourId, juce::Colours::darkred);
    
    // Knobs for compression of lows
    threshLow.addListener(this);
    threshLow.setBounds(75,75,150,150);
    threshLow.setRange(-24.f,6.f,.1f); // dB
    threshLow.setValue(-24.f);
    threshLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    threshLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshLow.setSize(80,80);
    threshLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(threshLow);
    
    ratioLow.addListener(this);
    ratioLow.setBounds(75,160,150,150);
    ratioLow.setRange(1.f, 100.f, .1f); // #:1 or something
    ratioLow.setValue(1.f);
    ratioLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    ratioLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioLow.setSize(80,80);
    ratioLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(ratioLow);
    
    kneeLow.addListener(this);
    kneeLow.setBounds(75,235,150,150);
    kneeLow.setRange(0.f, 24.f, .1f); // figure out units of this value
    kneeLow.setValue(0.f);
    kneeLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    kneeLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    kneeLow.setSize(80,80);
    kneeLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(kneeLow);
    
    attackLow.addListener(this);
    attackLow.setBounds(75,320,150,150);
    attackLow.setRange(0.1f, 1000.f, .1f); // ms
    attackLow.setValue(0.1f);
    attackLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    attackLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackLow.setSize(80,80);
    attackLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(attackLow);
    
    releaseLow.addListener(this);
    releaseLow.setBounds(75,395,150,150);
    releaseLow.setRange(0.1f, 1000.f, .1f); // ms
    releaseLow.setValue(0.1f);
    releaseLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    releaseLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseLow.setSize(80,80);
    releaseLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(releaseLow);
    
}

MultiBandCompressorAudioProcessorEditor::~MultiBandCompressorAudioProcessorEditor()
{
}

//==============================================================================
void MultiBandCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    auto baseColor = juce::Colours::powderblue;
    baseColor = baseColor.darker();
    baseColor = baseColor.darker();
    g.fillAll (baseColor);
    
    auto middleColor = baseColor.brighter();
    middleColor = middleColor.brighter();
    g.setColour(middleColor);
    g.fillRect(175, 0, 160, 650);
    
    // draw text for knob labels (will appear on left side)
    g.setFont(17);
    g.setColour(juce::Colours::white);
    g.drawFittedText("Threshold", 5, 80, 75, 50, juce::Justification::centred, 1);
    g.drawFittedText("Ratio", 5, 165, 75, 50, juce::Justification::centred, 1);
    g.drawFittedText("Knee", 5, 240, 75, 50, juce::Justification::centred, 1);
    g.drawFittedText("Attack", 5, 325, 75, 50, juce::Justification::centred, 1);
    g.drawFittedText("Release", 5, 400, 75, 50, juce::Justification::centred, 1);
    
    // text for frequency band labels
    g.setFont(20);
    g.setColour(juce::Colours::darkred);
    g.drawFittedText("Low", 55, 25, 115, 50, juce::Justification::centred, 1);
    g.drawFittedText("Hi", 360, 25, 115, 50, juce::Justification::centred, 1);
    g.setColour(juce::Colours::chocolate);
    g.drawFittedText("Mid", 200, 25, 115, 50, juce::Justification::centred, 1);
    
    
    
    

}

void MultiBandCompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MultiBandCompressorAudioProcessorEditor::sliderValueChanged(juce::Slider * slider){

    if (slider == &ratioLow){
       ;
    }
}
