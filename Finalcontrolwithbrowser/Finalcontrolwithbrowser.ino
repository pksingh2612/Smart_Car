#include <ESP8266WiFi.h>

//Ultrasound Sensor
#define trigPin1 15 // Trigger  D8
#define echoPin1 3 //echo      RX

#define trigPin2 13 // Trigger  D7
#define echoPin2 12//echo      D6

//Motor A
int enableA = 16;  //D0
int pinA1 = 5;    //D1
int pinA2 = 4;    //D2

///Motor B
int enableB = 14;//D5
int pinB1 = 0;    //D3
int pinB2 = 2;  //D4

int r;
//Variables1
long duration1;
int distance1;

//Variables1
long duration2;
int distance2;

 
const char* ssid = "PKS"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "12345678"; // Your Wifi password, in case you have open network comment the whole statement.
 

WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.
 

void setup()
{
 /* Initialize Ultrasound Pin Modes */
 pinMode(trigPin1, OUTPUT); // Trigger PIN1
 pinMode(echoPin1, INPUT); // Echo PIN1

 pinMode(trigPin2, OUTPUT); // Trigger PIN2
 pinMode(echoPin2, INPUT); // Echo PIN2

 /* Initialize Motor A Pin Modes */
  pinMode (enableA, OUTPUT);
  pinMode (pinA1, OUTPUT);
  pinMode (pinA2, OUTPUT);  
  
 /* Initialize Motor B Pin Modes */  
  pinMode (enableB, OUTPUT);
  pinMode (pinB1, OUTPUT);
  pinMode (pinB2, OUTPUT);  
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
  Serial.println("/");
 

}


void loop()
{
// Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = 0;
  if (request.indexOf("/MOTOR=FORWARD") != -1)  {
    goForward();
    value = 1;
    checkdistance();
    delay(1);
  }
  if (request.indexOf("/MOTOR=BACKWARD") != -1)  {
    goBack();
    value = 2;
    checkdistance();
    delay(1);
  }
  if (request.indexOf("/MOTOR=LEFT") != -1)  {
    turnLeft();
    value = 3;
    checkdistance();
    delay(1);
  }
  if (request.indexOf("/MOTOR=RIGHT") != -1)  {
    turnRight();
    value = 4;
    checkdistance();
    delay(1);
  } 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Motor is now: ");
 
  if(value == 1) {
    client.print("Forward");
  } else if(value == 2){
    client.print("Backward");
  }else if(value == 3){
    client.print("Left");
  }else{
    client.print("Right");
  }
  client.println("<br><br>");
  client.println("<a href=\"/MOTOR=FORWARD\"\"><button>UP</button></a>");
  client.println("<a href=\"/MOTOR=BACKWARD\"\"><button>DOWN</button></a><br />");  
  client.println("<a href=\"/MOTOR=LEFT\"\"><button>LEFT</button></a>");
  client.println("<a href=\"/MOTOR=RIGHT\"\"><button>RIGHT</button></a><br />");  
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 }

void checkdistance()
{
  //check the distance
  distance1 = checkDistance1(); 
  distance2 = checkDistance2();
  Serial.println(distance1);
  Serial.println(distance2);
  
  //if distance is less that 30 cm
  if(distance1 < 30 || distance2 < 30)
  {
    Serial.println("menor");
    //stop car, turn wheels right and go back for 500 ms. Then stop
    stopMotorB();
    stopMotorA();
  }
}
//function to calcutate the distance to an obstacle
long microsecondsToCentimeters (long microseconds) {
 // The speed of sound is 340 m/s or 29 microseconds per centimeter
 // The ping travels forth and back, so, the distance is half the distance traveled
 return microseconds / 29 / 2;
}

//function to check the distance of an obstacle
long checkDistance1()
{
 /* The following trigPin/echoPin cycle is used to determine the distance of the nearest
 object by bouncing soundwaves off it */
 //Trigger a HIGH pulse for 2 or more microseconds
 //Give a short LOW pulse before sending a HIGH one
 
 digitalWrite (trigPin1, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 digitalWrite (trigPin1, LOW);
 //Now, lets read the read the bounced wave
 duration1 = pulseIn(echoPin1, HIGH);
 //calculate the distance
 distance1 = microsecondsToCentimeters(duration1);
 
 return distance1;
}

long checkDistance2()
{
 /* The following trigPin/echoPin cycle is used to determine the distance of the nearest
 object by bouncing soundwaves off it */
 //Trigger a HIGH pulse for 2 or more microseconds
 //Give a short LOW pulse before sending a HIGH one
 
 digitalWrite (trigPin2, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite (trigPin2, LOW);
 //Now, lets read the read the bounced wave
 duration2 = pulseIn(echoPin2, HIGH);
 //calculate the distance
 distance2 = microsecondsToCentimeters(duration2);
 
 return distance2;
}

//function to go forward
void goForward()
{
  //Enable Motor B
  digitalWrite (enableB, HIGH);
  //forward
  digitalWrite (pinB1, LOW);
  digitalWrite (pinB2, HIGH);
}

//function to stop Motor B movement
void stopMotorB()
{
  digitalWrite(enableB, LOW);
}

//function to go back
void goBack()
{
  //Enable Motor B
  digitalWrite (enableB, HIGH);  
  //back
  digitalWrite (pinB1,HIGH);
  digitalWrite (pinB2,LOW);  
}

//function to stop Motor A movement
void stopMotorA()
{
  digitalWrite (enableA, LOW);
}

//function to turn the RC car right
void turnRight()
{
  //Enable Motor A  
  digitalWrite (enableA, HIGH);
  //right  
  digitalWrite (pinA1, LOW);
  digitalWrite (pinA2, HIGH);  
}

//function to turn the RC car left
void turnLeft()
{
  //Enable Motor A  
  digitalWrite (enableA, HIGH);  
  //left
  digitalWrite (pinA1,HIGH);
  digitalWrite (pinA2,LOW);  
}





 
