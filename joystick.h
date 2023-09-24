
//JOYSTICK FUNCTIONS


int x_pin;
int y_pin;

int xjoyval;
int previous_xjoyval;

int yjoyval;
int previous_yjoyval;

int xval;

typedef enum
{
  FLICK_UP,
  FLICK_UP_RETURN_CENTER,
  FLICK_DOWN,
  FLICK_DOWN_RETURN_CENTER,
  FLICK_LEFT,
  FLICK_LEFT_RETURN_CENTER,
  FLICK_RIGHT,
  FLICK_RIGHT_RETURN_CENTER
}joystick_event;

typedef void (*joystick_callback)(joystick_event event);

void initialize_joystick(int xpin, int ypin)
{
  x_pin=xpin;
  y_pin=ypin;
}

int read_joystick_xaxis()
{
  return (analogRead(x_pin));
}

int read_joystick_yaxis()
{
  return (analogRead(y_pin));
}

void detect_xjoystick_flick(joystick_callback joycallback)
{
  xval=read_joystick_xaxis();

  if(xval>900){
    xjoyval=1;
  }else if (xval>400 && xval<600){
    xjoyval=0;
  }else if(xval<120){
    xjoyval=-1;
  }

if(xjoyval!=previous_xjoyval)
{
  if(xjoyval==1 && previous_xjoyval==0)
  {
    joycallback(FLICK_LEFT);
  }
    else if(xjoyval==0 && previous_xjoyval==1)
  {
    joycallback(FLICK_LEFT_RETURN_CENTER);
  }
    else if(xjoyval==-1 && previous_xjoyval==0)
  {
    joycallback(FLICK_RIGHT);
  }
    else if(xjoyval==0 && previous_xjoyval==-1)
  {
    joycallback(FLICK_RIGHT_RETURN_CENTER);
  }
  

}
previous_xjoyval=xjoyval;
}


void detect_yjoystick_flick(joystick_callback joycallback)
{
  int yval=read_joystick_yaxis();

  if(yval>900){
    yjoyval=1;
  }else if (yval>400 && yval<600){
    yjoyval=0;
  }else if(yval<120){
    yjoyval=-1;
  }

if(yjoyval!=previous_yjoyval)
{
  if(yjoyval==1 && previous_yjoyval==0)
  {
    joycallback(FLICK_UP);
  }
    else if(yjoyval==0 && previous_yjoyval==1)
  {
    joycallback(FLICK_UP_RETURN_CENTER);
  }
    else if(yjoyval==-1 && previous_yjoyval==0)
  {
    joycallback(FLICK_DOWN);
  }
    else if(yjoyval==0 && previous_yjoyval==-1)
  {
    joycallback(FLICK_DOWN_RETURN_CENTER);
  }
}
  previous_yjoyval=yjoyval;

}
