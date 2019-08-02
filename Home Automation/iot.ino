#include <ArduinoJson.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
const char* ssid = "";
const char* password = "";

int ledpin[3] = {12,13,14}; // D7 on nodemcu
WiFiServer server(80);
void firebasereconnect()
  {
    Serial.println("trying to reconnect");
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
    return;
  }
void setup() {
  int i=0;
  // put your setup code here, to run once:
  Serial.begin(115200);
  for(i=0;i<3;i++)
  {
  pinMode(ledpin[i],OUTPUT);
  digitalWrite(ledpin[i], LOW);
  }

  //connect to WiFi
  Serial.print("connecting to....");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED)
  {delay(50);
  }

  Serial.println(".");
  Serial.println("Wifi connected");


  //server starting
  server.begin();
  Serial.println("server is started");

  //ip address
  Serial.print("use this url to connect:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  //firebase 
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("Value",0);

   

  
  }

void loop() {
  // put your main code here, to run repeatedly:
  int vall[3],j=0,i=0;
  int stat[3];
  if (Firebase.failed())
  {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    //firebasereconnect();
    return;
  }

   vall[0]=Firebase.getInt("stat[0]");
   vall[1]=Firebase.getInt("stat[1]"); 
   vall[2]=Firebase.getInt("stat[2]");

for(j=0;j<3;j++)
  {
  if(vall[j]==0)
  {
    digitalWrite(ledpin[j],LOW);
    Serial.println("led is off");
  }
  else if(vall[j]==1)
  {
    digitalWrite(ledpin[j],HIGH);
    Serial.println("led is on");
  }
  }
}
