#include <PS2X_lib.h>

PS2X ps2x;                                   //creates object of class PS2X

int error = 0, xcord = 0, ycord = 0;       // lefty  =  left stick y value 
                                            // righty = right stick y value

// SETUP --------------------------------------------------------------------
void setup()
{
  Serial.begin(57600);
  error=ps2x.config_gamepad(13,11,10,12,true,false);    // SPI pin configuration
  for(int i=0; i<10; i++)                               // Sets all outputs to zero
  analogWrite(i, 0);
  
}
void loop()
{
ps2x.read_gamepad();
  xcord = ps2x.Analog(PSS_RX);                //reads the ordinate
  xcord = map(xcord,0,255,-255,255);          //maps the values from the range 0-255 t0 -255-255
Serial.println(xcord);
//Serial.println("2");
  ycord = ps2x.Analog(PSS_RY);
  ycord = map(ycord,0,255,-255,255);
  if(ycord
  Serial.print(ycord);
  delay(50);
  Serial.print("   ");
  
}



