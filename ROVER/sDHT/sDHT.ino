// Rover Code
//SDA --A4
//SCL --A5
//VCC -- 3.3V

#include "Adafruit_Si7021.h"
#define pinhall 2
#define ledPin 13
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define Pin1 5
#define Pin2 4
#define LedPin 6
Adafruit_Si7021 sensor = Adafruit_Si7021();
RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";
int i=0;
void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
 pinMode(ledPin,OUTPUT);
  pinMode(pinhall,INPUT);
  pinMode(Pin1, OUTPUT);
 pinMode(Pin2, OUTPUT);
 pinMode(LedPin,OUTPUT);
  // wait for serial port to open
  while (!Serial) 
  {
    delay(10);
  }

  Serial.println("Si7021 test!");
  
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  Serial.print("Found model ");
  switch(sensor.getModel()) {
    case SI_Engineering_Samples:
      Serial.print("SI engineering samples"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }
  Serial.print(" Rev(");
  Serial.print(sensor.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor.sernum_a, HEX); Serial.println(sensor.sernum_b, HEX);
  delay(180000);// for 3min 180000 // for 1s = 1000 for 1min= 60000
}

void loop() {
int c;
// put your main code here, to run repeatedly:
int x=digitalRead(pinhall);
Serial.println(x);
if (x==1 ) 
 { 
  c=1;
  if (c!=0)
   {
   // digitalWrite(ledPin,HIGH);
   // delay(10);
   // digitalWrite(ledPin,LOW);
   motion();
   c=0;
  }
 }
else
{
  //digitalWrite(ledPin,LOW);
  digitalWrite(Pin1,LOW);
  digitalWrite(Pin2,LOW);
}

if(i==1)
{
int LDR=analogRead(A0);
float h=sensor.readHumidity();
float t=sensor.readTemperature();
  //Serial.print("HALL value:");
  Serial.print("LDR value:");
  Serial.print(LDR);
  Serial.print("\tHumidity:");
  Serial.print(h,2);
  Serial.print("\tTemperature: ");
  Serial.println(t,2);
  digitalWrite(LedPin,HIGH);
  float text[]={LDR,h,t};
  radio.write(&text, sizeof(text));
  digitalWrite(LedPin,LOW );
}
  delay(1000);
}

void motion()
{
     // put your main code here, to run repeatedly:
     if (i==0)
     {
      for(int g=0;g<=4;++g)
      {
//forward
digitalWrite(Pin1,HIGH);
digitalWrite(Pin2,HIGH);
delay(2000);
      }
////right
//digitalWrite(Pin1,LOW);
//digitalWrite(Pin2,HIGH);
//delay(2000);

////left
//digitalWrite(Pin1,HIGH);
//digitalWrite(Pin2,LOW);
//delay(2000);

//forward
digitalWrite(Pin1,HIGH);
digitalWrite(Pin2,HIGH);
delay(2000);

//forward
digitalWrite(Pin1,HIGH);
digitalWrite(Pin2,HIGH);
delay(2000);


//stop
digitalWrite(Pin1,LOW);
digitalWrite(Pin2,LOW);
delay(2000);
i=1;
     }

  }
