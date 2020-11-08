#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "water-monitor-8a78b.firebaseio.com" //--> URL address of your Firebase Realtime Database.
#define FIREBASE_AUTH "MiXOMtq5vkFBtj6e1QF2AZGPhsS8kIDgMxXL4XxW" //--> Your firebase database secret code.
#define ON_Board_LED 2 
const char* ssid = "test";
const char* password = "goPOWER1";
const int trigPin = 14;
const int echoPin = 12;
long duration;
int distance;

void setup() {
  
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
  delay(500);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
    
  pinMode(ON_Board_LED,OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH);
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance= (duration*0.034/2)+3;
  Serial.print("Distance: ");
  Serial.println(distance);

  
  Firebase.setInt("/Distance",distance);

  if (Firebase.failed()) { 
      Serial.print("Setting /Value failed :");
      Serial.println(Firebase.error());  
      delay(500);
      return;
  }

  Serial.println("Setting successful");
  Serial.println();

  //----------------------------------------Command or code to get data from Firebase Realtime Database.
  /*
  Serial.print("Value : ");
  Serial.println(Firebase.getString("RandomVal/Value")); //--> Command or code to get data (String data type) from Firebase Realtime Database.

  // Conditions for handling errors.
  if (Firebase.failed()) { 
      Serial.print("Getting /Value failed :");
      Serial.println(Firebase.error()); 
      delay(500); 
      return;
  }
  
  //----------------------------------------
  */
  delay(1000);
  
}
