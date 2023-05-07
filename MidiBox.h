#ifndef MIDIBOX_H
#define MIDIBOX_H

#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

#define DEBUG false                 // serial debug flag, set to false for normal operation

#define CONTROL_BYTE 0xFF
#define CONTROL_FLUSH true

#define MIDI_BAUDRATE 31250
#define HOST_BAUDRATE 31250
#define DEBUG_BAUDRATE 115200

#define MIDI_STREAM MIDI_S
#define MIDI_CHANNEL 2
#define MIDI_SERIAL AltSoftSerial

#define HOST_STREAM HOST_S
#define HOST_CHANNEL 1
#define HOST_SERIAL SoftwareSerial

#define HOST_SERIAL_RX 3
#define HOST_SERIAL_TX 2

#define MIDI_SERIAL_RX 12
#define MIDI_SERIAL_TX 11

#endif
