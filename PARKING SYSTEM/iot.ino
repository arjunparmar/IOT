#include <ArduinoJson.h>


//libraries used

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <ESP8266WiFi.h>

//definations
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

//global declarations
const char* ssid = "xyz";
const char* password = "12345678";
int sensor[3]={12,13,14};

//server specified
WiFiServer server(8080);
 
void set_wifi() //wifi function (To be called in setup)
{
  WiFi.begin(ssid,password);
  Serial.print("connecting to....");
  Serial.println(ssid);
  while(WiFi.status() != WL_CONNECTED)
    {
      delay(500);
    }
  Serial.println(".");
  Serial.println("Wifi connected");
  Serial.println("server is started");
  Serial.print("using this url to connect:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void set_firebase() //Firebase function (To be called in setup)
{
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH); 
  Firebase.setInt("Value",0);
}

void firebasereconnect() //Reconnect function if auth. fails at first  
{
    Serial.println("trying to reconnect");
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}
  void setup() 
{ 
  Serial.begin(115200);
  set_wifi();
  set_firebase();

  //setting pins
  pinMode(sensor[0],INPUT); //irsensor1
  pinMode(sensor[1],INPUT); //irsensor2
  pinMode(sensor[2],INPUT); //parked notifying leds
 // pinMode(sensor[3],INPUT);
}

void loop() 
{ 
  while (Firebase.failed())
    {
      Serial.print("Firebase connection error:");
      Serial.println(Firebase.error());
      firebasereconnect();
    }
  int data1=digitalRead(sensor[0]);
  int data2=digitalRead(sensor[1]);
  int data3=digitalRead(sensor[2]);
  Firebase.setInt("/slot1",data1); //setting parked or not digitally to firebase 
  Firebase.setInt("/slot2",data2);
  Firebase.setInt("/slot3",data3);
  /*if(data1==1)
  {
  digitalWrite(showled1,HIGH);
  delay(1000);
  digitalWrite(showled1,LOW);
  }
  if(data2==1)
  {
  digitalWrite(showled2,HIGH);
  delay(1000);
  digitalWrite(showled2,LOW);  
  }*/
}
