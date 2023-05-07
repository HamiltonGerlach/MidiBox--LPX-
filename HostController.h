#ifndef HOSTCTRL_H
#define HOSTCTRL_H

#include "Controller.h"
#include "MidiBox.h"
#include "Timer.h"
#include "State.h"


class HostController : public Controller
{
private:
    Timer Clock, Gate;
    
    byte ValueStart, ValueEnd, ValueCurrent, ValuePrev;
    byte RampParameter, RampDirection;
    bool IsRamping;
        
public:    
    void OnReceiveCC();
    void OnReceivePC();
    void OnReceiveNoteOn();
    void OnReceiveNoteOff();
    void OnReceiveAftertouch();
    void OnReceivePitchbend();
    
    void OnResetCtrl();
    
    void Invoke();
    
    HostController();
};

#endif
