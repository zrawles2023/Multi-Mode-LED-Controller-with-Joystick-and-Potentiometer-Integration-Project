/*

The project utilizes an Arduino Uno board along with six LEDs, a potentiometer, and joystick.
Its primary function is to control the state of LEDs connected to a breadboard, allowing them to be turned on or off and to blink.
The project uses external libraries for handling the button, joystick, and LED functionalities.

*/


#include "buttons.h"
#include "joystick.h"
#include "led.h"


//led starts in mode 1 (on state). State 2 is the blink state.
int ledMode = 2; 
int currentLed = 7;
int pot;

//Joystick movement function
void joystickchanged(joystick_event myevent){

  switch (myevent){
    case FLICK_RIGHT:

       if(currentLed> 2 && ledMode==1){
       turnoff_led();
       currentLed--;
       initialize_led(currentLed);
       turn_on_led();
       Serial.println("right flick");
      }
         
      break;
       case FLICK_LEFT:
       if(currentLed< 7 && ledMode==1){
       turnoff_led();
       currentLed++;
       initialize_led(currentLed);
       turn_on_led();
       Serial.println("letf flick");
       }
  }
}

//Switch between button states function
void button_event(button_state currentstate) {
  switch(currentstate) {
    case BUTTON_PRESSED:
      if (ledMode == 1) {
        ledMode = 2; // switch to mode 2
      } else if (ledMode == 2) {
        ledMode = 1; // switch back to mode 1
       initialize_led(currentLed);
       turn_on_led();
      }
      break;
  }
}


 //setup used top initialize hardware components
void setup(){
  // initialize all leds from pins 2-7
  initialize_led(7); 
  
  
  initialize_joystick(0,1);
  initialize_button(9, button_event);
  Serial.begin(9600);
}

void loop (){
 
 /* Print Potentiometer Values
 Serial.println(pot);
 Serial.println(analogRead(A0));
*/

  detect_xjoystick_flick(joystickchanged);
  detect_yjoystick_flick(joystickchanged);
  readbutton();
  

  pot = analogRead(A2);
  pot = map(pot, 0, 1023, 100, 1000); 
  
if(pot>220 && ledMode==1){
initialize_led(currentLed);
blink_led(pot);
}
else if (ledMode==2)
{
initialize_led(currentLed);
blink_led(1000);
}
else{
turn_on_led();
}

}
