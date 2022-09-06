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
    LookAndFeel_V4::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("Andale Mono");

    setColours();
    connectSliderAttachments();
    resized();
    
    // would like to figure out how to change color of meter; below did not work
//    lowMeter.setColour (juce::Slider::thumbColourId, juce::Colours::green);
    
    // ---------------- KNOBS FOR LOWS ------------------------------------

    threshLow.setLookAndFeel(&smallKnob1);
    setCompSliderParams(threshLow);
    ratioLow.setLookAndFeel(&smallKnob1);
    setCompSliderParams(ratioLow);
    attackLow.setLookAndFeel(&smallKnob1);
    setCompSliderParams(attackLow);
    releaseLow.setLookAndFeel(&smallKnob1);
    setCompSliderParams(releaseLow);

    // --------------------- KNOBS FOR MIDS -------------------------------
    
    // change text color in the boxes
    threshMid.setLookAndFeel(&smallKnob2);
    setCompSliderParams(threshMid);
    ratioMid.setLookAndFeel(&smallKnob2);
    setCompSliderParams(ratioMid);
    attackMid.setLookAndFeel(&smallKnob2);
    setCompSliderParams(attackMid);
    releaseMid.setLookAndFeel(&smallKnob2);
    setCompSliderParams(releaseMid);

    // --------------------- KNOBS FOR HIS --------------------------------
    threshHi.setLookAndFeel(&smallKnob1);
    setCompSliderParams(threshHi);
    ratioHi.setLookAndFeel(&smallKnob1);
    setCompSliderParams(ratioHi);
    attackHi.setLookAndFeel(&smallKnob1);
    setCompSliderParams(attackHi);
    releaseHi.setLookAndFeel(&smallKnob1);
    setCompSliderParams(releaseHi);
    
    // -------------------------------Other Knobs---------------------------------------------
    

    signalGain.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    signalGain.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    signalGain.setSize(60,80);
    signalGain.setLookAndFeel(&smallKnob3);
    addAndMakeVisible(signalGain);
    
    dryWet.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    dryWet.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryWet.setLookAndFeel(&smallKnob3);
    dryWet.setSize(60,80);
    addAndMakeVisible(dryWet);

    lowMidF.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 20);
    lowMidF.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lowMidF.setSize(50,60);
    lowMidF.setLookAndFeel(&smallKnob3);
    addAndMakeVisible(lowMidF);
    
    midHiF.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 20);
    midHiF.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    midHiF.setSize(50,60);
    midHiF.setLookAndFeel(&smallKnob3);
    addAndMakeVisible(midHiF);

    // -----------------------------------Meters---------------------------------
    gainMeter.configuration = SimpleMeter::HORIZONTAL;
    addAndMakeVisible(gainMeter);
    
    inMeter.configuration = SimpleMeter::HORIZONTAL;
    addAndMakeVisible(inMeter);
    
    startTimerHz(30);
}

MultiBandCompressorAudioProcessorEditor::~MultiBandCompressorAudioProcessorEditor()
{
}

//==============================================================================
void MultiBandCompressorAudioProcessorEditor::paint (Graphics& g)
{
    // Establish background colors
//    g.fillAll(primaryColor);
    g.fillAll(tertiaryColor);
    
    g.setColour(tertiaryColor.brighter());
    g.fillRect(175, 0, 160, 500);
    g.setColour(secondaryColor);
    g.fillRect(0, 500, 500, 2);
    g.drawLine(25, 167, 475, 167, 0.5);
    g.drawLine(25, 282, 475, 282, 0.5);
    g.drawLine(25, 387, 475, 387, 0.5);
    g.drawLine(25, 555, 300, 555, 0.75);
    
    // draw text for knob labels (will appear on left side)
    g.setFont(14);
    g.setColour(Colours::burlywood);
    g.drawFittedText("Threshold", 3, 80, 75, 50, Justification::centred, 1);
    g.drawFittedText("Ratio", 3, 195, 75, 50, Justification::centred, 1);
    g.drawFittedText("Attack", 3, 300, 75, 50, Justification::centred, 1);
    g.drawFittedText("Release", 3, 415, 75, 50, Justification::centred, 1);
    g.setFont(17);
    g.drawFittedText("Gain", 310, 500, 75, 50, Justification::centred, 1);
    g.drawFittedText("Dry/Wet", 400, 500, 75, 50, Justification::centred, 1);
    
    // text for frequency band labels
    g.setFont(30);
    g.setColour(Colours::burlywood);
    g.drawFittedText("Low", 40, 15, 115, 50, Justification::left, 1);
    g.drawFittedText("Hi", 370, 15, 100, 50, Justification::right, 1);
    g.drawFittedText("In", 12, 505, 115, 50, Justification::left, 1);
    g.drawFittedText("Out", 5, 565, 115, 50, Justification::left, 1);
    g.setColour(secondaryColor);
    g.drawFittedText("Mid", 200, 15, 115, 50, Justification::centred, 1);
    
}

