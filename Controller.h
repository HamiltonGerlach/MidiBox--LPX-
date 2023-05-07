#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"
#include "State.h"


enum MidiMessage {
    None        = 0,
    PC          = BIT(0),
    CC          = BIT(1),
    NoteOn      = BIT(2),
    NoteOff     = BIT(3),
    Aftertouch  = BIT(4),
    Pitchbend   = BIT(5)
};


// Controller struct
class Controller {
  public:
    byte Channel; // channel number
    
    byte PN; // program number
    byte CN; // controller number
    byte CV; // controller value
    byte Note; // note value
    byte Velocity; // velocity value
    byte PitchbendLsb; // pitchbend value lsb
    byte PitchbendMsb; // pitchbend value Msb
    
    byte RxStatus;
    bool RxActive;
    
    Stream *Com;    // serial port
    
    Controller();
    
    void Init(Stream *Com, byte Channel);
    
    void Update();
    void Reset();
    bool Done();
    
    void OnSend();
    
    virtual void OnReceiveCC() {};
    virtual void OnReceivePC() {};
    virtual void OnReceiveNoteOn() {};
    virtual void OnReceiveNoteOff() {};
    virtual void OnReceivePitchbend() {};
    virtual void OnReceiveAftertouch() {};
    virtual void OnResetCtrl() {};
};

typedef byte(*_customMsg)(Controller*, byte, byte, byte);

#endif
