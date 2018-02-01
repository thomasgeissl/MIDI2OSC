# MIDI2OSC
## description
MIDI2OSC is an audio plugin written with juce. It converts incomming midi messages to OSC messages. 

## usage
### installation
Download the plugin from the releases tab and copy the audio uni (MIDI2OSC.component) to your mac's audio unit directory (/Library/Audio/Plug-Ins/Components).

### DAW
Make sure your DAW finds the plugin. Drag it then to one of your tracks. Then set the remote hosts ip and port. By default it sends to localhost:9001.

Unfortunately midi effects are not supported very well.
This plugin is implemented as an instrument, but it does not generate audio. It cannot be placed infront of an instruments. 

One way to use this plugin is to combine it in an instrument rack with an actual tone generating instrument.