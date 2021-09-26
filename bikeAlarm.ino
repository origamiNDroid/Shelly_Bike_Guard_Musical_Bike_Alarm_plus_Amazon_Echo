#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "SamHomeWiFiCredentials.h" //ssid name and password
#include "ifttt_webhooks_api_key.h" // ifttt url resource
#define LIS3DH_CS D2 //ESP8266 Serial Data 
#define LIS3DH_CLK D1 //ESP8266 Serial Clock
#define TAMPERTHRESHOLD 10

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

//const int analogInPin = 0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from acc
int outputValue = 0;        // value sent to server
int prevValue = 0;
int currValue = 0;
bool counter = false;

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
void makeIFTTTRequest(void); //prototype
void initWifi(void);
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Upload successful");
  initWifi();
  //makeIFTTTRequest();
  ///////////////////////////////////////////////////////
  // Explicitly set the ESP8266 to be a WiFi-client
  
  if (! lis.begin(0x18)) 
  {
    Serial.println("Couldn't start");
    while (1) yield();
  }
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
}

void loop() {
  // read the analog in value:
  lis.read();
  sensorValue = lis.x;
  outputValue = map(sensorValue, -32768, 32767, 0, 999);
  currValue = outputValue;
  int difference = abs(prevValue - currValue);
  if((difference > TAMPERTHRESHOLD)&& (counter == true)){
    makeIFTTTRequest();
  }
  counter = true;
  prevValue = currValue;
  delay(500);
}

// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

void makeIFTTTRequest() {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  /*int retries = 20;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
     Serial.println("Failed to connect, going back to sleep");
  }*/
   if (!client.connect(server, 80)) {
    Serial.println(" connection failed");
    return;
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);
  client.print(String("GET ") + resource + 
                  " HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" + 
                  "Connection: close\r\n\r\n");
                  
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
     Serial.println("No response, going back to sleep");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop();
}
