#include "Arduino.h"
#include "Controller.h"
#include "MidiController.h"
#include "MidiOutIf.h"
#include "Log.h"
#include "Timer.h"


MidiController::MidiController() {}

void MidiController::OnReceiveCC() {
    DPRINTLN("MidiController::OnReceiveCC");
    #if DEBUG
        LogCC('R', Channel, CN, CV);
    #endif
}


void MidiController::OnReceivePC() {
    DPRINTLN("MidiController::OnReceivePC");
    #if DEBUG
        LogPC('R', Channel, PN);
    #endif
}


void MidiController::OnReceiveNoteOn() {
    DPRINTLN("MidiController::OnReceiveNoteOn");
    #if DEBUG
        LogNoteOn('R', Channel, Note, Velocity);
    #endif
}


void MidiController::OnReceiveNoteOff() {
    DPRINTLN("MidiController::OnReceiveNoteOff");
    #if DEBUG
        LogNoteOff('R', Channel, Note);
    #endif
}


void MidiController::OnReceiveAftertouch() {
    DPRINTLN("MidiController::OnReceiveAftertouch");
    #if DEBUG
        LogAftertouch('R', Channel, Note, Velocity);
    #endif
}


void MidiController::OnReceivePitchbend() {
    DPRINTLN("MidiController::OnReceivePitchbend");
    #if DEBUG
        LogPitchbend('R', Channel, PitchbendLsb, PitchbendMsb);
    #endif
}


void MidiController::OnResetCtrl() {
    // MidiOutIf::CC(Com, Channel, CN, CV);
    // MidiOutIf::PC(Com, Channel, 0);
    
    // DPRINTLN("MidiController::OnResetCtrl");
}


void MidiController::Invoke() {
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
    // DPRINTLN("MidiController::Invoke");
}
