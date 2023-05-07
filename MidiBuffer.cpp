#include "Arduino.h"
#include "MidiBox.h"
#include "MidiBuffer.h"
#include "Log.h"

static byte MidiBuffer::Data[3];

MidiBuffer::MidiBuffer() { this->Flush(); }

void MidiBuffer::Push(byte In) {
    Data[0] = Data[1];
    Data[1] = Data[2];
    Data[2] = In;
}


bool MidiBuffer::CC(byte Channel) { 
    if ((Data[0] == (0xB0 + Channel - 1)) && (Data[1] <= 0x7F) && (Data[2] <= 0x7F)){
        return true;}
    else
        return false;
}


bool MidiBuffer::NoteOn(byte Channel) { 
    if ((Data[0] == (0x90 + Channel - 1)) && (Data[1] <= 0x7F) && (Data[2] <= 0x7F))
        return true;
    else
        return false;
}


bool MidiBuffer::NoteOff(byte Channel) { 
    if ((Data[0] == (0x80 + Channel - 1)) && (Data[1] <= 0x7F) && (Data[2] <= 0x7F))
        return true;
    else
        return false;
}


bool MidiBuffer::Aftertouch(byte Channel) { 
    if ((Data[0] == (0xA0 + Channel - 1)) && (Data[1] <= 0x7F) && (Data[2] <= 0x7F))
        return true;
    else
        return false;
}


bool MidiBuffer::Pitchbend(byte Channel) {
    if ((Data[0] == (0xE0 + Channel - 1)) && (Data[1] <= 0x7F) && (Data[2] <= 0x7F))
      return true;
    else
      return false;
}


byte MidiBuffer::PC(byte Channel) {
    byte Out = CONTROL_BYTE;

    if (    ((Data[0] == (0xC0 + Channel - 1)) && (Data[1] <= 0x7F)) ||
            ((Data[1] == (0xC0 + Channel - 1)) && (Data[2] <= 0x7F))    )
    {
        if (Data[0] == (0xC0 + Channel - 1)) {
            Out = Data[1];
            Data[0] = CONTROL_BYTE;
            Data[1] = CONTROL_BYTE;
        }
        else {
            Out = Data[2];
            Data[1] = CONTROL_BYTE;
            Data[2] = CONTROL_BYTE;
        }
    }

    return Out;
}


void MidiBuffer::Flush() {
    byte B = CONTROL_FLUSH ? CONTROL_BYTE : 0;
    Data[0] = B; Data[1] = B; Data[2] = B;
}
