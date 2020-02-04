#define Pin1 5
#define Pin2 4
void setup() 
{
  // put your setup code here, to run once:
 pinMode(5, OUTPUT);
 pinMode(4, OUTPUT); 

   // put your main code here, to run repeatedly:
//forward
digitalWrite(5,HIGH);
digitalWrite(4,HIGH);
delay(2000);

//right
digitalWrite(5,LOW);
digitalWrite(4,HIGH);
delay(2000);

//left
digitalWrite(5,HIGH);
digitalWrite(4,LOW);
delay(2000);

//forward
digitalWrite(5,HIGH);
digitalWrite(4,HIGH);
delay(2000);


//stop
digitalWrite(5,LOW);
digitalWrite(4,LOW);
delay(2000);

}

void loop() {
}
