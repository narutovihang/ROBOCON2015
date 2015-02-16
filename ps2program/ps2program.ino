#include <PS2X_lib.h>
#include<SoftwareSerial.h>
SoftwareSerial MySerial1(3,2);      //rx,tx
SoftwareSerial MySerial3(5,4);      //rx,tx
SoftwareSerial MySerial2(7,6);
SoftwareSerial MySerial4(9,8);
PS2X ps2x;                                   //creates object of class PS2X

int error = 0, xcord = 0, ycord = 0;       // xcord  =  right stick x value 
                                            // ycord = right stick y value
String poshspeed="s200";
String neghspeed="s-200";
String lspeed="s0";
// SETUP --------------------------------------------------------------------
void setup()
{
  //Serial.begin(9600);
  MySerial3.begin(9600);
  MySerial2.begin(9600);
  MySerial1.begin(9600);
  MySerial4.begin(9600);
  ps2x.config_gamepad(13,11,10,12,true,false);    // SPI pin configuration
  //for(int i=0; i<10; i++)                               // Sets all outputs to zero
  //analogWrite(i, 0);
  //MySerial1.println("y");
  //MySerial3.println("y");
  //MySerial2.println("y");
  //MySerial4.println("y");
  MySerial1.println("d0");
  MySerial3.println("d0");
  MySerial2.println("d0");
  MySerial4.println("d0");  
  
  
}
void loop()
{
  ps2x.read_gamepad();
  
  if(ps2x.Button(PSB_R1))
  {
   brake(); 
  }
  else if(ps2x.Button(PSB_L1))
  {
  MySerial1.println("d0");
  MySerial3.println("d0");
  MySerial2.println("d0");
  MySerial4.println("d0");  
  }
  else if(ps2x.Button(PSB_R2))
  {
  MySerial1.println("y");
  MySerial3.println("y");
  MySerial2.println("y");
  MySerial4.println("y");  
  
  }
  else if(ps2x.Button(PSB_GREEN))
  {
  MySerial1.println(poshspeed);
  MySerial3.println(poshspeed);
  MySerial2.println(poshspeed);
  MySerial4.println(poshspeed); 
  }
   else if(ps2x.Button(PSB_BLUE))
  {
  MySerial1.println(neghspeed);
  MySerial3.println(neghspeed);
  MySerial2.println(neghspeed);
  MySerial4.println(neghspeed); 
  }
  else
  {
  xcord = ps2x.Analog(PSS_LX);                //reads the ordinate
  xcord = map(xcord,0,255,-255,255);  //maps the values from the range 0-255 t0 -255-255
  ycord = ps2x.Analog(PSS_LY);
  ycord = map(ycord,0,255,255,-255);
  delay(50);
  omnidrive(xcord,ycord);
  }
}
void omnidrive(int x,int y)
{
  if (abs(x)<20 && abs(y)<20)  //1- stay still
  {
    MySerial1.println(lspeed);
    MySerial3.println(lspeed);
    MySerial2.println(lspeed);
    MySerial4.println(lspeed);
    
    //Serial.println("Stay still");
  }
  /*else if( x<-240 && y>100 && y<200)    //2- 2nd quadrant movement
  {
    //MySerial1.println(lspeed);
    //MySerial3.println(lspeed);
    Serial.println("2nd quadrant movement");
  }
  else if(x>240 && y>200)      //3- first quadrant movement
  {
    //MySerial1.println(poshspeed);
    //MySerial3.println(poshspeed);
    Serial.println("first quadrant movement");
  }
  else if(x>240 && y<-240)    //4- 4th quadrant movement
  {
    //MySerial1.println(lspeed);
    //MySerial3.println(lspeed);
    Serial.println("4th quadrant movement");
  }
  else if(x<-240 && y<-240)    //5- 3rd quadrant movement
  {
    //MySerial1.println(neghspeed);
    //MySerial3.println(neghspeed);
    Serial.println("3rd quadrant movement");
  }*/
  else if(abs(x)<20 && y==255)    //6-forward
  {
    MySerial1.println(poshspeed);
    MySerial3.println(neghspeed);
    MySerial4.println(neghspeed);
    MySerial2.println(poshspeed);
    //Serial.println("forward");
  }
  else if(abs(x)<20 && y==-255)    //7-reverse
  {
    MySerial1.println(neghspeed);
    MySerial3.println(poshspeed);
    MySerial4.println(poshspeed);
    MySerial2.println(neghspeed);
    //Serial.println("reverse");
  }
  else if(x==255 && abs(y)<20)    //8-right
  {
    MySerial1.println(neghspeed);
    MySerial3.println(poshspeed);
    MySerial4.println(neghspeed);
    MySerial2.println(poshspeed);
    //Serial.println("right");
  }
  else if(x==-255 && abs(y)<20)    //9-left
  {
   MySerial1.println(poshspeed);
   MySerial3.println(neghspeed);
   MySerial4.println(poshspeed);
   MySerial2.println(neghspeed); 
   //Serial.println("left");
  }

}
void brake()
{
  MySerial1.println(lspeed);
   MySerial3.println(lspeed);
  MySerial2.println(lspeed);
    MySerial4.println(lspeed);
}


