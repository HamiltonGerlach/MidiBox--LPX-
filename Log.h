#ifndef LOG_H
#define LOG_H

#include "Arduino.h"
#include "MidiBox.h"

void Log(byte x);
void Log(int x);

void LogCC(char Direction, byte Channel, byte CN, byte CV);
void LogPC(char Direction, byte Channel, byte PN);
void LogNoteOn(char Direction, byte Channel, byte Note, byte Velocity);
void LogNoteOff(char Direction, byte Channel, byte Note);
void LogAftertouch(char Direction, byte Channel, byte Note, byte Velocity);
void LogPitchbend(char Direction, byte Channel, byte Lsb, byte Msb);
void LogPitchbendSingle(char Direction, byte Channel, int Bend);

#if DEBUG
// examples of use:
//
// DPRINTLN("Testing123");   
// DPRINTLN(0xC0FFEEul,DEC);
// DPRINTLN(12648430ul,HEX);
// DPRINT(myVariable);

#define DPRINT(...)     Serial.print(__VA_ARGS__)
#define DPRINTLN(...)   Serial.println(__VA_ARGS__)
#define DPRINTF(...)    Serial.print(F(__VA_ARGS__))
#define DPRINTLNF(...)  Serial.println(F(__VA_ARGS__))
#define DWRITE(...)     Serial.write(__VA_ARGS__)
#define DBEGIN(...)     Serial.begin(__VA_ARGS__)

#else

#define DPRINT(...)     // blank line
#define DPRINTLN(...)   // blank line
#define DPRINTF(...)    // blank line
#define DPRINTLNF(...)  // blank line
#define DWRITE(...)     // blank line
#define DBEGIN(...)     // blank line

#endif

#endif
