#ifndef TIMER_H
#define TIMER_H
class Timer {
  private:
    unsigned long _timerStart = 0;
 
  public:
    void startTimer() {
      _timerStart = millis();
    }
 
    bool isTimerReady(int _mSec) {
      return (millis() - _timerStart) < _mSec;
    }
 
    bool isTimeForLoop(int _mSec) {
      return (millis() - _timerStart) > _mSec;
    }
};
 
#endif
