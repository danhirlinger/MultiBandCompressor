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
    LookAndFeel_V4::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("Andale Mono");

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
    
    // would like to figure out how to change color of meter; below did not work
//    lowMeter.setColour (juce::Slider::thumbColourId, juce::Colours::green);
    
    // --------------------------------------------------------------------
    // ---------------- KNOBS FOR LOWS ------------------------------------
//    threshLow.addListener(this);
    threshLow.setBounds(70,65,150,150);
    threshLow.setRange(-50.f,0.f,.1f); // dB
//    threshLow.setValue(MBC.tLow);
    threshLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    threshLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshLow.setSize(80,100);
    threshLow.setLookAndFeel(&smallKnob1);
    addAndMakeVisible(threshLow);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshLow",threshLow));
    
//    sliderAttachments = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.state,"threshLow",threshLow);
    
//    ratioLow.addListener(this);
    ratioLow.setBounds(70,170,150,150);
    ratioLow.setRange(1.f, 100.f, .1f); // #:1 or something
//    ratioLow.setValue(MBC.raLow);
    ratioLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    ratioLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioLow.setSize(80,100);
    ratioLow.setLookAndFeel(&smallKnob1);
    addAndMakeVisible(ratioLow);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioLow",ratioLow));
//    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"ratioLow",ratioLow));
    
//    attackLow.addListener(this);
    attackLow.setBounds(70,285,150,150);
    attackLow.setRange(0.1f, 1000.f, .1f); // ms
//    attackLow.setValue(MBC.aLow);
    attackLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    attackLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackLow.setSize(80,100);
    attackLow.setLookAndFeel(&smallKnob1);
    addAndMakeVisible(attackLow);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackLow",attackLow));
    
//    releaseLow.addListener(this);
    releaseLow.setBounds(70,390,150,150);
    releaseLow.setRange(0.1f, 1000.f, .1f); // ms
//    releaseLow.setValue(MBC.reLow);
    releaseLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    releaseLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseLow.setSize(80,100);
    releaseLow.setLookAndFeel(&smallKnob1);
    addAndMakeVisible(releaseLow);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseLow",releaseLow));

    // --------------------------------------------------------------------
    // --------------------- KNOBS FOR MIDS -------------------------------
    
    // change text color in the boxes
//    threshMid.addListener(this);
    threshMid.setBounds(215,65,150,150);
//    threshMid.setRange(-24.f,6.f,.1f); // dB
    threshMid.setRange(-50.f,0.f,.1f);
//    threshMid.setValue(MBC.tMid);
    threshMid.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    threshMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshMid.setSize(80,100);
    threshMid.setLookAndFeel(&smallKnob2);
    addAndMakeVisible(threshMid);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshMid",threshMid));
    
//    ratioMid.addListener(this);
    ratioMid.setBounds(215,170,150,150);
    ratioMid.setRange(1.f, 100.f, .1f); // #:1 or something
//    ratioMid.setValue(MBC.raMid);
    ratioMid.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    ratioMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioMid.setSize(80,100);
    ratioMid.setLookAndFeel(&smallKnob2);
    addAndMakeVisible(ratioMid);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioMid",ratioMid));
    
//    attackMid.addListener(this);
    attackMid.setBounds(215,285,150,150);
    attackMid.setRange(0.1f, 1000.f, .1f); // ms
//    attackMid.setValue(MBC.aMid);
    attackMid.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    attackMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackMid.setSize(80,100);
    attackMid.setLookAndFeel(&smallKnob2);
    addAndMakeVisible(attackMid);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackMid",attackMid));
    
//    releaseMid.addListener(this);
    releaseMid.setBounds(215,390,150,150);
    releaseMid.setRange(0.1f, 1000.f, .1f); // ms
//    releaseMid.setValue(MBC.reMid);
    releaseMid.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    releaseMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseMid.setSize(80,100);
    releaseMid.setLookAndFeel(&smallKnob2);
    addAndMakeVisible(releaseMid);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseMid",releaseMid));
    
    // --------------------------------------------------------------------
    // --------------------- KNOBS FOR HIS --------------------------------
//    threshHi.addListener(this);
    threshHi.setBounds(365,65,150,150);
    threshHi.setRange(-50.f,0.f,.1f); // dB
//    threshHi.setValue(MBC.tHi);
    threshHi.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    threshHi.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshHi.setSize(80,100);
    threshHi.setLookAndFeel(&smallKnob1);
    addAndMakeVisible(threshHi);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshHi",threshHi));
    
//    ratioHi.addListener(this);
    ratioHi.setBounds(365,170,150,150);
    ratioHi.setRange(1.f, 100.f, .1f); // #:1 or something
//    ratioHi.setValue(MBC.raHi);
    ratioHi.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    ratioHi.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioHi.setSize(80,100);
    ratioHi.setLookAndFeel(&smallKnob1);
    addAndMakeVisible(ratioHi);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioHi",ratioHi));
    
//    attackHi.addListener(this);
    attackHi.setBounds(365,285,150,150);
    attackHi.setRange(0.1f, 1000.f, .1f); // ms
//    attackHi.setValue(MBC.aHi);
    attackHi.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    attackHi.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackHi.setSize(80,100);
    attackHi.setLookAndFeel(&smallKnob1);
    addAndMakeVisible(attackHi);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackHi",attackHi));
    
//    releaseHi.addListener(this);
    releaseHi.setBounds(365,390,150,150);
    releaseHi.setRange(0.1f, 1000.f, .1f); // ms
//    releaseHi.setValue(MBC.reHi);
    releaseHi.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    releaseHi.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseHi.setSize(80,100);
    releaseHi.setLookAndFeel(&smallKnob1);
    addAndMakeVisible(releaseHi);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseHi",releaseHi));
    
    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    
