#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define sensorPin1 0
int hts=1, vels=1;

char ssid[] = "Do Not Connect";                 // Network Name
char pass[] = "abcd1234";                 // Network Password
byte mac[6];

char server[] = "192.168.43.140";
IPAddress ip(192, 168, 43, 175);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiClient client;

unsigned long myChannelNumber = 755824;
const char * myWriteAPIKey = "N3MEOPZ2NHSIATJC";

void setup() {

  Serial.begin(9600);
  Serial.println("Initialising connection");
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);

  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  ThingSpeak.begin( client );

}

void loop() {
  ThingSpeak.setField( 1, hts );
  ThingSpeak.setField( 2, vels );
  ThingSpeak.writeFields( myChannelNumber, myWriteAPIKey );

  delay(60000); //3 sec
hts++;
vels++;

  Serial.println("Recording data.");
}
