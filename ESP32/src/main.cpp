#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <PubSubClient.h>

#define SeaLevelPreasure_HPA (1013.25)

Adafruit_BME280 bme;

const char* ssid = "Oshadha's Galaxy Tab S6 Lite";
const char* password = "bxmu1409";
const char* mqtt_server = "xxxx";

void setup() {
  Serial.begin(115200);
  Serial.println(F("BME280 test"));

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("BME280 sensor connected successfully");
  Serial.println();
}

void loop() {

}

void reconnect() {

}