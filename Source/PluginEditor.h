/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class Midi2oscAudioProcessorEditor  : public AudioProcessorEditor, public TextEditor::Listener
{
public:
    Midi2oscAudioProcessorEditor (Midi2oscAudioProcessor&);
    ~Midi2oscAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void textEditorReturnKeyPressed (TextEditor& textEditor) override;

private:
    Midi2oscAudioProcessor& _processor;
    TextEditor _remoteHostTextEditor, _remotePortTextEditor, _trackIdentifierTextEditor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Midi2oscAudioProcessorEditor)
};
