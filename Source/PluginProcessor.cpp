/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Midi2oscAudioProcessor::Midi2oscAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    _sender.connect("127.0.0.1", 9001);
}

Midi2oscAudioProcessor::~Midi2oscAudioProcessor()
{
}

//==============================================================================
const String Midi2oscAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Midi2oscAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Midi2oscAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Midi2oscAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Midi2oscAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Midi2oscAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Midi2oscAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Midi2oscAudioProcessor::setCurrentProgram (int index)
{
}

const String Midi2oscAudioProcessor::getProgramName (int index)
{
    return {};
}

void Midi2oscAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Midi2oscAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Midi2oscAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Midi2oscAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void Midi2oscAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    jassert (buffer.getNumChannels() == 0);
    
    int time;
    MidiMessage m;
    String type;
    
    
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        if (m.isNoteOn())
        {
            type = "noteOn";
        }
        else if (m.isNoteOff())
        {
            type = "noteOff";
        }
        else if (m.isAftertouch())
        {
            type = "aftertouch";

        }
        else if (m.isPitchWheel())
        {
            type = "pitchWheel";
        }
        if(type != ""){
            _sender.send("/"+getName()+"/TODO:trackName/"+type, m.getChannel(), m.getNoteNumber(), m.getVelocity());
        }
    }
}

//==============================================================================
bool Midi2oscAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Midi2oscAudioProcessor::createEditor()
{
    return new Midi2oscAudioProcessorEditor (*this);
}

//==============================================================================
void Midi2oscAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Midi2oscAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Midi2oscAudioProcessor();
}

bool Midi2oscAudioProcessor::connect(String address, int port){
    _sender.send("/"+getName()+"/info/connect", (int)(port));
    return _sender.connect(address, port);
}
