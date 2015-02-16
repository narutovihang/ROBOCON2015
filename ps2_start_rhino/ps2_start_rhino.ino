#include<PS2X_lib.h>  //for v1.6

PS2X ps2x;

int error=0;
byte type=0;
byte vibrate=0;

void setup()
{
  Serial.begin(57600);
  
  ps2x.config_gamepad(13,11,10,12,true,false);  //(clock,cmd,attention,data,pressurs,rumble)
  
  //for(int i=0; i<10; i++)                               // Sets all outputs to zero
  //analogWrite(i, 0);
  
  if(error==0)
  {
    Serial.println("Okay");
  }
  else if(error==1)
  {
    Serial.println("No controller found,check wiring");
  }
  else if(error==2)
  {
    Serial.println("Controller found,not taking ");
  }
  else if (error==3)
  {
    Serial.println("Controller refusing to enter pressure mode");
  }
  
  type=ps2x.readType();
  switch(type)
  {
    case 0:
    Serial.println("Unknown controller");
    break;
    case 1:
    Serial.println("Dualshock");
    break;
    case 2:
    Serial.println("unknown controller2");
    break;
  }
}
void loop()
{
  
  if(type!=2)
  {
    ps2x.read_gamepad();  //read controller and 
    
    if(ps2x.Button(PSB_RED))
    {Serial.println("Circle pressed");}
    if(ps2x.Button(PSB_PINK))
    {Serial.println("square pressed");}
    if(ps2x.Button(PSB_GREEN))
    {Serial.println("triangle pressed");}
    if(ps2x.Button(PSB_BLUE))
    {Serial.println("cross pressed");}
   
    
    
    
    
    
    
    /*if(ps2x.Button(PSB_START))  //will be true as long button is pressed
    {
    Serial.println("Start_held");
    }
    if(ps2x.Button(PSB_SELECT))
    {
      Serial.println("Select_held");
    }
    */
   /* if(ps2x.Button(PSB_PAD_UP))
    {
      Serial.println("Up_held");
      Serial.println(ps2x.Analog(PSAB_PAD_UP),DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT))
    {
      Serial.println("RIGHT_held");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT),DEC);      
    }
    if(ps2x.Button(PSB_PAD_LEFT))
    {
      Serial.println("LEFT_held");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT),DEC);      
    }
    if(ps2x.Button(PSB_PAD_DOWN))
    {
      Serial.println("DOWN_held");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN),DEC);      
    }
    
    vibrate=ps2x.Analog(PSAB_BLUE);  //this will set the large motor vibrate speed
                                      //on hard you press the blue (X)button
    if(ps2x.NewButtonState())        //true for every change
    {    
      if(ps2x.Button(PSB_L3))
      Serial.println("L3");
      if(ps2x.Button(PSB_R3))
      Serial.println("R3");
      if(ps2x.Button(PSB_L2))
      Serial.println("L2");
      if(ps2x.Button(PSB_R2))
      Serial.println("R2");
      if(ps2x.Button(PSB_GREEN))
      Serial.println("Triangle pressed");
    }
    if(ps2x.ButtonPressed(PSB_RED))  //true if just pressed
    Serial.println("Circle_pressed_just");
    
    if(ps2x.ButtonReleased(PSB_PINK))  //true of button just released    
      Serial.println("Square_just_released");
      
    if(ps2x.NewButtonState(PSB_BLUE))  // will be true if just released/pressed
    Serial.println("X_changed");
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))  //print stick values if either is true
    {
      Serial.print("Stick values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }*/
  }

  delay(50);
}
    
    
