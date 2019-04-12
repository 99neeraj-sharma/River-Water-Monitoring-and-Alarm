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

char user[] = "user";           // MySQL user
char password[] = "local";       // MySQL password

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

}

void loop() {
  if (client.connect(server, 80)) 
      {
      Serial.println("Connection Established 2");
      client.print("GET /info.php?"); //GET request to write data to the database.
      client.print("hght=");
      client.print(hts);
      client.print("&");
      client.print("velocity=");
      client.print(2*vels);
      client.println(" HTTP/1.1"); 
      client.println("Host: 192.168.43.140"); 
      client.println("Connection: close"); 
      client.println(); 
      client.println(); 
      client.stop();
      Serial.println(hts, vels);
      }
      else
      {
        Serial.println("Connection failed 2");
      }

  delay(3000); //3 sec
hts++;
vels++;

  Serial.println("Recording data.");
}
