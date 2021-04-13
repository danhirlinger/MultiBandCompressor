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
    setSize(500, 525);
    
    lowHiKnobColor.setColour (Slider::thumbColourId, secondaryColor);
    midKnobColor.setColour (Slider::thumbColourId, primaryColor);
    midKnobTextColor.setColour (Slider::textBoxTextColourId, Colours::black);
    fValsColor.setColour (Slider::textBoxBackgroundColourId, tertiaryColor);
    
    
//    midKnobColors::thumbColorId = primaryColor;
    // would like to figure out how to change color of meter; below did not work
//    lowMeter.setColour (juce::Slider::thumbColourId, juce::Colours::green);
    
    // --------------------------------------------------------------------
    // ---------------- KNOBS FOR LOWS ------------------------------------
//    threshLow.addListener(this);
    threshLow.setBounds(60,65,150,150);
    threshLow.setRange(-24.f,6.f,.1f); // dB
//    threshLow.setValue(MBC.tLow);
    threshLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    threshLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshLow.setSize(80,80);
    threshLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(threshLow);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshLow",threshLow));
    
//    sliderAttachments = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.state,"threshLow",threshLow);
    
//    ratioLow.addListener(this);
    ratioLow.setBounds(60,160,150,150);
    ratioLow.setRange(1.f, 100.f, .1f); // #:1 or something
//    ratioLow.setValue(MBC.raLow);
    ratioLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    ratioLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioLow.setSize(80,80);
    ratioLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(ratioLow);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioLow",ratioLow));
//    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"ratioLow",ratioLow));
    
//    attackLow.addListener(this);
    attackLow.setBounds(60,245,150,150);
    attackLow.setRange(0.1f, 1000.f, .1f); // ms
//    attackLow.setValue(MBC.aLow);
    attackLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    attackLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackLow.setSize(80,80);
    attackLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(attackLow);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackLow",attackLow));
    
//    releaseLow.addListener(this);
    releaseLow.setBounds(60,340,150,150);
    releaseLow.setRange(0.1f, 1000.f, .1f); // ms
//    releaseLow.setValue(MBC.reLow);
    releaseLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    releaseLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseLow.setSize(80,80);
    releaseLow.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(releaseLow);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseLow",releaseLow));

    // --------------------------------------------------------------------
    // --------------------- KNOBS FOR MIDS -------------------------------
    
    // change text color in the boxes
//    threshMid.addListener(this);
    threshMid.setBounds(200,65,150,150);
    threshMid.setRange(-24.f,6.f,.1f); // dB
//    threshMid.setValue(MBC.tMid);
    threshMid.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    threshMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshMid.setSize(80,80);
    threshMid.setLookAndFeel(&midKnobColor);
//    threshMid.setLookAndFeel(&midKnobTextColor);
    addAndMakeVisible(threshMid);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshMid",threshMid));
    
//    ratioMid.addListener(this);
    ratioMid.setBounds(200,160,150,150);
    ratioMid.setRange(1.f, 100.f, .1f); // #:1 or something
//    ratioMid.setValue(MBC.raMid);
    ratioMid.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    ratioMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioMid.setSize(80,80);
    ratioMid.setLookAndFeel(&midKnobColor);
    ratioMid.setLookAndFeel(&midKnobTextColor);
    addAndMakeVisible(ratioMid);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioMid",ratioMid));
    
//    attackMid.addListener(this);
    attackMid.setBounds(200,245,150,150);
    attackMid.setRange(0.1f, 1000.f, .1f); // ms
//    attackMid.setValue(MBC.aMid);
    attackMid.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    attackMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackMid.setSize(80,80);
    attackMid.setLookAndFeel(&midKnobColor);
    attackMid.setLookAndFeel(&midKnobTextColor);
    addAndMakeVisible(attackMid);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackMid",attackMid));
    
//    releaseMid.addListener(this);
    releaseMid.setBounds(200,340,150,150);
    releaseMid.setRange(0.1f, 1000.f, .1f); // ms
//    releaseMid.setValue(MBC.reMid);
    releaseMid.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    releaseMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseMid.setSize(80,80);
    releaseMid.setLookAndFeel(&midKnobColor);releaseMid.setLookAndFeel(&midKnobTextColor);
    addAndMakeVisible(releaseMid);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseMid",releaseMid));
    
    // --------------------------------------------------------------------
    // --------------------- KNOBS FOR HIS --------------------------------
//    threshHi.addListener(this);
    threshHi.setBounds(365,65,150,150);
    threshHi.setRange(-24.f,6.f,.1f); // dB
//    threshHi.setValue(MBC.tHi);
    threshHi.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    threshHi.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshHi.setSize(80,80);
    threshHi.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(threshHi);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"threshHi",threshHi));
    
//    ratioHi.addListener(this);
    ratioHi.setBounds(365,160,150,150);
    ratioHi.setRange(1.f, 100.f, .1f); // #:1 or something
