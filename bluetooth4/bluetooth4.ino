#include <SoftwareSerial.h>
SoftwareSerial Serial1(3,2);    //rx,tx
void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  //pinMode(2,OUTPUT);
  //pinMode(3,INPUT);
  
}
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
    
   if(trans!="")
    {
    Serial1.println(trans);
    //Serial2.println(trans);
    trans="";
    
    }
     while(Serial1.available()>0)
    {
      char rexchar=Serial1.read();
      rex +=rexchar;
      delay(5); //Doesn't work without this bitch
    }
    
   if(rex!="")
    {
    Serial.println(rex);
    //Serial2.println(trans);
    rex="";
    
    }
}
