/*
Pin configuration MD10A
1-GND
2-PWM2-Pwm speed control motor 2
3-DIR2-Direction i/p motor 2
4-PWM1-PWM i/p speed control motor 1
5-DIR1-Direction i/p motor 1


*/



void setup() {
  // put your setup code here, to run once:
pinMode(7,OUTPUT);      //pwm pin for motor
pinMode(6,OUTPUT);      //direction control motor
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  String trans;
  String rex;
  while(Serial.available()>0)
    {
      char transchar=Serial.read(); 
      trans =transchar;
      delay(5); //Doesn't work without this bitch
    }
    if(trans=="b")
    {
      brake();
    }
    else if(trans=="cw")
    {
      clockwise();
    }
    else if(trans=="ccw")
    {
      counterclockwise();
    }  
    
}
void brake()
{
  analogWrite(7,0);
}
void clockwise()
{
  digitalWrite(6,HIGH);
  analogWrite(7,255);
}
void counterclockwise()
{
  digitalWrite(6,LOW);
  analogWrite(7,255);
}
