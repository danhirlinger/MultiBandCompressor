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

    setSize(500, 600);
    
    // Knobs for compression of lows
    threshLow.addListener(this);
    threshLow.setBounds(50,75,150,150);
    threshLow.setRange(-24.f,6.f,.1f); // dB
    threshLow.setValue(-24.f);
    threshLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    threshLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshLow.setSize(80,80);
    addAndMakeVisible(threshLow);
    
    ratioLow.addListener(this);
    ratioLow.setBounds(50,160,150,150);
    ratioLow.setRange(1.f, 100.f, .1f); // #:1 or something
    ratioLow.setValue(1.f);
    ratioLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    ratioLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioLow.setSize(80,80);
    addAndMakeVisible(ratioLow);
    
    kneeLow.addListener(this);
    kneeLow.setBounds(50,235,150,150);
    kneeLow.setRange(0.f, 24.f, .1f); // figure out units of this value
    kneeLow.setValue(0.f);
    kneeLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    kneeLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    kneeLow.setSize(80,80);
    addAndMakeVisible(kneeLow);
    
    attackLow.addListener(this);
    attackLow.setBounds(50,320,150,150);
    attackLow.setRange(0.1f, 1000.f, .1f); // ms
    attackLow.setValue(0.1f);
    attackLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    attackLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackLow.setSize(80,80);
    addAndMakeVisible(attackLow);
    
    releaseLow.addListener(this);
    releaseLow.setBounds(50,395,150,150);
    releaseLow.setRange(0.1f, 1000.f, .1f); // ms
    releaseLow.setValue(0.1f);
    releaseLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    releaseLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseLow.setSize(80,80);
    addAndMakeVisible(releaseLow);
    
}

MultiBandCompressorAudioProcessorEditor::~MultiBandCompressorAudioProcessorEditor()
{
}

//==============================================================================
void MultiBandCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::orange);
    g.drawFittedText("Low", 25, 25, 115, 50, juce::Justification::centred, 1);

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
