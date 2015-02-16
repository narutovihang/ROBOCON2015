int pwmvalue=255;
String inString="";
void setup()
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  Serial.begin(9600);
}
void loop()
{
    while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char 
      // and add it to the string:
      inString += (char)inChar; 
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      //Serial.print("Value:");
      pwmvalue=inString.toInt();
      Serial.println(pwmvalue);
      //Serial.println(inString);
      // clear the string for new input:
      inString = ""; 
    }
  }
     analogWrite(2,pwmvalue);
       
}
