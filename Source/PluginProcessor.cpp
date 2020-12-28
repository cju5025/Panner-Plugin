/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Panner01AudioProcessor::Panner01AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(mTimeParameter = new AudioParameterFloat("time", "Time", 1.f, 10000.f, 1000.f));
}

Panner01AudioProcessor::~Panner01AudioProcessor()
{
}

//==============================================================================
const juce::String Panner01AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Panner01AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Panner01AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Panner01AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Panner01AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Panner01AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Panner01AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Panner01AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Panner01AudioProcessor::getProgramName (int index)
{
    return {};
}

void Panner01AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Panner01AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Panner01AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Panner01AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Panner01AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto* channelDataLeft = buffer.getWritePointer(0);
    auto* channelDataRight = buffer.getWritePointer(1);
    
    float time = mTimeParameter->get() / 1000;
    
    int numberOfSamples = getSampleRate() * time;
    const float radiansPerSample = (2 * double_Pi) / numberOfSamples;
    
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        auto inputLeft = channelDataLeft[i];
        auto inputRight = channelDataRight[i];
        
//        float sinValue = 0.5 * std::sin(nextRadian) + 0.5;
//
//        inputLeft *= (1 - sinValue);
//        inputRight *= sinValue;
        
        float sinValue = std::sin(nextRadian) + 1;
        sinValue = (sinValue * double_Pi) / 4;
        
        inputLeft *= cos(sinValue);
        inputRight *= sin(sinValue);
        
        channelDataLeft[i] = inputLeft;
        channelDataRight[i] = inputRight;
        
        nextRadian += radiansPerSample;
    }
    if (nextRadian > numberOfSamples)
    {
        nextRadian = 0;
    }
}

//==============================================================================
bool Panner01AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Panner01AudioProcessor::createEditor()
{
    return new Panner01AudioProcessorEditor (*this);
}

//==============================================================================
void Panner01AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Panner01AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Panner01AudioProcessor();
}
