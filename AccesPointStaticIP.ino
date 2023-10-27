#include <ESP8266WiFi.h>

const char* ssid     = "myWiFi";	    // Replace with SSID
const char* password = "password";	// Replace with WiFi Password

IPAddress subnet(255, 255, 0, 0);			            // Subnet Mask
IPAddress gateway(192, 168, 1, 1);			            // Default Gateway
IPAddress local_IP(192, 168, 1, 184);			        // Static IP Address for ESP8266

void setup() {
  Serial.begin(115200);

  if (WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Static IP Configured");
  }
  else {
    Serial.println("Static IP Configuration Failed");
  }
  
  WiFi.begin(ssid, password);

  Serial.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected! IP address:");
  Serial.println(WiFi.localIP());
}

void loop(){

  // YOUR CODE HERE //

}