//    signalGain.addListener(this);
    signalGain.setBounds(320,540,100,100);
    signalGain.setRange(-12.f,12.f,.1f);
//    signalGain.setValue(MBC.gain);
    signalGain.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    signalGain.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    signalGain.setSize(60,80);
    signalGain.setLookAndFeel(&smallKnob3);
    addAndMakeVisible(signalGain);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"signalGain",signalGain));
    
//    dryWet.addListener(this);
    dryWet.setBounds(410,540,50,50);
    dryWet.setRange(0.f,1.f,.01f);
//    dryWet.setValue(0.5f);
    dryWet.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    dryWet.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryWet.setLookAndFeel(&smallKnob3);
    dryWet.setSize(60,80);
    addAndMakeVisible(dryWet);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"dryWet",dryWet));
    
//    lowMidF.addListener(this);
    lowMidF.setBounds(115, 5, 100, 30);
    lowMidF.setRange(250,1000,1);
//    lowMidF.setValue(MBC.lowMidF);
    lowMidF.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 20);
    lowMidF.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lowMidF.setSize(50,60);
    lowMidF.setLookAndFeel(&smallKnob3);
    addAndMakeVisible(lowMidF);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"lowMidF",lowMidF));
    
//    lowMidF2.addListener(this);
//    lowMidF2.setBounds(50, 50, 50, 50);
//    lowMidF2.textBoxTextChanged();
//
//    addAndMakeVisible(lowMidF2);
    
    
//    midHiF.addListener(this);
    midHiF.setBounds(335, 5, 100, 30);
    midHiF.setRange(1500, 5000, 1);
//    midHiF.setValue(MBC.midHiF);
    midHiF.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 20);
    midHiF.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    midHiF.setSize(50,60);
    midHiF.setLookAndFeel(&smallKnob3);
    addAndMakeVisible(midHiF);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"midHiF",midHiF));
    
    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    // Meters
    
//    lowMeter.setBounds(150, 100, 10, 320);
//    lowMeter.configuration = SimpleMeter::VERTICAL;
//    addAndMakeVisible(lowMeter);
//
//    midMeter.setBounds(310,100,10,320);
//    midMeter.configuration = SimpleMeter::VERTICAL;
//    addAndMakeVisible(midMeter);
//
//    hiMeter.setBounds(470,100,10,320);
//    hiMeter.configuration = SimpleMeter::VERTICAL;
//    addAndMakeVisible(hiMeter);
    
    gainMeter.setBounds(60,585,230,10);
    gainMeter.configuration = SimpleMeter::HORIZONTAL;
    addAndMakeVisible(gainMeter);
    
    inMeter.setBounds(60,525,230,10);
    inMeter.configuration = SimpleMeter::HORIZONTAL;
    addAndMakeVisible(inMeter);
    
    startTimerHz(30);
    
//    gainMeter2.setBounds(60,585,230,10);
//    
//    
//    inMeter2.setBounds(60, 525, 230, 10);
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
//    g.setColour(primaryColor);
    g.drawLine(25, 167, 475, 167, 0.5);
    g.drawLine(25, 282, 475, 282, 0.5);
    g.drawLine(25, 387, 475, 387, 0.5);
    g.drawLine(25, 555, 300, 555, 0.75);
//
//    g.setColour(tertiaryColor);
//    g.fillRect(0,425,500,200);
    
    // draw text for knob labels (will appear on left side)
    g.setFont(14);
    g.setColour(Colours::burlywood);
    g.drawFittedText("Threshold", 3, 80, 75, 50, Justification::centred, 1);
    g.drawFittedText("Ratio", 3, 195, 75, 50, Justification::centred, 1);
//    g.drawFittedText("Knee", 3, 260, 75, 50, Justification::centred, 1);
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MultiBandCompressorAudioProcessorEditor::sliderValueChanged(juce::Slider * slider){
    // don't need this with AudioProcessorValueTreeState //
    
//    if (slider == &threshLow){
//        MBC.tLow = threshLow.getValue();}
//    if (slider == &ratioLow){
//        MBC.raLow = ratioLow.getValue();
//    } if (slider == &attackLow){
//        MBC.aLow = attackLow.getValue();
//    } if (slider == &releaseLow){
//        MBC.reLow = releaseLow.getValue();
//    }
//    
//    if (slider == &threshMid){
//        MBC.tMid = threshMid.getValue();
//    } if (slider == &ratioMid){
//        MBC.raMid = ratioMid.getValue();
//    } if (slider == &attackMid){
//        MBC.aMid = attackMid.getValue();
//    } if (slider == &releaseMid){
//        MBC.reMid = releaseMid.getValue();
//    }
//    
//    if (slider == &threshHi){
//        MBC.tHi = threshHi.getValue();
//    } if (slider == &ratioHi){
//        MBC.raHi = ratioHi.getValue();
//    } if (slider == &attackHi){
//        MBC.aHi = attackHi.getValue();
//    } if (slider == &releaseHi){
//        MBC.reHi = releaseHi.getValue();
//    }
//    
//    if (slider == &lowMidF){
//        MBC.lowMidF = lowMidF.getValue();
//    } if (slider == &midHiF){
//        MBC.midHiF = midHiF.getValue();
//    }
//    
//    if (slider == &signalGain){
//        MBC.gain = signalGain.getValue();
//    }
}

void MultiBandCompressorAudioProcessorEditor::timerCallback(){
    lowMeter.update(audioProcessor.lowMeterVal);
    midMeter.update(audioProcessor.midMeterVal);
    hiMeter.update(audioProcessor.hiMeterVal);
    gainMeter.update(audioProcessor.gainMeterVal);
    inMeter.update(audioProcessor.inMeterVal);
    
//    signalGain.setValue(audioProcessor.MBC.gain);
}
