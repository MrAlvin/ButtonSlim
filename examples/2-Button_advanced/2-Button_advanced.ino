/*
 *  This is a sample sketch to show how to use the ButtonSlim Library
 *  
 *  When pushing a button connected to pin A1 
 *    the built-in LED will  change between on and off
 *  
 *
 * Test circuit:
 * 
 *  Connect a push-button to pin A1 (ButtonPin), connect other side of button to ground.
 *  
 *  The built-in LED is used for output 
 *    many Arduino boards already have a LED that is controlled via a pin
 *
 *
 * Other functions presented in this Sketch: 
 *   setting the time (in milli seconds (ms) ) for the 
 *     - debounce
 *      
 *  Serial.println() is used to show the event of:
 *     - a Button Press, 
  *  
 *  
 *  by MrAlvin - May 2023
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

  Serial.begin(115200); // serial is used to show button event
  
  // set the LED pin to output
  pinMode(LED_Pin, OUTPUT);      // sets the digital pin as output

  //Initiate internal button management
  //   within the button.begin() function, the button pin will be set to INPUT_PULLUP
  button.begin(); 
  
  // link the btnPress() function to be called on a button Press event.   
  button.attachPress(btnPress);

  // adjust debounce details about the button press
  button.setDebounceTime(20);    // set number of milli sec that have to pass before we test to see if the button state has changed
                                      // default is 75 milli seconds
                                      
   // for Blinky Shield to work correctly
  delay(2); 
} // END setup()


//*********************************************
// main code -  to run repeatedly: 
//*********************************************
void loop() {
  // keep watching the push button:
  button.check();

  // You can implement other code in here or just wait a while 
  // put your main code here, to run repeatedly:

} // END loop()


//********************************************************************
// Button Press function - will be called when the Button is pressed
//********************************************************************
void btnPress() {
  static int m = LOW;   //used so we can toggle the LED 
  // reverse the LED 
  m = !m;
  // write to the LED pin
  digitalWrite(LED_Pin, m);

  Serial.print( F("button Pressed - ") );
  Serial.println( millis() );
} // END btnPress()

// END Sketch
