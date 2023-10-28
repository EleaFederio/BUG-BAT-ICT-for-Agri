#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
int led = LED_BUILTIN;

const char MAIN_page[] PROGMEM = R"=====(

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

  WiFi.begin("eliebird", "password");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
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