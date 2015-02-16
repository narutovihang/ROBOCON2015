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

//#include<SoftwareSerial.h>

//SoftwareSerial Serial1(3,2);  //rx,tx  3-orange 2-yellow
//SoftwareSerial Serial2(5,4);  //rx,tx  3-orange 2-yellow
String rex;
int  ms1=255,ms2=255,ms3=255,ms4=255;
int  mp1=2,mp2=3,mp3=4,mp4=5;
//char rexchar;
void setup()
{
  //Serial.begin(9600);
  Serial1.begin(9600);
    for(int i=22; i<=29;i++)
  {
    pinMode(i,OUTPUT);
  }
  //Serial2.begin(9600); 
}

void loop()
{
 
     while(Serial1.available()>0)
    {
     char rexchar=Serial1.read();
      rex +=rexchar;
      delay(5); //Doesn't work without this bitch
    }
    
    if(rex!="")
    {
    //Serial.println(rex);
    //Serial1.println(trans);
    int x=rex.toInt();
    //Serial.println(x);
    if(x==0)
    {
      brake();
     // Serial.println("b");
    }
    else  if(x==1)
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
      //Serial.println("1st");
    }
     else  if(x==2)
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
    //Serial.println("f");
    } else  if(x==3)
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
      //Serial.println("2nd");
    } else  if(x==4)
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
      //Serial.println("L");
    } else  if(x==5)
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
      //Serial.println("3rd");
    } else  if(x==6)
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
      //Serial.println("Rev");
    } else  if(x==7)
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
      //Serial.println("4th");
    } else  if(x==8)
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
      Serial.println("Right");
    } else  if(x==9)
    {
      clockwise();
      //Serial.println("c");
    } else  if(x==10)
    {
      anticlockwise();
      Serial.println("ac");
    }
    else
    {
      brake();
      //Serial.println(x);
    }
    rex="";
    
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
}
