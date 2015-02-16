#include<SoftwareSerial.h>

SoftwareSerial Serial1(3,2);  //rx,tx  3-orange 2-yellow
SoftwareSerial Serial2(5,4);  //rx,tx  3-orange 2-yellow

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600); 
}

void loop()
{
  String trans,trans1,trans2;
  String rex;
  while(Serial.available()>0)
    {
      char transchar=Serial.read();
      trans +=transchar;
      delay(5); //Doesn't work without this bitch
    }
    
   if(trans!="")
    {
    trans1 = 's'+trans;
    trans2 = '-'+trans;
    trans2 = 's'+trans2;
    Serial1.println(trans1);
    Serial2.println(trans2);
    trans="";
    trans1="";
    trans2="";
    }
    
}

