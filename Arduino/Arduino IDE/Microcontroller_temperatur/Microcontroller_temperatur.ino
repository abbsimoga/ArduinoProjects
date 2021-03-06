#include <Wire.h>
#include <AM2320.h>

AM2320 sensor;

String sensorHeat = "50";
String sensorHum = "50";

void setup() {
  Serial.begin(9600);
  Wire.begin(12,13);
}

void getTemperature() {
  if (sensor.measure()) {
    Serial.print("Temperature: ");
    Serial.println(sensor.getTemperature());
    sensorHeat = sensor.getTemperature();
    sensorHum = sensor.getHumidity();
    Serial.print("Humidity: ");
    Serial.println(sensor.getHumidity());
  } else {
    int errorCode = sensor.getErrorCode();
    switch (errorCode) {
      case 1: Serial.println("ERR: Sensor is offline"); break;
      case 2: Serial.println("ERR: CRC validation failed."); break;
    }
  }
}

void loop() {
  delay(5000);
  getTemperature();
}
