/*
required system registers:
PS2:
PS2 connected or not
weather bluetooth is connected or not?
Serving:
current status of both pneumatics
Hitting:
current status of pneumatics
*/
/*
serving:
pn1 open
delay
pn2open

change delay:
press d:
current delay
print
press c:
change delay

current status of System:

1)shuttlepneumatic
2)lockpneumatic
*/



/*********************************SystemManual************************************************************************************************************      
                                  Press    Effect
                                  A        Closes shuttle(Loading) Pneumatic
                                  B        Press to Serve Shuttle
                                  C        Change delay Value
                                  D        Current Delay Value
                                  *        Open Lock Pneumatic
                                  #        Enter Value
                                  0        System Status                                  11=Ready to Serve     10/00/01=Not Ready to Serve 
                                  1        Change Value of System Register                Input value of current status of Shuttle and Lock Pneumatic
                                                                                          X=Shuttle Y=Lock Pneumatic    Default Value XY=00
                                                                                          1=Open   0=Close  
                                                                                          
                                  
                                  EEPROM Address of Delay=0  <--Currently not Used
                                  Deafult Delay Value=1000
                                  
*********************************************************************************************************************************************************                                  
*/
/*        L298
10,11-piston
open piston
  10-HIGH
  11-LOW
close piston
   10-LOW
  11-HIGH
8,9-motor
move:
  8-HIGH
  9-LOW
brake:
  8-LOW
  9-LOW
  
  /*********************************SystemManual************************************************************************************************************      
                                  Press    Effect
                                  A        Closes motor
                                  B        Press to Serve Shuttle
                                  C        Change delay Value
                                  D        Current Delay Value
                                  *        Open Lock Pneumatic
                                  #        Enter Value
                                  0        System Status                                  11=Ready to Serve     10/00/01=Not Ready to Serve 
                                  1        Change Value of System Register                Input value of current status of Shuttle and Lock Pneumatic
                                                                                          X=Shuttle Y=Lock Pneumatic    Default Value XY=00
                                                                                          1=Open   0=Close  
                                                                                          
                                  
                                  EEPROM Address of Delay=0  <--Currently not Used
                                  Deafult Delay Value=1000
                                  
*********************************************************************************************************************************************************   
  
  
*/

#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // RS, EN, d4-d7
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3,2,1,0}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//boolean lockPneumatic=true;  //true=lock pneumatic is locked
                             //false=lock pneumatic is released
//boolean shuttlePneumatic=true;  //true=shuttle not released
                                //false=shuttle released
byte lckPneumaClo=10;
byte lckPneumaOp=11;
byte motor1=8;
byte motor2=9;
//byte shutPneumaClo=10;
//byte shutPneumaOp=11;
char key;
int delayValue=1000;
byte x=0;
byte y=0;
void setup(){
  //Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  //delayValue=EEPROM.read(0);
  lcd.begin(16,2);
  lcd.clear();
  //lcd.print("Hello World");
  
}
  
void loop(){
   key = keypad.getKey();
  if (key=='D'){
    getDelay();
  }
  else if(key=='C')
  {
    setDelay();
  }
  else if(key=='B')
  {
    serve();   
  }
  else if(key=='A')
  {
    //close shuttle pneumatic
    opeShutPneuma();
    
  }
  else if(key=='*')
  {
    //open lock pneumatic
    opeLckPneuma();
  }
  else if(key=='0')
  {
    sysStatus();
  }
  else if(key=='1')
  {
    cngSystemStatus();
  }
}
void getDelay()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CurrentDelay");
    lcd.setCursor(0,1);
    lcd.print(delayValue);
    key='f';
}
void setDelay()
{
  String finalDelay = "";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("cngDelay:EntrVal");
  lcd.setCursor(0,1);
  while(key!='#')
  {
     char waitForKey();
    key= keypad.getKey();
    if(isDigit(key))
    {
      lcd.print(key);
      finalDelay+=key;
    }
    
  }
  delayValue=finalDelay.toInt();
 // EEPROM.write(0,delayValue);
  key='f';
  lcd.clear();
}
/*void cloShutPneuma()
{
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,LOW);
  delay(300);                        //*
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,LOW);    //*
  x=0;  
}*/
void opeShutPneuma()
{
  /*lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("openingShuttle");
  lcd.setCursor(0,1);
  lcd.print("Pneumatic");
  digitalWrite(shutPneumaClo,HIGH);
  digitalWrite(shutPneumaOp,LOW);
  key='f';
  x=1;*/
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,LOW);
  delay(300);                        //*
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,LOW);    //*
  x=0;
}
void cloLckPneuma()
{
  digitalWrite(lckPneumaClo,HIGH);
  digitalWrite(lckPneumaOp,LOW);
  y=0;
}
void opeLckPneuma()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("openingLock");
  lcd.setCursor(0,1);
  lcd.print("Pneumatic");
  digitalWrite(lckPneumaClo,HIGH);
  digitalWrite(lckPneumaOp,LOW);
  key='f';
  y=1;
}
void sysStatus()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SystemStatus:");
    lcd.print(x);
    lcd.print(y);
    lcd.setCursor(0,1);
    if(x!=1 && y!=1)
    {
      lcd.print("NotReadyToServe");
    }
    else 
    {
      lcd.print("ReadyToServe");
    }
    key='f';
}
void cngSystemStatus()
{
  String sysstatus="";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("entrCurentStatus");
  lcd.setCursor(0,1);
  while(key!='#')
  {
    char waitForKey();
    key= keypad.getKey();
    if(isDigit(key))
    {
      lcd.print(key);
      sysstatus+=key;
    }
  }
   if(sysstatus=="11")
   {
    x=1;
    y=1;
   }
  else if(sysstatus=="10")
  {
    x=1;
    y=0;
  }
  else if(sysstatus=="01")
  {
    x=0;
    y=1;
  }
  else if(sysstatus=="00")
  {
    x=0;
    y=0;
  }
  key='f';
}
void serve()
{    
  if(x==1 && y==1)
  {
    //1)shuttle pneumatic open
    //2)delay
    //3)lock pneumatic close
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Serving  ");
    lcd.print(delayValue);
    lcd.setCursor(0,1);    
    //cloShutPneuma();
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    delay(delayValue);
    cloLckPneuma();
    
    lcd.print("ShuttleHit");
  }
  else
  {
    lcd.clear();
    lcd.print("NotReadyToServe");
  }
  key='f';
}
