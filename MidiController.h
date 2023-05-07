#ifndef MIDICTRL_H
#define MIDICTRL_H

#include "Controller.h"
#include "MidiBox.h"
#include "Timer.h"
#include "State.h"

#define MOOD_CN_TBL_LEN      8
#define MOOD_CN_VOLUME       7
#define MOOD_CN_LEVEL        12
#define MOOD_CN_DRIVE        13
#define MOOD_CN_BASS         14
#define MOOD_CN_MID          15
#define MOOD_CN_TREBLE       16
#define MOOD_CN_ROOM         17
#define MOOD_CN_EXPRESSION   100

#define MOOD_PN_FORCE_PATCH  126
#define MOOD_PN_MANUAL_MODE  127

#define MOOD_CUSTOM_MSG_NUM  10

#define MOOD_RAMP_GRAD_MS    100
#define MOOD_RAMP_GATE_MS    10


namespace Mood {
    const PROGMEM byte ParamTable[] =
        {   MOOD_CN_VOLUME, MOOD_CN_LEVEL, MOOD_CN_DRIVE,
            MOOD_CN_BASS, MOOD_CN_MID, MOOD_CN_TREBLE,
            MOOD_CN_ROOM, MOOD_CN_EXPRESSION  };
    
    enum StateMode {
        None        = 0,
        PatchChange = BIT(0),
        ParamChange = BIT(1),
        ManualMode  = BIT(2),
        CustomMsg   = BIT(3),
        ForcePatch  = BIT(4)
    };
    
    typedef struct Parameters {
        byte Patch      = CONTROL_BYTE;
        byte Level      = CONTROL_BYTE;
        byte Drive      = CONTROL_BYTE;
        byte Bass       = CONTROL_BYTE;
        byte Mid        = CONTROL_BYTE;
        byte Treble     = CONTROL_BYTE;
        byte Room       = CONTROL_BYTE;
        byte Expression = CONTROL_BYTE;
        byte Volume     = CONTROL_BYTE;
        
        Parameters() :
            Patch(CONTROL_BYTE),
            Volume(CONTROL_BYTE),
            Level(CONTROL_BYTE),
            Drive(CONTROL_BYTE),
            Bass(CONTROL_BYTE),
            Mid(CONTROL_BYTE),
            Treble(CONTROL_BYTE),
            Room(CONTROL_BYTE),
            Expression(CONTROL_BYTE) {}
    };
}


class MidiController : public Controller
{
private:
    Timer Clock, Gate;
    
    byte ValueStart, ValueEnd, ValueCurrent, ValuePrev;
    byte RampParameter, RampDirection;
    bool IsRamping;
        
public:
    byte CustomMsgIdx;
    
    _customMsg CustomMessage[MOOD_CUSTOM_MSG_NUM] =
        { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    
    Mood::Parameters Param;    
    Mood::StateMode State = Mood::StateMode::None;
    
    void OnReceiveCC();
    void OnReceivePC();
    void OnReceiveNoteOn();
    void OnReceiveNoteOff();
    void OnReceiveAftertouch();
    void OnReceivePitchbend();
    
    void OnResetCtrl();
    
    void Invoke();
    
    MidiController();
};

#endif
