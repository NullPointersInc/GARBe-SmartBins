#include<ESP8266WiFi.h>

const char* server = "api.thingspeak.com";
//For SmartBin1
String apiKey ="PKLFMPCI43DDAYN2";

//For SmartBin2
//String apiKey ="O3QS6ONITRLAOU3U";

const char* MY_SSID = "Akash"; 
const char* MY_PWD = "astr1x2096";

#define trigger 13
#define echo 14

void setup() {
  Serial.begin(115200);
  connectWifi();
  pinMode(trigger, INPUT);
  pinMode(echo, OUTPUT);
}

void connectWifi()
{
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}//end connect

void loop() {
 postValue();
}

int checkLevel() {
  float distance, cent;
  int len = 20; //Assumed length of the box
  float level = 0.0;
  digitalWrite(trigger, LOW); //low pulse first to ensure a clean high pulse.
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delayMicroseconds(10);

  distance = pulseIn(echo, HIGH);
  // convert the time into a distance
  cent = microToCms(distance);
  //calculate percentage
  level = cent/len;
  level = 100 - level * 100;
  return ((int)level);
}

void postValue() {
   WiFiClient client;
  if(client.connect(server, 80)) {
   Serial.println("Wifi Client Connected");
   String postStr = apiKey;
   postStr += "&field1=";
   postStr += String(checkLevel());
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   delay(15000);
  }
}

long microToCms(long microseconds) {
  return microseconds / 29 / 2;
}
