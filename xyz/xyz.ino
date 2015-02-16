int i = 0;
void setup()
{
  pinMode(22,OUTPUT);
}
void loop()
{
  while(i==0)
{
  digitalWrite(22,HIGH);
  delay(20);
  i++;
}
digitalWrite(22,LOW);
}
