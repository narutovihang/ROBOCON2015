int vr1=A0,vr2=A1,vL1=A2,vL2=A3;
int IR1=A4,IR2=A5;
int rp=5 , rn=6 , lp=9 , ln=10 ;
int count=0, pwm = 0;
void setup()
{
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  
  Serial.begin(9600);
}
void loop()
{
while(cnt<5)
{
  if( digitalRead(IR1)==HIGH )
  {
    count++;
    valveClose(vr1, vr2);
    //drive(rp, rn, pwm);
    if( digitalRead(IR2)==HIGH )
    {
      valveClose(vL1, vL2);
      delay(1000);
      valveOpen(vr1, vr2);
      //drive(lp, ln, pwm);
      delay(1000);
    }
  }
  
  if( digitalRead(IR2)==HIGH )
  {
    count++;
    valveClose(vL1, vL2);
    //drive(lp, ln, pwm);
    if( digitalRead(IR1)==HIGH )
    {
      valveClose(vr1, vr2);
      delay(1000);
      valveOpen(vL1, vL2);
      //drive(rp, rn, pwm);
      delay(1000);
    }
  }
  
  
}
}

 void valveOpen(int a, int b)
{
 digitalWrite(a, HIGH);
 digitalWrite(b, LOW);
}
void valveClose(int a, int b)
{
 digitalWrite(a, LOW);
 digitalWrite(b, HIGH);
}

void drive(int h, int l, int value)
{
  analogWrite(h, value);
  analogWrite(l,0);
}

