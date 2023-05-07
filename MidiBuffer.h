#ifndef MIDIBUFFER_H
#define MIDIBUFFER_H

#include "Arduino.h"

// Midi buffer
class MidiBuffer {
  public:
    static byte Data[3];
    
    static void Push(byte In);
    static byte PC(byte Channel);
    static bool CC(byte Channel);
    static bool NoteOn(byte Channel);
    static bool NoteOff(byte Channel);
    static bool Pitchbend(byte Channel);
    static bool Aftertouch(byte Channel);
    
    static void Flush();
  
  private:
    MidiBuffer();
};

#endif
