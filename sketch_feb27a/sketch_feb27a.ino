int v1=7;
int v2=6;
int counter=0;
void setup()
{
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}
void loop()
{
  if(counter<=5)
 { 
 digitalWrite(7,HIGH);
 //digitalWrite(6,LOW);
 delay(20);
 counter++;
 digitalWrite(7,LOW);
 delay(200);
 }
 else if(counter>=6)
 {
 digitalWrite(7,HIGH);
 //digitalWrite(6,LOW);
counter++;
 delay(75);
 digitalWrite(7,LOW);
 delay(200);
}
 //digitalWrite(7,LOW);tttttttttttttttttttttttttttttt
 //digitalWrite(6,HIGH);
  //delay(500);
}
