int tact_Pin = 2;
int pin_A = 4;
int pin_B = 5;
int m=0,n=0,i=1;
int mode;

void setup()
{
  Serial.begin(9600);
 pinMode(pin_A, OUTPUT);   
 pinMode(pin_B, OUTPUT);        
 pinMode(tact_Pin, INPUT);
}

void loop()
{
mode  = (PIND&0b00000100);   // for mode change
Serial.println(mode);// when you press the button mode=0
if(mode==0)
{
  delay(1000);
   n=n+1;
  if(n==1)
  {
    m=m+1;
    if(m>1)
    {
      m=0;
    }
    
  }
  else
  {
      m=m;
  }
  
}
else
{
  m=m;
  n=0;
  i=0;
}

if(m==1 && i==1)
{
  //digitalWrite(pin_A,HIGH);
  //delay(100);
  // digitalWrite(pin_A,LOW);
  digitalWrite(pin_B,HIGH);
  delay(700);
  digitalWrite(pin_B,LOW);
  delay(300000); //5 min
  digitalWrite(pin_A,HIGH);
  delay(700);
  digitalWrite(pin_A,LOW);  
  i=0;  
}
else if(m==4 && i==1)
{
}
else
{
  digitalWrite(pin_A,LOW);
  i=1;
}

}