//    ratioHi.setValue(MBC.raHi);
    ratioHi.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    ratioHi.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioHi.setSize(80,80);
    ratioHi.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(ratioHi);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"ratioHi",ratioHi));
    
//    attackHi.addListener(this);
    attackHi.setBounds(365,245,150,150);
    attackHi.setRange(0.1f, 1000.f, .1f); // ms
//    attackHi.setValue(MBC.aHi);
    attackHi.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    attackHi.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackHi.setSize(80,80);
    attackHi.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(attackHi);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"attackHi",attackHi));
    
//    releaseHi.addListener(this);
    releaseHi.setBounds(365,340,150,150);
    releaseHi.setRange(0.1f, 1000.f, .1f); // ms
//    releaseHi.setValue(MBC.reHi);
    releaseHi.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    releaseHi.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseHi.setSize(80,80);
    releaseHi.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(releaseHi);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"releaseHi",releaseHi));
    
    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    
//    signalGain.addListener(this);
    signalGain.setBounds(310,445,100,100);
    signalGain.setRange(-12.f,12.f,.1f);
//    signalGain.setValue(MBC.gain);
    signalGain.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    signalGain.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    signalGain.setSize(80,80);
    signalGain.setLookAndFeel(&lowHiKnobColor);
    addAndMakeVisible(signalGain);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"signalGain",signalGain));
    
//    dryWet.addListener(this);
    dryWet.setBounds(400,445,50,50);
    dryWet.setRange(0.f,1.f,.01f);
//    dryWet.setValue(0.5f);
    dryWet.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    dryWet.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryWet.setLookAndFeel(&lowHiKnobColor);
    dryWet.setSize(80,80);
    addAndMakeVisible(dryWet);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"dryWet",dryWet));
    
//    lowMidF.addListener(this);
    lowMidF.setBounds(144, 30, 100, 30);
    lowMidF.setRange(250,1000,1);
//    lowMidF.setValue(MBC.lowMidF);
    lowMidF.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 20);
    lowMidF.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lowMidF.setSize(60,60);
    lowMidF.setLookAndFeel(&fValsColor);
    addAndMakeVisible(lowMidF);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"lowMidF",lowMidF));
    
    
//    midHiF.addListener(this);
    midHiF.setBounds(306, 30, 100, 30);
    midHiF.setRange(1500, 5000, 1);
//    midHiF.setValue(MBC.midHiF);
    midHiF.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 20);
    midHiF.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    midHiF.setSize(60,60);
    midHiF.setLookAndFeel(&fValsColor);
    addAndMakeVisible(midHiF);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.MBCstate,"midHiF",midHiF));
    
    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    // Meters
    
    // Make meters different colors??????
    
    lowMeter.setBounds(150, 100, 10, 320);
    lowMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(lowMeter);
    
    midMeter.setBounds(310,100,10,320);
    midMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(midMeter);
    
    hiMeter.setBounds(470,100,10,320);
    hiMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(hiMeter);
    
    gainMeter.setBounds(30,470,280,15);
    gainMeter.configuration = SimpleMeter::HORIZONTAL;
    addAndMakeVisible(gainMeter);
    
    startTimerHz(30);
}

MultiBandCompressorAudioProcessorEditor::~MultiBandCompressorAudioProcessorEditor()
{
}

//==============================================================================
void MultiBandCompressorAudioProcessorEditor::paint (Graphics& g)
{
    // Establish background colors
    g.fillAll(primaryColor);
    
    g.setColour(secondaryColor);
    g.fillRect(175, 0, 160, 525);
    
    g.setColour(tertiaryColor);
    g.fillRect(0,425,500,200);
    
    // draw text for knob labels (will appear on left side)
    g.setFont(14);
    g.setColour(Colours::burlywood);
    g.drawFittedText("Threshold", 3, 80, 75, 50, Justification::centred, 1);
    g.drawFittedText("Ratio", 3, 175, 75, 50, Justification::centred, 1);
//    g.drawFittedText("Knee", 3, 260, 75, 50, Justification::centred, 1);
    g.drawFittedText("Attack", 3, 260, 75, 50, Justification::centred, 1);
    g.drawFittedText("Release", 3, 355, 75, 50, Justification::centred, 1);
    g.setFont(17);
    g.drawFittedText("Gain", 310, 415, 75, 50, Justification::centred, 1);
    g.drawFittedText("Dry/Wet", 400, 415, 75, 50, Justification::centred, 1);
    
    // text for frequency band labels
    g.setFont(30);
    g.setColour(Colours::burlywood);
    g.drawFittedText("Low", 40, 15, 115, 50, Justification::centred, 1);
    g.drawFittedText("Hi", 370, 15, 115, 50, Justification::centred, 1);
    g.drawFittedText("Output", 115, 420, 115, 50, Justification::centred, 1);
    g.setColour(Colours::maroon);
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
    
//    signalGain.setValue(audioProcessor.MBC.gain);
}
