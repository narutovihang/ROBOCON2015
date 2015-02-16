void setup()
{
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);  
  Serial.begin(9600);
}
int d=3000;
void loop()
{
  String trans;
  String rex;
  while(Serial.available()>0)
    {
      char transchar=Serial.read(); 
      trans +=transchar;
      delay(5); //Doesn't work without this bitch
    }
    if(trans=="1")
    {
      Serial.println(trans);
      motor(d);
    }
    else if(trans=="2")
    {
      Serial.println(trans);
      while(Serial.available()>0)
    {
      char transchar=Serial.read(); 
      trans +=transchar;
      delay(5); //Doesn't work without this bitch
    }
    d=trans.toInt();
    }
    
}
void motor(int a)
{
   digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  delay(a);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(5000);
}
