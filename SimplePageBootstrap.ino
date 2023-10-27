#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">
<script src="https://kit.fontawesome.com/ed7ad1745f.js" crossorigin="anonymous"></script>
</head>
<body>
<div class="container">
<center>
<h3 class="mt-5">Plant Moisture Monitor</h3>
<p class="mt-5"><i class="fa-solid fa-seedling fa-2xl"></i></p>
</center>
<div class="progress mt-5" role="progressbar" aria-label="Success example" aria-valuenow="25" aria-valuemin="0" aria-valuemax="100">
  <div class="progress-bar bg-success" style="width: 25%">Moisture 25%</div>
</div>
<button type="button" class="btn btn-primary mt-5">Water Me</button>
</div>
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

  WiFi.begin("free_wifi", "SmartWifi123*");

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

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}