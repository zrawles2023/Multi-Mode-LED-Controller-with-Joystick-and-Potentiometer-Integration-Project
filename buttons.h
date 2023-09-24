//BUTTON FUNCTIONS


bool buttonvalue;
bool previousvalue;
bool previouscleanvalue;
unsigned long lastButtonTime;

int buttonpin;

typedef enum
{
  BUTTON_PRESSED,
  BUTTON_RELEASED,
  BUTTON_HELD
}button_state;

typedef void (*button_callback)(button_state currentstate);
button_callback mycallback;



void initialize_button(int pin, button_callback callback)
{
  buttonpin = pin;
  mycallback = callback;
  pinMode(buttonpin, INPUT_PULLUP);
  
}




bool readbutton()
{
  buttonvalue=digitalRead(buttonpin);

  if(buttonvalue!=previousvalue)
  {
    lastButtonTime=millis(); 
  }

  if(millis()-lastButtonTime>50)
  {
    if(buttonvalue!=previouscleanvalue)
    {
      previouscleanvalue=buttonvalue;

      if(buttonvalue==HIGH)
      {
        //rising edge or pressed
        mycallback(BUTTON_PRESSED);
      }
      else{
        //falling edge or released
        mycallback(BUTTON_RELEASED);
      }
    }
  }
  previousvalue=buttonvalue;
}
