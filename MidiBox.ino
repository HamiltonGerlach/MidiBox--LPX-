#include "MidiBox.h"
#include "Log.h"
#include "MidiOutIf.h"
#include "Timer.h"
#include <MIDI.h>

#include <midi_Defs.h>

MIDI_CREATE_DEFAULT_INSTANCE()

byte rampMode;
bool rampActive = false;
int delta, count;
byte destination, source;
byte lastMixVal, prev;

// GLOBALS
Timer Clock;
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
    
    if ((channel == 2) && (number == 15))
    {
        lastMixVal = value; prev = value;
        rampActive = false;
    }
}
void handleProgramChange(byte channel, byte number)
{
    MidiOutIf::PC(&MIDI_STREAM, channel, number);
    
    if (channel == 16)
    {
         switch (number)
        {
            case 120:
                rampMode = 1;
                rampActive = true;
                delta = 1;
                source = lastMixVal;
                count = lastMixVal;
                destination = 127;
                Clock.Reset();
                break;
            case 121:
                rampMode = 1;
                rampActive = true;
                delta = 4;
                source = lastMixVal;
                count = lastMixVal;
                destination = 127;
                Clock.Reset();
                break;
            case 122:
                rampMode = 1;
                rampActive = true;
                delta = 8;
                source = lastMixVal;
                count = lastMixVal;
                destination = 127;
                Clock.Reset();
                break;
            case 123:
                MIDI.sendControlChange(68, 0, 1);
                MidiOutIf::CC(&MIDI_STREAM, 1, 68, 0);
                rampMode = 2;
                rampActive = true;
                delta = -1;
                destination = prev;
                source = lastMixVal;
                count = lastMixVal;
                Clock.Reset();
                break;
            case 124:
                MIDI.sendControlChange(68, 0, 1);
                MidiOutIf::CC(&MIDI_STREAM, 1, 68, 0);
                rampMode = 2;
                rampActive = true;
                delta = -4;
                destination = prev;
                source = lastMixVal;
                count = lastMixVal;
                Clock.Reset();
                break;
            case 125:
                MIDI.sendControlChange(68, 0, 1);
                MidiOutIf::CC(&MIDI_STREAM, 1, 68, 0);
                rampMode = 2;
                rampActive = true;
                delta = -8;
                destination = prev;
                source = lastMixVal;
                count = lastMixVal;
                Clock.Reset();
                break;
        }
    }
    
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
void handleAfterTouchChannel(byte channel, byte pressure) { return; }
void handleAfterTouchPoly(byte channel, byte note, byte pressure) { return; }


// MAIN INIT FUNCTION
void setup() {
    MIDI_STREAM.begin(MIDI_BAUDRATE);    // MIDI In/Out           <- send to HX stomp via MIDI Out
    MIDI_STREAM.flush();
    
    MIDI.begin(MIDI_CHANNEL_OMNI);
    
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandleControlChange(handleControlChange);
    MIDI.setHandleProgramChange(handleProgramChange);
    MIDI.setHandlePitchBend(handlePitchBend);
    MIDI.setHandleAfterTouchPoly(handleAfterTouchPoly);
    MIDI.setHandleAfterTouchChannel(handleAfterTouchChannel);
    
    Clock.Reset();
    DBEGIN(DEBUG_BAUDRATE);              // Debug Out
}


// MAIN LOOP FUNCTION
void loop() {
    // Update buffer
    MIDI.read();
    // if (Clock.Check(RAMP_DT * 50))
    // {
    //     Clock.Reset();
    //     Serial.write((byte)0xB1);     
    //     Serial.write((byte)18);
    //     Serial.write((byte)random(0, 127));
    // }
    //MIDI.sendControlChange(18, random(0, 127), 16);
    
    if (rampActive)
    {
        if ( ((rampMode == 1) && (count > destination)) || ((rampMode == 2) && (count < destination)) )
        {
            rampActive = false;
            if (rampMode == 1)
            {
                MIDI.sendControlChange(68, 127, 1);
                MidiOutIf::CC(&MIDI_STREAM, 1, 68, 127);
            }
            MIDI.sendControlChange(15, destination, 1);
            MidiOutIf::CC(&MIDI_STREAM, 2, 15, destination);
            lastMixVal = destination;
        }
        else {
            if (Clock.Check(RAMP_DT)) {
                Clock.Reset();
                count = count + delta;
                lastMixVal = count;
                if ( ((rampMode == 1) && (count > destination)) || ((rampMode == 2) && (count < destination)) )
                {
                    rampActive = false;
                    if (rampMode == 1)
                    {
                        MIDI.sendControlChange(68, 127, 1);
                        MidiOutIf::CC(&MIDI_STREAM, 1, 68, 127);
                    }
                    MIDI.sendControlChange(15, destination, 1);
                    MidiOutIf::CC(&MIDI_STREAM, 2, 15, destination);
                    lastMixVal = destination;
                }
                else
                {
                    MIDI.sendControlChange(15, count, 1);
                    MidiOutIf::CC(&MIDI_STREAM, 2, 15, count);
                }
            }
        }
    }
    
    // Invoke controller ramping / background tasks
    // CtrlMIDI.Invoke();
} 
