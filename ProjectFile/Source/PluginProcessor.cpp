/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultiBandCompressorAudioProcessor::MultiBandCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), MBCstate(*this, nullptr, "MBCParams", createParameterLayout()){}
#endif
//{
//    addParameter(MBC.gain = new AudioParameterFloat("gain", // string for ID'ing parameter in code
//                                   "Gain", // string shown in DAW to user
//                                   -12.f, // min value for range
//                                   12.f, // max value for range
//                                   0.f // default value
//                                                ));
//}

MultiBandCompressorAudioProcessor::~MultiBandCompressorAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout MultiBandCompressorAudioProcessor::createParameterLayout(){
    std::vector<std::unique_ptr<RangedAudioParameter>> params; // a vector of pointers to the parameters
    
    params.push_back( std::make_unique<AudioParameterFloat> ("threshLow","ThreshLow",-24.f,6.f,0.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("ratioLow","RatioLow",1.f,100.f,1.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("attackLow","AttackLow",0.1f,10000.f,1.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("releaseLow","ReleaseLow",0.1f,10000.f,1.f));
    
    params.push_back( std::make_unique<AudioParameterFloat> ("threshMid","ThreshMid",-24.f,6.f,0.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("ratioMid","RatioMid",1.f,100.f,1.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("attackMid","AttackMid",0.1f,10000.f,1.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("releaseMid","ReleaseMid",0.1f,10000.f,1.f));
    
    params.push_back( std::make_unique<AudioParameterFloat> ("threshHi","ThreshHi",-24.f,6.f,0.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("ratioHi","RatioHi",1.f,100.f,1.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("attackHi","AttackHi",0.1f,10000.f,1.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("releaseHi","ReleaseHi",0.1f,10000.f,1.f));
    
    params.push_back( std::make_unique<AudioParameterFloat> ("signalGain","SignalGain",-12.f,12.f,0.f));
    params.push_back( std::make_unique<AudioParameterFloat> ("dryWet","DryWet",0.f,1.f,0.5f));
    
    params.push_back( std::make_unique<AudioParameterFloat>("lowMidF","LowMidF",250,1000,500));
    params.push_back( std::make_unique<AudioParameterFloat>("midHiF","MidHiF",1500,5000,3000));
    
    return {params.begin() , params.end() };
}

//==============================================================================
const juce::String MultiBandCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultiBandCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultiBandCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultiBandCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultiBandCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultiBandCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultiBandCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultiBandCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MultiBandCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultiBandCompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MultiBandCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    VU.setSampleRate(sampleRate);
    
    MBC.prepare(spec);
}

void MultiBandCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultiBandCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MultiBandCompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    MBC.tLow = *MBCstate.getRawParameterValue("threshLow");
    MBC.raLow = *MBCstate.getRawParameterValue("ratioLow");
    MBC.aLow = *MBCstate.getRawParameterValue("attackLow");
    MBC.reLow = *MBCstate.getRawParameterValue("releaseLow");
    
    MBC.tMid = *MBCstate.getRawParameterValue("threshMid");
    MBC.raMid = *MBCstate.getRawParameterValue("ratioMid");
    MBC.aMid = *MBCstate.getRawParameterValue("attackMid");
    MBC.reMid = *MBCstate.getRawParameterValue("releaseMid");
    
    MBC.tHi = *MBCstate.getRawParameterValue("threshHi");
    MBC.raHi = *MBCstate.getRawParameterValue("ratioHi");
    MBC.aHi = *MBCstate.getRawParameterValue("attackHi");
    MBC.reHi = *MBCstate.getRawParameterValue("releaseHi");
    
    MBC.gain = *MBCstate.getRawParameterValue("signalGain");
    MBC.dryWet = *MBCstate.getRawParameterValue("dryWet");
    MBC.lowMidF = *MBCstate.getRawParameterValue("lowMidF");
    MBC.midHiF = *MBCstate.getRawParameterValue("midHiF");

    
    MBC.processBlock(buffer,spec.sampleRate);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        for (int n = 0; n < buffer.getNumSamples(); n++){
            lowMeterVal = MBC.getMeterVal(MBC.lowBuffer, channel, n);
            midMeterVal = MBC.getMeterVal(MBC.midBuffer, channel, n);
            hiMeterVal = MBC.getMeterVal(MBC.hiBuffer, channel, n);
            gainMeterVal = MBC.getMeterVal(buffer, channel, n);
        }
    }
}

//==============================================================================
bool MultiBandCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MultiBandCompressorAudioProcessor::createEditor()
{
    return new MultiBandCompressorAudioProcessorEditor (*this);
}

//==============================================================================
void MultiBandCompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
//    std::unique_ptr<XmlElement> xml (new XmlElement("MBCGeneralParameters") );
//    xml->setAttribute("gain", (double) *MBC.gain);
////    xml->setAttribute("lowMidF", (double) *MBC.lowMidF);
//    copyXmlToBinary(*xml, destData);
    auto currentState = MBCstate.copyState();
    std::unique_ptr<XmlElement> xml (currentState.createXml());
    copyXmlToBinary(*xml, destData);
}

void MultiBandCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
//    std::unique_ptr<XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
//    if (xml != nullptr){
//        if (xml->hasTagName("MBCGeneralParameters")){
//            *MBC.gain = xml->getDoubleAttribute("gain",0.f);
////            *MBC.lowMidF = xml->getDoubleAttribute("lowMidF",0.f);
//        }
//    }
    std::unique_ptr<XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    if (xml && xml->hasTagName("MBCParams")){
        MBCstate.replaceState(ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultiBandCompressorAudioProcessor();
}
