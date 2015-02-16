#include <PS2X_lib.h>

PS2X ps2x;

//PINS---------------------------------------------------------------------
int 
error =  0, 
lefty =  0,
leftx =  0,
rightx=  0,
clk   = 52,
cmd   = 51,
att   = 53,
data  = 50, 
up    =  2, 
un    =  3, 
dp    =  4,
dn    =  5,
lp    =  6,
ln    =  7,
rp    =  8,
rn    =  9
;

// SETUP --------------------------------------------------------------------
void setup()
{
  
  error=ps2x.config_gamepad(clk,cmd,att,data,true,false);
  for(int i=2; i<9; i++)
  analogWrite(i, 0);
  
}

// MAIN LOOP -----------------------------------------------------------------
void loop()
{
  ps2x.read_gamepad();
  
  if( ps2x.ButtonPressed(PSB_R2) )
     reverse();
      
  //-------------------------------   
  lefty = ps2x.Analog(PSS_LY);
  lefty = map(lefty,0,255,255,-255);
  if(lefty > 5)
  {
    
    drive(lp, ln, lefty);
    drive(rp, rn, lefty);  
  
  } 
  else if(lefty < -5)
  {
    lefty = (-1)*lefty;
    
    drive(ln, lp, lefty);
    drive(rn, rp, lefty);
    
  }
  else
  {
    halt(lp, ln, rp, rn);
  }
   
  //--------------------------------        
  leftx = ps2x.Analog(PSS_LX);
  leftx = map(leftx,0,255,-255,255);
  if(leftx > 5)
  {
    
    drive(up, un, leftx);
    drive(dp, dn, leftx);  
  
  } 
  else if(leftx < -5)
  {
    leftx = (-1)*leftx;
    
    drive(un, up, leftx);
    drive(dn, dp, leftx);
    
  }
  else
  {
    halt(up, un, dp, dn);
  }
  
  //---------------------------------            
  rightx = ps2x.Analog(PSS_RX);
  rightx = map(rightx,0,255,-255,255);
  if(rightx > 5)
  {

    drive(up, un, rightx);
    drive(dn, dp, rightx);  
    drive(lp, ln, rightx);
    drive(rn, rp, rightx); 
  }
  if(rightx < -5)
  {
    rightx = (-1)*rightx;
    
    drive(un, up, rightx);
    drive(dp, dn, rightx);  
    drive(ln, lp, rightx);
    drive(rp, rn, rightx); 
    
  }
  
  delay(50);
}


// DRIVE ----------------------------------------------------------------
void drive(int h, int l, int value)
{
  analogWrite(h, value);
  analogWrite(l, 0);
}
void halt(int a, int b, int c, int d)
{
  analogWrite(a, 0);
  analogWrite(b, 0);
  analogWrite(c, 0);
  analogWrite(d, 0);
}
void reverse()
{
 int t1 = up, t2 = un, t3 = dp, t4 = dn ;
 up = lp;
 un = ln;
 dp = rp;
 dn = rn;
 lp = t1;
 ln = t2;
 rp = t3;
 rn = t4; 
}

