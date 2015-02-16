#include<Serial.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("G214748364");
  delay(500000);
}

  


