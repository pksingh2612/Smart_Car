#define pinhall 2
#define ledPin 13

void setup() 
{
// put your setup code here, to run once:
pinMode(pinhall,INPUT);
pinMode(ledPin,OUTPUT);
Serial.begin(9600);
}

void loop() 
{
int c;
// put your main code here, to run repeatedly:
int x=digitalRead(pinhall);
Serial.println(x);
if (x==0 ) 
 { 
  c=1;
  if (c!=0)
   {
    digitalWrite(ledPin,HIGH);
    delay(10);
    digitalWrite(ledPin,LOW);
    c=0;
  }
 }
else
{
  digitalWrite(ledPin,LOW);
}
}
