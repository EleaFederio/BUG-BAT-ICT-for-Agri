int soilMoistureSensorPin = A0;

void setup() {
  pinMode(soilMoistureSensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  float sensorReading = analogRead(soilMoistureSensorPin);
  // update the 3rd parameter of the map function depending on the sesitivity of your moisture sensor
  float moistureContent = map(sensorReading, 1024, 633, 0, 100);
  Serial.print("Soil Moisture ");
  Serial.print(moistureContent);
  Serial.println("%");
  delay(1000);
}