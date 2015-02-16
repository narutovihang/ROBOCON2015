#include<Wire.h>
int j;
void setup()
{
  Serial.begin(9600);
  Wire.begin();
}
void loop()
{
  int i=0;
  
  long int trans=9;
  int command=9;
  while(Serial.available())
  {
    
    int transchar=Serial.read();
    trans+=transchar;  //trans=trans+transchar;
    delay(5);
  }
 
  if(trans<9&&i==0)
  {
    command=trans;
    trans=9;
    i=1;
  }
  else
  {
  i=0;
  j=0;
  }
  
  if(j==0)
  {
    Serial.println(trans);
    Wire.beginTransmission(16);
    Wire.write(command);
    Wire.write(trans);
    Wire.endTransmission(16);
    trans=9;
  }
 
  Wire.requestFrom(16,4);
  while(Wire.available())
  {
    char c=Wire.read();
    Serial.print(c);
  }
}
