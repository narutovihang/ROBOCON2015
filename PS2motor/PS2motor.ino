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

*/

int xcord=0,ycord=0,rxcord=0;

#include<PS2X_lib.h>

PS2X ps2x;
int  ms1=200,ms2=200,ms3=200,ms4=200;
int  mp1=2,mp2=3,mp3=4,mp4=5;
void setup()
{
  ps2x.config_gamepad(13,11,10,12,true,false);              //spi configuration of ps2// (clk,cmd,att,data)
  Serial.begin(9600);
  for(int i=22; i<=29;i++)
  {
    pinMode(i,OUTPUT);
  }
}
void loop()
{
   ps2x.read_gamepad();
  
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
  //Serial.println(xcord);
  //Serial.print("  "); 
  //Serial.print(ycord);
  //Serial.print("  "); 
  //Serial.print(rxcord);
  omnidrive(xcord,ycord,rxcord);
  } 
}
void omnidrive(int x,int y,int z)
{
  if (abs(x)<20 && abs(y)<20)  //1- stay still
  {
     digitalWrite(22,LOW);
     digitalWrite(23,LOW);
     digitalWrite(24,LOW);
     digitalWrite(25,LOW);
     digitalWrite(26,LOW);
     digitalWrite(27,LOW);
     digitalWrite(28,LOW);
     digitalWrite(29,LOW);
     //Serial.println("Stay still");
  }
  /*
  else if( x<-240 && y>100 && y<200)    //2- 2nd quadrant movement
  {

    Serial.println("2nd quadrant movement");
  }
  else if(x>240 && y>200)      //3- first quadrant movement
  {

    Serial.println("first quadrant movement");
  }
  else if(x>240 && y<-240)    //4- 4th quadrant movement
  {
    
    Serial.println("4th quadrant movement");
  }
  else if(x<-240 && y<-240)    //5- 3rd quadrant movement
  {
  
    Serial.println("3rd quadrant movement");
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
     digitalWrite(22,LOW);
     digitalWrite(23,LOW);
     digitalWrite(24,HIGH);
     digitalWrite(25,LOW);
     digitalWrite(26,LOW);
     digitalWrite(27,LOW);
     digitalWrite(28,LOW);
     digitalWrite(29,HIGH);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
     //Serial.println("1st quad");
    }
    else if(z==-255)
    {
     digitalWrite(22,HIGH);
     digitalWrite(23,LOW);
     digitalWrite(24,LOW);
     digitalWrite(25,LOW);
     digitalWrite(26,LOW);
     digitalWrite(27,HIGH);
     digitalWrite(28,LOW);
     digitalWrite(29,LOW);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
     //Serial.println("2nd quad");
    }
    else
    {
     digitalWrite(22,HIGH);
     digitalWrite(23,LOW);
     digitalWrite(24,HIGH);
     digitalWrite(25,LOW);
     digitalWrite(26,LOW);
     digitalWrite(27,HIGH);
     digitalWrite(28,LOW);
     digitalWrite(29,HIGH);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
     //Serial.println("forward");
    }
  }
  else if(abs(x)<20 && y==-255)    //7-reverse
  {
        if(z==255)    //4th quad
    {
     digitalWrite(22,LOW);
     digitalWrite(23,HIGH);
     digitalWrite(24,LOW);
     digitalWrite(25,LOW);
     digitalWrite(26,HIGH);
     digitalWrite(27,LOW);
     digitalWrite(28,LOW);
     digitalWrite(29,LOW);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
     //Serial.println("4th quad");
    }
    else if(z==-255)
    {
     digitalWrite(22,LOW);
     digitalWrite(23,LOW);
     digitalWrite(24,LOW);
     digitalWrite(25,HIGH);
     digitalWrite(26,LOW);
     digitalWrite(27,LOW);
     digitalWrite(28,HIGH);
     digitalWrite(29,LOW);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
     //Serial.println("3rd quad");
    } 
    else
     {
     digitalWrite(22,LOW);
     digitalWrite(23,HIGH);
     digitalWrite(24,LOW);
     digitalWrite(25,HIGH);
     digitalWrite(26,HIGH);
     digitalWrite(27,LOW);
     digitalWrite(28,HIGH);
     digitalWrite(29,LOW);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
     //Serial.println("reverse");
     }
  }
  else if(x==255 && abs(y)<20)    //8-right
  {
     digitalWrite(22,LOW);
     digitalWrite(23,HIGH);
     digitalWrite(24,HIGH);
     digitalWrite(25,LOW);
     digitalWrite(26,HIGH);
     digitalWrite(27,LOW);
     digitalWrite(28,LOW);
     digitalWrite(29,HIGH);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
     //Serial.println("right");
  }
  else if(x==-255 && abs(y)<20)    //9-left
  {
     digitalWrite(22,HIGH);
     digitalWrite(23,LOW);
     digitalWrite(24,LOW);
     digitalWrite(25,HIGH);
     digitalWrite(26,LOW);
     digitalWrite(27,HIGH);
     digitalWrite(28,HIGH);
     digitalWrite(29,LOW);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
   //Serial.println("left");
  }

}
void brake()
{
     digitalWrite(22,LOW);
     digitalWrite(23,LOW);
     digitalWrite(24,LOW);
     digitalWrite(25,LOW);
     digitalWrite(26,LOW);
     digitalWrite(27,LOW);
     digitalWrite(28,LOW);
     digitalWrite(29,LOW);
     //Serial.println("brake");
}

void clockwise()
{
     digitalWrite(22,HIGH);
     digitalWrite(23,LOW);
     digitalWrite(24,HIGH);
     digitalWrite(25,LOW);
     digitalWrite(26,HIGH);
     digitalWrite(27,LOW);
     digitalWrite(28,HIGH);
     digitalWrite(29,LOW);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4); 
     //Serial.println("clockwise");
}

void anticlockwise()
{
     digitalWrite(22,LOW);
     digitalWrite(23,HIGH);
     digitalWrite(24,LOW);
     digitalWrite(25,HIGH);
     digitalWrite(26,LOW);
     digitalWrite(27,HIGH);
     digitalWrite(28,LOW);
     digitalWrite(29,HIGH);
     
     analogWrite(mp1,ms1);
     analogWrite(mp2,ms2);
     analogWrite(mp3,ms3);
     analogWrite(mp4,ms4);
     //Serial.println("anticlockwise");
}
