#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>

// Data wire is plugged into port D4 on the Arduino
#define ONE_WIRE_BUS D4

const char* host = "api.thingspeak.com";
const char* host2 = "maker.ifttt.com";
String ApiKey = "X0H2CVES01LVUESN";
String IFTTTKEY = "omdodugR3B7rVgfpaGAgVvbbEYNkdri3X9zjV5YCcjM";
String EVENTO = "hot_temp";
const char* ssid = "iptime";
const char* pwd = "12341234";


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void connectWiFi()
{
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,pwd);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("\nConnected!, IP address is ");
  Serial.println(WiFi.localIP());
}

void sendTemperatureToThingspeak(float temp)
{
  WiFiClient client;
  
  /*
  if(!client.connect(host, 80)) {
    Serial.print("connection failed");
    Serial.print("\n");
    return;
  }
  */
  
  if(client.connect(host2, 80)) {
    Serial.println("WiFi Client connected");

    /* 이부분은 thingspeak로 측정온도값 쏘아보내기
    String path = ApiKey;
    path += "&field1=";
    path += String(temp);
    path += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + ApiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(path.length());
    client.print("\n\n");
    client.print(path);
    //delay(1000);
    */

    String toSend = "GET /trigger/";
    toSend += EVENTO;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += String(temp);
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += host2;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";

    client.print(toSend);
  }
  client.stop();
    //client.println(postStr);
    //client.println("User-Agent: Seongyun Kim");
    //client.println("Host: " + String(host));
    //client.println("Connection: close");
    //client.println();
    /*
    Serial.println(postStr);
    while(client.connected()) {
      String line = client.readStringUntil('\n');
      //Serial.println("what?");
      Serial.println(line);
    }
    */
}
void setup(void)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");
  connectWiFi();
  // Start up the library
  sensors.begin();
}
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));  

  sendTemperatureToThingspeak(sensors.getTempCByIndex(0));
  delay(5000);
}
