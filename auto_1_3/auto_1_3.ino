int vr=A0,vL=A1;
int IR1=A2, IR2=A3, LIR1=2, LIR2=3, RIR1=7, RIR2=8 ;
int rp=5 , rn=6 , lp=9 , ln=10 ;
int count=0, pwm = 150;
void setup()
{
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
}
void loop()
{
while(count<5)
{
  
  if( digitalRead(IR1)==HIGH )
  {
    count++;
    valveClose(vr);
    //drive(rp, rn, pwm);
    if( count !=1)
    {
    if(digitalRead(LIR2)==LOW)
    {
      drive(lp, ln, pwm);
    }
    else 
    {
    halt(lp, ln);
    }
    }
    if( digitalRead(IR2)==HIGH )
    {
      valveClose(vL);
      delay(1000);
      if (count != 3)
      {
        valveOpen(vr);
        //drive(lp, ln, pwm);
        delay(1000);
      }
    }
  }
  if( digitalRead(IR2)==HIGH )
  {
    count++;
    valveClose(vL);
    //drive(lp, ln, pwm);
    if(digitalRead(RIR2)==LOW)
    {
      //drive(rp, rn, pwm);
    }
    else 
    {
      halt(rp, rn);
    }  
    if( digitalRead(IR1)==HIGH )
    {
      
      valveClose(vr);
      delay(1000);
      valveOpen(vL);
      //drive(rp, rn, pwm);
      delay(1000);
    }
  }
}
}

 void valveOpen(int a)
{
 digitalWrite(a, LOW);
}
void valveClose(int a)
{
 digitalWrite(a, HIGH);
}

void drive(int h, int l, int value)
{
  analogWrite(h, value);
  analogWrite(l,0);
}
void halt(int h, int l)
{
  analogWrite(h, 0);
  analogWrite(l,0);
}
