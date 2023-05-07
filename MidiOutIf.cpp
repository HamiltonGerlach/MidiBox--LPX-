#include "Arduino.h"
#include "MidiOutIf.h"
#include "MidiBox.h"
#include "Log.h"

void MidiOutIf::PC(Stream *Com, byte Channel, byte PN) {
    #if DEBUG
        LogPC('T', Channel, PN);
    #endif

    Com->write(0xC0 + Channel - 1);
    Com->write(PN);
}

void MidiOutIf::CC(Stream *Com, byte Channel, byte CN, byte CV) {
    #if DEBUG
        LogCC('T', Channel, CN, CV);
    #endif

    Com->write(0xB0 + Channel - 1);
    Com->write(CN);
    Com->write(CV);
}

void MidiOutIf::NoteOn(Stream *Com, byte Channel, byte Note, byte Velocity) {
    #if DEBUG
        LogNoteOn('T', Channel, Note, Velocity);
    #endif

    Com->write(0x90 + Channel - 1);
    Com->write(Note);
    Com->write(Velocity);
}

void MidiOutIf::NoteOff(Stream *Com, byte Channel, byte Note) {
    #if DEBUG
        LogNoteOff('T', Channel, Note);
    #endif

    Com->write(0x80 + Channel - 1);
    Com->write(Note);
    Com->write((byte)0x00);
}

void MidiOutIf::NoteAftertouch(Stream *Com, byte Channel, byte Note, byte Velocity) {
    #if DEBUG
        LogAftertouch('T', Channel, Note, Velocity);
    #endif

    Com->write(0xA0 + Channel - 1);
    Com->write(Note);
    Com->write(Velocity);
}


void MidiOutIf::Pitchbend(Stream *Com, byte Channel, byte Lsb, byte Msb) {
    #if DEBUG
        LogPitchbend('T', Channel, Lsb, Msb);
    #endif

    Com->write(0xE0 + Channel - 1);
    Com->write(Lsb);
    Com->write(Msb);
}