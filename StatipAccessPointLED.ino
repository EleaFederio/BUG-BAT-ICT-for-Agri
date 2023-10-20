#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress local_IP(192,168,0,1);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
int ledPin = LED_BUILTIN;
ESP8266WebServer server(80);

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>WiFi LED on off demo: 1</h1><br>
Ciclk to turn <a href="ledOn">LED ON</a><br>
Ciclk to turn <a href="ledOff">LED OFF</a><br>
<hr>
</center>

</body>
</html>
)=====";

void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleLEDon() { 
 Serial.println("LED on page");
 digitalWrite(ledPin,LOW);
 server.send(200, "text/html", "LED is ON");
}

void handleLEDoff() { 
 Serial.println("LED off page");
 digitalWrite(ledPin,HIGH);
 server.send(200, "text/html", "LED is OFF");
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println();

  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("the_wifi", "happyfeet", 1, false, 8) ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot); 
  server.on("/ledOn", handleLEDon);
  server.on("/ledOff", handleLEDoff);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
 server.handleClient();   
}

