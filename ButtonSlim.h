// -----
// ButtonSlim.h - Library for detecting and debouncing a button press on a single button.
// This class is implemented for use with the Arduino environment.
// by MrAlvin -  alvin@3iii.dk - Initial: Jan 2016 - Trimmed: May 2023
//
// ButtonSlim is inspired by OneButton ground work, done by Matthias Hertel, http://www.mathertel.de
// -----

#ifndef Button_Slim_h
#define Button_Slim_h

#include "Arduino.h"

// ----- Callback function types -----

extern "C" {
  typedef void (*callbackFunction)(void);
}


class ButtonSlim
{
public:
  // ----- Constructor -----
  ButtonSlim(byte pin);
  ButtonSlim(uint8_t pin, bool state) ;
    
  // ----- Set runtime parameters -----
  void begin(void) ;
  void setDebounceTime(int ms_ticks);    // set # of millisec that have to pass before we test to see if the button state has changed
  void setActiveState(bool state);     // choose if LOW or HIGH is the active state of the push button
  void currentStateIsInactiveState(void);  // read current state of button, and set it to be the inacive state
  
  // attach functions that will be called when button was pressed
  void attachPress(callbackFunction newFunction);     // called when ever a button is pressed
      
  // ----- State machine functions -----

  // call this function every some milliseconds for handling button events.
  bool check(void); // needs to be called often to allow all states of the button to be processed
  
  // hardware detached button state evaluation and debounce machine  
 void buttonEvaluate(boolean buttonLevel);  
 
private:
  uint8_t _pin;        // hardware pin number. 
  int _debounceTime;   // number of milli seconds that have to pass  before we test to see if the button state has changed
  bool _active_state;         // when reading this state,  we register a push of the button
  bool _btnEngagedState;         // true - when a push has been detected : false - when a release has been detected
  

  // These variables will hold functions acting as event source.
  callbackFunction _pressFunction;
  
  // These variables that hold information across the upcoming check calls.
  // They are initialized once on program start and are updated every time the check function is called.
  uint8_t _state_idx;    // index in the state machine
  unsigned long  _btn_millis;    // time in milli seconds.
};

#endif


