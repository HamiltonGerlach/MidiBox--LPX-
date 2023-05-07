#include "Arduino.h"
#include "Controller.h"
#include "MidiBuffer.h"
#include "MidiBox.h"
#include "Log.h"

Controller::Controller() {
    this->Reset();
}

void Controller::Init(Stream *Com, byte Channel)
{
    this->Com = Com;
    this->Channel = Channel;
}

void Controller::Update() {
    // Note On Message
    if (MidiBuffer::NoteOn(Channel)) {
        // DPRINTLN("NoteOn");
        RxStatus = BIT_SET(RxStatus, MidiMessage::NoteOn);
        
        Note = MidiBuffer::Data[1];
        Velocity = MidiBuffer::Data[2];
    }
    
    // Note Off Message
    if (MidiBuffer::NoteOff(Channel)) {
        // DPRINTLN("NoteOff");
        RxStatus = BIT_SET(RxStatus, MidiMessage::NoteOff);
        
        Note = MidiBuffer::Data[1];
        Velocity = MidiBuffer::Data[2];
    }
    
    // Aftertouch Message
    if (MidiBuffer::Aftertouch(Channel)) {
        // DPRINTLN("Aftertouch");
        RxStatus = BIT_SET(RxStatus, MidiMessage::Aftertouch);
        
        Note = MidiBuffer::Data[1];
        Velocity = MidiBuffer::Data[2];
    }
    
    // Pitchbend Message
    if (MidiBuffer::Pitchbend(Channel)) {
        // DPRINTLN("Pitchbend");
        RxStatus = BIT_SET(RxStatus, MidiMessage::Pitchbend);
        
        PitchbendLsb = MidiBuffer::Data[1];
        PitchbendMsb = MidiBuffer::Data[2];
    }
    
    // CC Message
    if (MidiBuffer::CC(Channel)) {
        // DPRINTLN("CC");
        RxStatus = BIT_SET(RxStatus, MidiMessage::CC);
        
        CN = MidiBuffer::Data[1];
        CV = MidiBuffer::Data[2];
    }
    
    // PC Message
    if (!BIT_CHECK(RxStatus, MidiMessage::PC)) {
        PN = MidiBuffer::PC(Channel);
        if (PN < CONTROL_BYTE)
        {
            DPRINTLN("");
            DPRINTLN("");
            DPRINTLN("PC");
            DPRINTLN(PN);
            DPRINTLN("");
            RxStatus = BIT_SET(RxStatus, MidiMessage::PC);
        }
    }
  
}


void Controller::Reset() {
    this->OnResetCtrl();

    PN = 0;
    CN = 0;
    CV = 0;
    Note = 0;
    Velocity = 0;
    PitchbendLsb = 0;
    PitchbendMsb = 0;

    RxStatus = 0;
    RxActive = true;
}


bool Controller::Done() {
    return (RxStatus > 0) ? true : false;
}


void Controller::OnSend() {
    if (BIT_CHECK(RxStatus, MidiMessage::CC))           this->OnReceiveCC();
    if (BIT_CHECK(RxStatus, MidiMessage::PC))           this->OnReceivePC();
    if (BIT_CHECK(RxStatus, MidiMessage::NoteOn))       this->OnReceiveNoteOn();
    if (BIT_CHECK(RxStatus, MidiMessage::NoteOff))      this->OnReceiveNoteOff();
    if (BIT_CHECK(RxStatus, MidiMessage::Aftertouch))   this->OnReceiveAftertouch();
    if (BIT_CHECK(RxStatus, MidiMessage::Pitchbend))    this->OnReceivePitchbend();
}
