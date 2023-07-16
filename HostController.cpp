#include "Arduino.h"
#include "Controller.h"
#include "HostController.h"
#include "MidiOutIf.h"
#include "Log.h"
#include "Timer.h"
#include <math.h>


HostController::HostController() {}

void HostController::OnReceiveCC() {
    DPRINTLN("HostController::OnReceiveCC");
    #if DEBUG
        LogCC('R', Channel, CN, CV);
    #endif
    
    if (CN > 0) {
        if (CN == 127)
        {
            if (CV > 0)
            {
                // KILL ALL NOTES
                for (byte n = 0; n <= 127; n++)
                {
                    MidiOutIf::NoteOff(Com, Channel, n);
                    delayMicroseconds(50);
                }
            }
        }
        else
        {
            MidiOutIf::CC(Com, Channel, CN, CV);
        }
    }
    else {
        int pbInt = (int)((CV / 127.0) * 16383.0) << 1;
        byte PitchbendLsb = highByte(pbInt);
        byte PitchbendMsb = lowByte(pbInt) >> 1;
        MidiOutIf::Pitchbend(Com, Channel, PitchbendLsb, PitchbendMsb);
    }
}


void HostController::OnReceivePC() {
    DPRINTLN("HostController::OnReceivePC");
    #if DEBUG
        LogPC('R', Channel, PN);
    #endif
    MidiOutIf::PC(Com, Channel, PN);
}


void HostController::OnReceiveNoteOn() {
    DPRINTLN("HostController::OnReceiveNoteOn");
    #if DEBUG
        LogNoteOn('R', Channel, Note, Velocity);
    #endif

    if (Velocity > 0)
    {
        MidiOutIf::NoteOn(Com, Channel, Note, 127);
    }
    else
    {
        MidiOutIf::NoteOff(Com, Channel, Note);
    }
}


void HostController::OnReceiveNoteOff() {
    DPRINTLN("HostController::OnReceiveNoteOff");
    #if DEBUG
        LogNoteOff('R', Channel, Note);
    #endif
    
    MidiOutIf::NoteOff(Com, Channel, Note);
}


void HostController::OnReceiveAftertouch() {
    DPRINTLN("HostController::OnReceiveAftertouch");
    #if DEBUG
        LogAftertouch('R', Channel, Note, Velocity);
    #endif

    if (Velocity > 0)
    {
        // MidiOutIf::NoteOn(Com, Channel, Note, Velocity);
    }
    else
    {
        //MidiOutIf::NoteOff(Com, Channel, Note);
    }
}


void HostController::OnReceivePitchbend() {
    DPRINTLN("HostController::OnReceivePitchbend");
    #if DEBUG
        LogPitchbend('R', Channel, PitchbendLsb, PitchbendMsb);
    #endif

    MidiOutIf::Pitchbend(Com, Channel, PitchbendLsb, PitchbendMsb);
}





void HostController::OnResetCtrl() {
    // MidiOutIf::PC(Com, Channel, 0);
    
    // DPRINTLN("HostController::OnResetCtrl");
}


void HostController::Invoke() {
  // if (IsRamping)
  // {    
  //   if (Gate.Check(IRIDIUM_RAMP_GATE_MS))
  //   {
  //     unsigned long DeltaT = millis() - Clock.TimerStart;
  //     float FacT = ((float)DeltaT / (float)IRIDIUM_RAMP_GRAD_MS);
  //     float CV = ValueStart + FacT * (ValueEnd - ValueStart);
  // 
  //     ValueCurrent = CV;
  // 
  //     if (((RampDirection == 1) && (ValueCurrent >= ValueEnd)) || 
  //        ((RampDirection == -1) && (ValueCurrent <= ValueEnd)) ||
  //        (ValueCurrent < 0) || (ValueCurrent > 127))
  //     {
  //       ValueCurrent = ValueEnd;
  //       IsRamping = false;
  //     }
  // 
  //     if ((ValueCurrent != ValueStart) && (ValueCurrent != ValuePrev))
  //     {
  //       MidiOutIf::CC(Com, Channel, RampParameter, ValueCurrent);
  //       ValuePrev = ValueCurrent;
  //     }
  // 
  //     Gate.Reset();
  //   }
  // 
  // }
    DPRINTLN("HostController::Invoke");
}
