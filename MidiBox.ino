#include "MidiBox.h"
#include "Log.h"
#include "MidiController.h"
#include "HostController.h"
#include "MidiBuffer.h"
#include "Timer.h"

// GLOBALS
Timer Clock;

// MidiController CtrlMIDI;
HostController CtrlHOST;

MIDI_SERIAL MIDI_STREAM = MIDI_SERIAL(MIDI_SERIAL_RX, MIDI_SERIAL_TX);
HOST_SERIAL HOST_STREAM = HOST_SERIAL(HOST_SERIAL_RX, HOST_SERIAL_TX);


// MAIN INIT FUNCTION
void setup() {  
    MIDI_STREAM.begin(MIDI_BAUDRATE);    // MIDI In/Out           <- send to HX stomp via MIDI Out
    MIDI_STREAM.flush();

    HOST_STREAM.begin(HOST_BAUDRATE);    // USB Host MIDI out     -> receive from Launchpad X via USB MIDI In
    HOST_STREAM.flush();

    DBEGIN(DEBUG_BAUDRATE);              // Debug Out
    CtrlHOST.Init(&MIDI_STREAM, HOST_CHANNEL); // CtrlMIDI.Init(&MIDI_STREAM, MIDI_CHANNEL);
}


// MAIN LOOP FUNCTION
void loop() {
    // Update buffer
    while ((HOST_STREAM.available() > 0) && CtrlHOST.RxActive)
    {
        MidiBuffer::Push(HOST_STREAM.read());
        CtrlHOST.Update(); // CtrlMIDI.Update();
    }
    
    // State check and sending routine
    if (CtrlHOST.Done()) {
        DPRINTLN("---------------------------------------------------------");
        CtrlHOST.OnSend(); CtrlHOST.Reset(); // CtrlMIDI.OnSend(); // CtrlMIDI.Reset();
        MidiBuffer::Flush();
    }
  
    // Invoke controller ramping / background tasks
    // CtrlMIDI.Invoke();
}
