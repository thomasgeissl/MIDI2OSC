/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Midi2oscAudioProcessorEditor::Midi2oscAudioProcessorEditor (Midi2oscAudioProcessor& p)
    : AudioProcessorEditor (&p), _processor (p)
{
    setOpaque (true);
    addAndMakeVisible (_remoteHostTextEditor);
    addAndMakeVisible (_remotePortTextEditor);
    addAndMakeVisible (_remotePortTextEditor);
    
    _remoteHostTextEditor.addListener(this);
    _remoteHostTextEditor.setInputRestrictions(15, "0123456789.");
    _remoteHostTextEditor.setReturnKeyStartsNewLine(false);
    _remoteHostTextEditor.setText("127.0.0.1");
    _remoteHostTextEditor.unfocusAllComponents();
    
    
    _remotePortTextEditor.addListener(this);
    _remotePortTextEditor.setInputRestrictions(5, "0123456789");
    _remotePortTextEditor.setReturnKeyStartsNewLine(false);
    _remotePortTextEditor.setText("9001");
    _remotePortTextEditor.unfocusAllComponents();
    
    _trackIdentifierTextEditor.addListener(this);
    _trackIdentifierTextEditor.setReturnKeyStartsNewLine(false);
    _trackIdentifierTextEditor.setText("replaceThisUntilICanCaptureTheTrackName");
    _trackIdentifierTextEditor.unfocusAllComponents();
    setSize (400, 300);
}

Midi2oscAudioProcessorEditor::~Midi2oscAudioProcessorEditor()
{
}

//==============================================================================
void Midi2oscAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void Midi2oscAudioProcessorEditor::resized()
{
    Rectangle<int> r = getLocalBounds();
    _remoteHostTextEditor.setBounds(r.removeFromTop (25));
    _remotePortTextEditor.setBounds(r.removeFromTop (25));
    _trackIdentifierTextEditor.setBounds(r.removeFromTop (50));
    
}

void Midi2oscAudioProcessorEditor::textEditorReturnKeyPressed (TextEditor & textEditor){
    textEditor.unfocusAllComponents();
    _processor.connect(_remoteHostTextEditor.getText(), _remotePortTextEditor.getText().getIntValue());
}
