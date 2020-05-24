#ifndef RANGE_H
#define RANGE_H

#include "Timer.h"

Timer tm;

class Range{
  enum SensorStates{
    TRIG_LOW,
    TRIG_HIGH,
    ECHO_HIGH 
  };

  SensorStates  _sensorState = TRIG_LOW;

  int _TrigPin;
  int _EchoPin;
  int _triggerHigh = 10;
  int _timerLow = 2;
  
  private:
    float _timeDuration, _distance;
 
    void trigStateLOW() {
      digitalWrite(_TrigPin, LOW);
    }
    void trigStateHIGH() {
      digitalWrite(_TrigPin, HIGH);
    }

  public:

    Range(int TRIG_PIN,int ECHO_PIN){
      _TrigPin = TRIG_PIN;
      _EchoPin = ECHO_PIN;
      pinMode(_TrigPin, OUTPUT);
      pinMode(_EchoPin, INPUT);
    }

    float sensorRange() {
      switch (_sensorState) {
        case TRIG_LOW: {
            trigStateLOW();
            tm.startTimer();
            if (tm.isTimerReady(_timerLow)) {
              _sensorState = TRIG_HIGH;
            }
          } break;
 
        case TRIG_HIGH: {
            trigStateHIGH();
            tm.startTimer();
            if (tm.isTimerReady(_triggerHigh)) {
              _sensorState = ECHO_HIGH;
            }
          } break;
 
        case ECHO_HIGH: {
            trigStateLOW();
            _timeDuration = pulseIn(_EchoPin, HIGH);
            _sensorState = TRIG_LOW;
            return (_timeDuration * 0.034 / 2);
          } break;
 
      }
    }

};

#endif
