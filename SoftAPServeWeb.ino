#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>Hello my name is ELeazar Federio</h1><br>
<hr>
</center>

</body>
</html>
)=====";

void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}

void setup()
{
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

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}