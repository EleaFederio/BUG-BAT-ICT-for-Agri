#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
int led = LED_BUILTIN;

const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Bootstrap demo</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">
</head>
<body>
  <div class="container">
    <h1 class="h1 text-center mt-5">No Group</h1>
    <div class="d-grid gap-2 mt-5 ">
      <button class="btn btn-primary" onclick="window.location = 'http://'+location.hostname+'/led/on'" type="button">LED ON</button>
      <button class="btn btn-primary" onclick="window.location = 'http://'+location.hostname+'/led/off'" type="button">LED OFF</button>
    </div>
  </div>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-C6RzsynM9kWDrMNeT87bh95OGNyZPhcTNXj1NW7RuBCsyN/o0jlpcV8Qyq46cDfL" crossorigin="anonymous"></script>
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

  WiFi.begin("bat_wifi", "password");

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

void loop() {
  server.handleClient();
}