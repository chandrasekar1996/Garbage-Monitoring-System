#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>
#include <TinyGPS++.h>

const int trigPin = 0;
const int echoPin = 2;

const char* ssid = "santhosh";
const char* password = "Santhosh50";

unsigned long myChannelNumber=700554;
const char * MyApiKey="NWVTPD4RATM2VJY1";
TinyGPSPlus gps;  // The TinyGPS++ object

SoftwareSerial ss(4, 5);
long duration;
int distance;
float latitude , longitude;

String lat_str , lng_str;

WiFiClient client;
void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");


 
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 


  // Print the IP address
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);

}

void loop()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;
      if (gps.encode(ss.read()))
      {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
      }

     
      }

     Serial.print("distance:");
     Serial.println(distance);
     Serial.println(latitude);
     Serial.println(longitude);
     
  if(distance==35)
  {
      int empty=0;
      ThingSpeak.setField(1,empty);
      ThingSpeak.setField(2,lat_str);
      ThingSpeak.setField(3,lng_str);
      ThingSpeak.writeFields(myChannelNumber,MyApiKey); 
      Serial.println("Sensor Data is stored");
  }
  else if(distance==25)
  {
      int quarter=25;
      ThingSpeak.setField(1,quarter);
      ThingSpeak.setField(2,lat_str);
      ThingSpeak.setField(3,lng_str);
      ThingSpeak.writeFields(myChannelNumber,MyApiKey);
      Serial.println("Sensor Data is stored");
  }
  else if(distance==17)
  {
    int half=50;
    ThingSpeak.setField(1,half);
    ThingSpeak.setField(2,lat_str);
    ThingSpeak.setField(3,lng_str);
    ThingSpeak.writeFields(myChannelNumber,MyApiKey); 
    Serial.println("Sensor Data is stored");
   }
   else if(distance==10)
   {
    int mid_half=75;
    ThingSpeak.setField(1,mid_half);
    ThingSpeak.setField(2,lat_str);
    ThingSpeak.setField(3,lng_str);
    ThingSpeak.writeFields(myChannelNumber,MyApiKey); 
    Serial.println("Sensor Data is stored");
    }
}
