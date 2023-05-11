/*
 *  This is a sample sketch to show how to use the ButtonSlim Library
 *  
 *    When pushing a button connected to pin A1 
 *    the built-in LED will change between on and off
 *  
 *
 * Test circuit:
 * 
 *  Connect a push-button to pin A1 (ButtonPin), connect other side of button to ground.
 *  
 *  The built-in LED is used for output 
 *    many Arduino boards already have one LED that is controlled via a pin
 *    The built-in LED is often referenced by LED_BUILTIN
 *
 */
 
#include "ButtonSlim.h"

// Setup a ButtonSlim instance on pin A1.  
ButtonSlim button(A1);

const int LED_Pin =  13;               // 13 for UNO, Nano and Mega
// const int LED_Pin =  LED_BUILTIN;   // for other boards try using LED_BUILTIN


//*********************************************
// setup function - to run once:
//*********************************************
void setup() {
  //Serial.begin(9600);
  
  // set the LED pin to output
  pinMode(LED_Pin, OUTPUT);      // sets the digital pin as output

  //Initiate internal button management
  //   within the button.begin() function, the button pin will be set to INPUT_PULLUP
  button.begin(); 
  
  // set a pointer to the function that will be called when a Button Press event occurs
  button.attachPress(btnPress);    // the btnPress() function will be called - when the button is pressed
                                   // see below for btnPress() declaration

  // Put your setup code here, to run once:
  
} // END setup


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  
  // keep watching the push button:
  button.check();

  // You can implement other code in here or just wait a while 
  // Put your main code here, to run repeatedly:
  
} // END loop()


//********************************************************************
// Button Press function - will be called when the Button is Pressed
//********************************************************************
void btnPress() {
  static int m = LOW;   //used so we can toggle the LED 
  
  // reverse the LED state
  m = !m;

  // set er LED on or off
  digitalWrite(LED_Pin, m);
  
} // END btnPress()


// END sketch