void MultiBandCompressorAudioProcessorEditor::resized()
{
    setSize(500, 625);
    
    threshLow.setBounds(70,65,150,150);
    attackLow.setBounds(70,285,150,150);
    ratioLow.setBounds(70,170,150,150);
    releaseLow.setBounds(70,390,150,150);
    
    threshMid.setBounds(215,65,150,150);
    ratioMid.setBounds(215,170,150,150);
    attackMid.setBounds(215,285,150,150);
    releaseMid.setBounds(215,390,150,150);
    
    threshHi.setBounds(365,65,150,150);
    ratioHi.setBounds(365,170,150,150);
    attackHi.setBounds(365,285,150,150);
    releaseHi.setBounds(365,390,150,150);
    
    signalGain.setBounds(320,540,100,100);
    dryWet.setBounds(410,540,50,50);
    lowMidF.setBounds(115, 5, 100, 30);
    midHiF.setBounds(335, 5, 100, 30);
    
    gainMeter.setBounds(60,585,230,10);
    inMeter.setBounds(60,525,230,10);
}


void MultiBandCompressorAudioProcessorEditor::timerCallback(){
    lowMeter.update(audioProcessor.lowMeterVal);
    midMeter.update(audioProcessor.midMeterVal);
    hiMeter.update(audioProcessor.hiMeterVal);
    gainMeter.update(audioProcessor.gainMeterVal);
    inMeter.update(audioProcessor.inMeterVal);
}

void MultiBandCompressorAudioProcessorEditor::setCompSliderParams(juce::Slider &slider){
    
    slider.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setSize(80,100);
    addAndMakeVisible(slider);
}

void MultiBandCompressorAudioProcessorEditor::setColours(){
    
    // primary = maroon
    // secondary = gold
    // tertiary = black
    lowHiKnobColor.setColour (Slider::thumbColourId, secondaryColor);
    lowHiKnobColor.setColour (Slider::textBoxOutlineColourId, tertiaryColor);
    lowHiKnobColor.setColour (Slider::rotarySliderFillColourId, secondaryColor.darker());
    
    midKnobColor.setColour (Slider::thumbColourId, primaryColor);
    midKnobColor.setColour (Slider::textBoxTextColourId, primaryColor);
    midKnobColor.setColour (Slider::textBoxOutlineColourId, tertiaryColor);
    midKnobColor.setColour (Slider::rotarySliderFillColourId, primaryColor.darker());
    
    overallKnobsColor.setColour (Slider::thumbColourId, secondaryColor);
    overallKnobsColor.setColour (Slider::textBoxOutlineColourId, tertiaryColor);
    overallKnobsColor.setColour (Slider::rotarySliderFillColourId, primaryColor);
    
    fValsColor.setColour(Slider::thumbColourId, Colours::white);
    fValsColor.setColour(Slider::textBoxOutlineColourId, tertiaryColor);
    fValsColor.setColour (Slider::textBoxBackgroundColourId, tertiaryColor);
    
    smallKnob1.setColour(Slider::textBoxOutlineColourId, tertiaryColor);
    smallKnob1.setColour(Slider::textBoxTextColourId, secondaryColor);
    
    smallKnob2.setColour(Slider::textBoxOutlineColourId, tertiaryColor.brighter());
    smallKnob2.setColour(Slider::textBoxTextColourId, secondaryColor);
    
    smallKnob3.setColour(Slider::textBoxOutlineColourId, tertiaryColor);
    smallKnob3.setColour(Slider::textBoxTextColourId, secondaryColor);
    
}

void MultiBandCompressorAudioProcessorEditor::connectSliderAttachments(){

    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshLow",threshLow));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioLow",ratioLow));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackLow",attackLow));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseLow",releaseLow));
    
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshMid",threshMid));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioMid",ratioMid));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackMid",attackMid));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseMid",releaseMid));
    
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshHi",threshHi));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioHi",ratioHi));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackHi",attackHi));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseHi",releaseHi));
    
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"signalGain",signalGain));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"dryWet",dryWet));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"lowMidF",lowMidF));
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"midHiF",midHiF));
}
