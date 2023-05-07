#include "Arduino.h"
#include "Log.h"

void Log(byte x)    { DWRITE(x); }
void Log(int x)     { DWRITE(x); }

void LogCC(char Direction, byte Channel, byte CN, byte CV) {
    DPRINTLN("");
    DPRINT(Direction);
    DPRINTF("X: Channel ");
    DPRINT(Channel, DEC);
    DPRINTF(" CC ");
    DPRINT(CN, DEC);
    DPRINT(" ");
    DPRINTLN(CV, DEC);
}

void LogPC(char Direction, byte Channel, byte PN) {
    DPRINTLN("");
    DPRINT(Direction);
    DPRINTF("X: Channel ");
    DPRINT(Channel, DEC);
    DPRINTF(" PC ");
    DPRINTLN(PN, DEC);
}

void LogNoteOn(char Direction, byte Channel, byte Note, byte Velocity) {
    DPRINTLN("");
    DPRINT(Direction);
    DPRINTF("X: Channel ");
    DPRINT(Channel, DEC);
    DPRINTF(" Note On ");
    DPRINT(Note, DEC);
    DPRINTF(" vel: ");
    DPRINTLN(Velocity, DEC);
}

void LogNoteOff(char Direction, byte Channel, byte Note) {
    DPRINTLN("");
    DPRINT(Direction);
    DPRINTF("X: Channel ");
    DPRINT(Channel, DEC);
    DPRINTF(" Note Off ");
    DPRINTLN(Note, DEC);
}

void LogAftertouch(char Direction, byte Channel, byte Note, byte Velocity) {
    DPRINTLN("");
    DPRINT(Direction);
    DPRINTF("X: Channel ");
    DPRINT(Channel, DEC);
    DPRINTF(" Aftertouch ");
    DPRINT(Note, DEC);
    DPRINTF(" vel: ");
    DPRINTLN(Velocity, DEC);
}

void LogPitchbend(char Direction, byte Channel, byte Lsb, byte Msb) {
    DPRINTLN("");
    DPRINT(Direction);
    DPRINTF("X: Channel ");
    DPRINT(Channel, DEC);
    DPRINTF(" Pitchbend LSB: ");
    DPRINT(Lsb, DEC);
    DPRINTF(" MSB: ");
    DPRINTLN(Msb, DEC);
}