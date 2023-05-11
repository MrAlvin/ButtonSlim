// -----
// ButtonSlim.cpp - Library for detecting and debouncing a button press on a single button.
// This class is implemented for use with the Arduino environment.
// by MrAlvin -  alvin@3iii.dk - Initial: Jan 2016 - Trimmed: May 2023
//
// ButtonSlim is inspired by OneButton ground work, done by Matthias Hertel, http://www.mathertel.de
// -----
// Changelog: see ButtonSlim.h
// -----

#include "ButtonSlim.h"

// ----- Initialization and Default Values -----

ButtonSlim::ButtonSlim(byte pin) {
  _pin = pin;
  _active_state = LOW;  // when reching this state, we register a push of the button
} // ButtonSlim

ButtonSlim::ButtonSlim(uint8_t pin,  bool state) {
  _pin = pin;
  _active_state = state;  // when reching this state, we register a push of the button
} // ButtonSlim

void ButtonSlim::begin(void) {
  pinMode(_pin, INPUT_PULLUP);    // set the Button Pin as input and activate the internal Arduino pull-up resistor.
  _debounceTime = 75;   // number of millisec that have to pass before we test to see if the button state has changed
  _pressFunction = NULL;
}

// explicitly set the number of millisec that have to pass  before we test to see if the button state has changed
void ButtonSlim::setDebounceTime(int ms_ticks) { 
  _debounceTime = ms_ticks;
} // setPressDebounceTime

void ButtonSlim::setActiveState(bool state){
  _active_state = state;
}

void ButtonSlim::currentStateIsInactiveState(void) {
	_active_state = !digitalRead(_pin);
}

// save function for Press event
void ButtonSlim::attachPress(callbackFunction newFunction) {
  _pressFunction = newFunction;
} // attachPress

boolean ButtonSlim::check(void) {
  boolean pinLevel = digitalRead(_pin); // detect the hardware button state
  buttonEvaluate(pinLevel); 
  return _btnEngagedState;
}

void ButtonSlim::buttonEvaluate(boolean buttonLevel) {
  switch ( _state_idx ) {
    case 0: // read btn - waiting for press
        if (buttonLevel == _active_state) {
          _btnEngagedState = true;
          _btn_millis = millis(); // ready for debounce and Click and LongPress detection
          _state_idx++;
          if ( _pressFunction) _pressFunction();
        }  // if
        break;
    case 1: // debounce btn
        if (millis() - _btn_millis > _debounceTime)  { 
          _state_idx++; 
        } // if
        break;
    case 2: // read btn - waiting for release
        // check to see if the button has been released
        if (buttonLevel == !_active_state) { // the button has been released
          _btnEngagedState = false; 
          _btn_millis = millis();  // ready for debounce
          _state_idx++;   // ready for debounce
        }
        break;
    case 3: // debounce btn
        if (millis() - _btn_millis > _debounceTime)   {
          _state_idx = 0;  // ready to register next push action
        } // if
        break;
    default: 
        _state_idx = 0; 
        break;
  } // switch
  return;
} // check
// end.
