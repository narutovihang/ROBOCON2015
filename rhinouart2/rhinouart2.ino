#include<SoftwareSerial.h>

SoftwareSerial MySerial2(3,2);  //rx,tx  3-orange 2-yellow
//SoftwareSerial Serial2(5,4);  //rx,tx  3-orange 2-yellow

void setup()
{
  Serial.begin(9600);
  MySerial2.begin(9600);
  //Serial2.begin(9600); 
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
    MySerial2.println(trans);
    Serial.println(trans);
    trans="";
    
    }
     while(MySerial2.available()>0)
    {
      char rexchar=MySerial2.read();
      rex +=rexchar;
      delay(5); //Doesn't work without this bitch
    }
    
   if(rex!="")
    {
    Serial.println(rex);
    MySerial2.println(trans);
    rex="";
    
    }
    
    
    
}

