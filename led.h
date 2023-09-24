//LED FUNCTIONS

int ledpin = 2;
unsigned long previousLedTime1;
bool ledState;


unsigned long lastFadeTime;
int brightness;

int incrament = 1;


void initialize_led(int pin)
{
  ledpin=pin;
  pinMode(ledpin,OUTPUT);
}

void turn_on_led()
{
  digitalWrite(ledpin,HIGH);
}
void turnoff_led()
{
  digitalWrite(ledpin,LOW);
}


void blink_led(int periodms)
{
    if(millis() - previousLedTime1 >= periodms)
    {
      previousLedTime1 = millis();
      ledState =! ledState;
      digitalWrite(ledpin, ledState);
    }
}

void blink_led(int periodms,int durationms)
{
  unsigned long end_time=millis()+durationms;
  
  while(millis()<end_time)
  {
   blink_led(periodms);
  }
  turnoff_led();
  
}



void fade_led_sawtooth(int periodms)
{

    if(millis()- lastFadeTime>periodms)
  {
    brightness =(brightness+1)%255;
     analogWrite(ledpin,brightness);
     lastFadeTime=millis();
  }
}

void fade_led_sawtooth( int periodms,int durationms)
{
  unsigned long end_time=millis()+durationms;
  
  while(millis()<end_time)
  {
   fade_led_sawtooth(periodms);
  }
  turnoff_led();
}

void fade_led_triangle(int periodms)
{
    if(millis()- lastFadeTime>periodms)
  {
    if(brightness>=255)
    {
      incrament=-1;
    }
    else if(brightness<=0)
    {
      incrament=1;
    }
    
    brightness=(brightness+incrament);
     analogWrite(ledpin,brightness);
     lastFadeTime=millis();
  }
}

void fade_led_triangle(int periodms,int durationms)
{
  unsigned long end_time=millis()+durationms;
  
  while(millis()<end_time)
  {
   fade_led_triangle(periodms);
  }
  turnoff_led();
}
