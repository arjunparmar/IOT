
//libraries used
#include <ArduinoJson.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <ESP8266WiFi.h>

//definations
#define FIREBASE_HOST "arraydata-2396a.firebaseio.com"
#define FIREBASE_AUTH "6MjKdwhrABSOez25bll4UM971OnbpHhxNfASWlZP"

//global declarations
const char* ssid = "xyz";
const char* password = "12345678";
int showled1=14;
int showled2=15;
int sensor1=13;
int sensor2=12;

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
  pinMode(sensor1,INPUT); //irsensor1
  pinMode(sensor2,INPUT); //irsensor2
  pinMode(showled1,OUTPUT); //parked notifying leds
  pinMode(showled2,OUTPUT);
}

void loop() 
{ 
  while (Firebase.failed())
    {
      Serial.print("Firebase connection error:");
      Serial.println(Firebase.error());
      firebasereconnect();
    }
  int data1=digitalRead(sensor1);
  int data2=digitalRead(sensor2);
  Firebase.setInt("/data1",data1); //setting parked or not digitally to firebase 
  Firebase.setInt("/data2",data2);
  if(data1==1)
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
  }
}
