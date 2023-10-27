#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
int led = LED_BUILTIN;

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<center>
<h1>Smart Farm</h1>

<h3> LED </h3>
<button onclick="window.location = 'http://'+location.hostname+'/led/on'">On</button><button onclick="window.location = 'http://'+location.hostname+'/led/off'">Off</button>
</center>
</body>
</html>

)=====";

void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}

void handleLedOn() {
 Serial.println("Turn on LED");
 digitalWrite(led, LOW);
 server.send(200, "text/html", MAIN_page); 
}

void handleLedOff() {
 Serial.println("Turn Off LED");
 digitalWrite(led, HIGH);
 server.send(200, "text/html", MAIN_page); 
}

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  Serial.println();

  boolean result = WiFi.softAP("myWiFi", "password");
  if(result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  
  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}