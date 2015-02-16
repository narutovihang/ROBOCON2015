/*
Pins for hercules lite 6v-16v 8Amp driver:
1-gnd
2-direction control 1
3-diagnostic 1
4-pwm speed control
5-diagnostic 2
6-direction control 2
7-current sense output

motor driver pins connected to arduino Mega-
        PWM  In1 In2
Motor1  2    22  23
Motor2  3    24  25
Motor3  4    26  27  
Motor4  5    28  29

Motor behavior for In1 and In2 values:
In1  In2  behavior
1    1    break to VCC
1    0    clockwise
0    1    counterclockwise
0    0    break to ground

PS2 pins configuration:

12   11   10   13
data cmd  att  clk

{data cmd n/c gnd vcc att clk n/c ack}--->General pin configuration of all pins of a PS2
{miso mosi             ss   sclk}-------->


ominidrive motor arrangements:
motor1    motor2

motor4    motor3

omnidrive configuration:          
           motor1*      motor2      motor3*      motor4
           in1  in2     in1  in2    in1  in2     in1  in2
forward    1    0        0    1      1    0      0    1
reverse    0    1        1    0      0    1      1    0
left       0    1        1    0      0    1      1    0
right      1    0        0    1      1    0      0    1
clkwise    1    0        1    0      1    0      1    0
antclkwise 0    1        0    1      0    1      0    1
1st quad   1    0        0    0      1    0      0    0
2nd quad   0    0        0    1      0    0      0    1
3rd quad   0    1        0    0      0    1      0    0
4th quad   0    0        1    0      0    0      1    0
To Brake:
IN1 In2        In1  In2
1    1    or    0    0


PS2 Bluetooth Transmit-Receive codebook
1st quad-1
forward-2
2nd quad-3
left-4
3rd quad-5
reverse-6
4th quad-7
right-8
brake-0
Stay still-0
Clockwise- 9
anticlockwise- 10
*/

int xcord=0,ycord=0,rxcord=0;

#include<SoftwareSerial.h>
#include<PS2X_lib.h>
SoftwareSerial MySerial(3,2);
PS2X ps2x;
//int  ms1=200,ms2=200,ms3=200,ms4=200;
//int  mp1=2,mp2=3,mp3=4,mp4=5;
void setup()
{
  ps2x.config_gamepad(13,11,10,12,true,false);              //spi configuration of ps2// (clk,cmd,att,data)
  MySerial.begin(9600);

}
void loop()
{
   ps2x.read_gamepad();
   delay(50);
  
  if(ps2x.Button(PSB_R1))
  {
   brake(); 
  }
  /*else if(ps2x.Button(PSB_L1))
  {
   
  }
  else if(ps2x.Button(PSB_R2))
  {
 
  }*/
  else if(ps2x.Button(PSB_PINK))
  {
    
    
     clockwise();
    
  }
   else if(ps2x.Button(PSB_RED))
  {
     anticlockwise();
   
  }
  else
  {
  xcord = ps2x.Analog(PSS_LX);                //reads the ordinate
  xcord = map(xcord,0,255,-255,255);  //maps the values from the range 0-255 t0 -255-255
  ycord = ps2x.Analog(PSS_LY);
  ycord = map(ycord,0,255,255,-255);
  rxcord = ps2x.Analog(PSS_RX);                //reads the ordinate
  rxcord = map(rxcord,0,255,-255,255);  //maps the values from the range 0-255 t0 -255-255
  delay(50);
  //MySerial.println(xcord);
  //MySerial.print("  "); 
  //MySerial.print(ycord);
  //MySerial.print("  "); 
  //MySerial.print(rxcord);
  omnidrive(xcord,ycord,rxcord);
  } 
}
void omnidrive(int x,int y,int z)
{
  if (abs(x)<20 && abs(y)<20)  //1- stay still
  {
 
     MySerial.println("0");
  }
  /*
  else if( x<-240 && y>100 && y<200)    //2- 2nd quadrant movement
  {

    MySerial.println("2nd quadrant movement");
  }
  else if(x>240 && y>200)      //3- first quadrant movement
  {

    MySerial.println("first quadrant movement");
  }
  else if(x>240 && y<-240)    //4- 4th quadrant movement
  {
    
    MySerial.println("4th quadrant movement");
  }
  else if(x<-240 && y<-240)    //5- 3rd quadrant movement
  {
  
    MySerial.println("3rd quadrant movement");
  }
  */
  /*           motor1*      motor2      motor3*      motor4
           in1  in2     in1  in2    in1  in2     in1  in2
forward    1    0        0    1      1    0      0    1
reverse    0    1        1    0      0    1      1    0
left       0    1        1    0      0    1      1    0
right      1    0        0    1      1    0      0    1
  */
  else if(abs(x)<20 && y==255)    //6-forward                     
  {     
     if(z==255)    //1st quad
    {

     MySerial.println("1");
    }
    else if(z==-255)
    {

     MySerial.println("3");
   
    }
    else
    {

     MySerial.println("2");
    }
  }
  else if(abs(x)<20 && y==-255)    //7-reverse
  {
        if(z==255)    //4th quad
    {
  
     MySerial.println("7");
    }
    else if(z==-255)
    {

     MySerial.println("5");
    } 
    else
     {
 
     MySerial.println("6");
     }
  }
  else if(x==255 && abs(y)<20)    //8-right
  {

     MySerial.println("8");
  }
  else if(x==-255 && abs(y)<20)    //9-left
  {

   MySerial.println("4");
  }
  else
  {
    brake();
  }

}
void brake()
{
 
     MySerial.println("0");
}

void clockwise()
{ 

     MySerial.println("9");

}

void anticlockwise()
{
    
     MySerial.println("10");
}
