long debouncing_time = 25; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

//const byte ledPin = 13;

const byte Pin1=4;
const byte Pin2=5;
const byte interruptPin = 2;

volatile byte state = LOW;

void setup() 
{
  //pinMode(ledPin, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin),debounceInterrupt, LOW);
  
  //attachInterrupt(0, debounceInterrupt, RISING);
}

void loop() 
{
  
}

void debounceInterrupt() 
{
  if((long)(micros() - last_micros) >= debouncing_time * 1000) 
  {
    Interrupt();
    last_micros = micros();
  }
}

void Interrupt() 
{
  //Do Something
  state = !state;
  //digitalWrite(ledPin, state);
  digitalWrite(Pin1, state);
  delay(1500);
  digitalWrite(Pin1, !state);
  delay(1000);
  
 
}
