#include "MidiBox.h"
#include "Log.h"
#include "MidiController.h"
#include "HostController.h"
#include "MidiOutIf.h"
#include "MidiBuffer.h"
#include "Timer.h"
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE()
#define DLY 50
// GLOBALS
Timer Clock;
HostController CtrlHOST1, CtrlHOST2;
// MidiController CtrlMIDI;

MIDI_SERIAL MIDI_STREAM = MIDI_SERIAL(MIDI_SERIAL_RX, MIDI_SERIAL_TX);
//HOST_SERIAL HOST_STREAM = HOST_SERIAL(HOST_SERIAL_RX, HOST_SERIAL_TX);


void handleNoteOff(byte channel, byte note, byte velocity)
{
    MidiOutIf::NoteOff(&MIDI_STREAM, channel, note);
    delayMicroseconds(DLY);
}
void handleNoteOn(byte channel, byte note, byte velocity)
{
    MidiOutIf::NoteOn(&MIDI_STREAM, channel, note, velocity);
    delayMicroseconds(DLY);
}

void handleControlChange(byte channel, byte number, byte value)
{
    MidiOutIf::CC(&MIDI_STREAM, channel, number, value);
    delayMicroseconds(DLY);
}
void handleProgramChange(byte channel, byte number)
{
    MidiOutIf::PC(&MIDI_STREAM, channel, number);
    delayMicroseconds(DLY);
}
void handlePitchBend(byte channel, int bend)
{
    int pbInt = (int)((bend / 127.0) * 16383.0) << 1;
    byte PitchbendLsb = highByte(pbInt);
    byte PitchbendMsb = lowByte(pbInt) >> 1;
    MidiOutIf::Pitchbend(&MIDI_STREAM, channel, PitchbendLsb, PitchbendMsb);
    delayMicroseconds(DLY);
}
void handleAfterTouchChannel(byte channel, byte pressure)
{
    LogAftertouch('R', channel, 0, pressure);
}
void handleAfterTouchPoly(byte channel, byte note, byte pressure)
{
    LogAftertouch('R', channel, note, pressure);
}


// MAIN INIT FUNCTION
void setup() {  
    MIDI_STREAM.begin(MIDI_BAUDRATE);    // MIDI In/Out           <- send to HX stomp via MIDI Out
    MIDI_STREAM.flush();
    
    MIDI.begin(MIDI_CHANNEL_OMNI);
    
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandleAfterTouchPoly(handleAfterTouchPoly);
    MIDI.setHandleAfterTouchChannel(handleAfterTouchChannel);
    MIDI.setHandleControlChange(handleControlChange);
    MIDI.setHandleProgramChange(handleProgramChange);
    MIDI.setHandlePitchBend(handlePitchBend);
}


// MAIN LOOP FUNCTION
void loop() {
    // Update buffer
    MIDI.read();
    /*
    while ((HOST_STREAM.available() > 0))
    {
        byte B = HOST_STREAM.read();
        if (B > 127) { Serial.println(' '); }
        Serial.print(B, HEX); Serial.print(' ');
        MidiBuffer::Push(B);
        CtrlHOST1.Update();
        CtrlHOST2.Update();
        
        if (CtrlHOST1.Done())
        {
            CtrlHOST1.OnSend(); CtrlHOST1.Reset(); MidiBuffer::Flush();
        }
        if (CtrlHOST2.Done())
        {
            CtrlHOST2.OnSend(); CtrlHOST2.Reset(); MidiBuffer::Flush();
        }
    }
    while ((HOST_STREAM.available() > 0))
    {
        byte B = HOST_STREAM.read();
        if (B > 127) { Serial.println(' '); Serial.print(B, HEX); }
        else { Serial.print(B); }
        Serial.print(' ');
    }
    
    if (midiAvailable)
    {
        Serial.println(' ');
        Serial.print(byte1, HEX); Serial.print(' ');
        Serial.print(byte2, HEX); Serial.print(' ');
        Serial.print(byte3, HEX); Serial.print(' ');
        midiAvailable = false;
        
        // MidiBuffer::Push(B);
        // CtrlHOST1.Update();
        // CtrlHOST2.Update();
        
        if (CtrlHOST1.Done())
        {
            CtrlHOST1.OnSend(); CtrlHOST1.Reset(); MidiBuffer::Flush();
        }
        if (CtrlHOST2.Done())
        {
            CtrlHOST2.OnSend(); CtrlHOST2.Reset(); MidiBuffer::Flush();
        }
    }
    
    
    bool anyDone = false;
    if (CtrlHOST1.Done()) {
        DPRINTLN(" ");
        DPRINTLN("---------------------- HOST 1 -------------------------");
        CtrlHOST1.OnSend(); CtrlHOST1.Reset();
        anyDone = true;
    }
    if (CtrlHOST2.Done()) {
        DPRINTLN(" ");
        DPRINTLN("---------------------- HOST 2 -------------------------");
        CtrlHOST2.OnSend(); CtrlHOST2.Reset();
        anyDone = true;
    }
    if (anyDone) { MidiBuffer::Flush(); }
    */
    
    // Invoke controller ramping / background tasks
    // CtrlMIDI.Invoke();
}