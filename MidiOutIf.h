#ifndef MIDIOUTIF_H
#define MIDIOUTIF_H

#include "Arduino.h"

class MidiOutIf
{
  public:
    static void PC(Stream *Com, byte Channel, byte PN);
    static void CC(Stream *Com, byte Channel, byte CN, byte CV);
    static void NoteOn(Stream *Com, byte Channel, byte Note, byte Velocity);
    static void NoteOff(Stream *Com, byte Channel, byte Note);
    static void NoteAftertouch(Stream *Com, byte Channel, byte Note, byte Velocity);
    static void Pitchbend(Stream *Com, byte Channel, byte Lsb, byte Msb);
    
  private:
    MidiOutIf();
};

#endif
