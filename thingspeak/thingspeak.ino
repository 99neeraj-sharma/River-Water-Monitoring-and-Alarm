#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>

#define sensorPin1 0
int hts=1, vels=1;

char ssid[] = "Do Not Connect";                 // Network Name
char pass[] = "abcd1234";                 // Network Password
byte mac[6];

char server[] = "192.168.43.140";
byte thingspeakServer[] = { 184, 106, 153, 149 }; 
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
  String dataStr;
        dataStr  = "api_key=";
        dataStr += myWriteAPIKey;
        dataStr += "&field1=";
        dataStr += floatToString(hts,  4);
        dataStr += "&field2=";
        dataStr += floatToString(vels, 4);
        client.connect(thingspeakServer, 80);
        client.println(F("POST  /update.json HTTP/1.1"));
        client.println(F("host:api.thingspeak.com"));
        client.println(F("Connection: close"));
        client.println(F("Content-Type: application/x-www-form-urlencoded"));
//        Client.println(F("User-agent: ELEN215-Arduino"));
        client.println(F("Accept: */*"));
        client.print(F("Content-length: "));
        client.println(dataStr.length());                                      
        client.println();
        client.println(dataStr);
        // was thingspeakClient.print(dataStr);  // but also \n was appended to dataStr
        
        Serial.println(F("POST  /update.json HTTP/1.1"));
        Serial.println(F("host: api.thingspeak.com"));
        Serial.println(F("Connection: close\n"));
        Serial.println(F("Content-Type: application/x-www-form-urlencoded"));
        Serial.println(F("User-agent: ELEN215-Arduino"));
        Serial.println(F("Accept: */*"));
        Serial.print(F("Content-length: "));
        Serial.println(dataStr.length());                                      
        Serial.println();
        Serial.println(dataStr);
  ThingSpeak.setField( 1, hts );
  ThingSpeak.setField( 2, vels );
  ThingSpeak.writeFields( myChannelNumber, myWriteAPIKey );

  delay(60000); //3 sec
hts++;
vels++;

  Serial.println("Recording data.");
}
String floatToString(double number, uint8_t digits) 
{ 
  String resultString = "";
  // Handle negative numbers
  if (number < 0.0)
  {
    resultString += "-";
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  resultString += int_part;

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    resultString += "."; 

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    resultString += toPrint;
    remainder -= toPrint; 
  } 
  return resultString;
}
