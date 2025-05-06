#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <PubSubClient.h>

void reconnect();

Adafruit_BME280 bme; // I2C

const char* ssid = "Oshadha's Galaxy Tab S6 Lite";
const char* password = "bxmu1409";
const char* mqtt_server = "192.168.155.149";

long lastMsg = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  delay(100);

  // Start the serial communication
  Serial.begin(115200);

  // Start the BME280 sensor
  Serial.println(F("BME280 test"));

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("BME280 sensor connected successfully");
  Serial.println();

  // Connect to the wifi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to the MQTT broker
  client.setServer(mqtt_server, 1883);
}

void loop() {
  // Reconnect to the MQTT broker
  if (!client.connected()) {
    reconnect();
  }

  StaticJsonDocument<80> doc;
  char output[80];

  // Publish the sensor data every 5 seconds
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    // Read the sensor data
    float temp = bme.readTemperature();
    float pressure = bme.readPressure()/100.0;
    float humidity = bme.readHumidity();

    // Add the sensor data to the JSON document
    doc["t"] = temp;
    doc["p"] = pressure;
    doc["h"] = humidity;

    // Serialize the JSON document
    serializeJson(doc, output);

    // Print the JSON document
    Serial.println(output);
    client.publish("/home/sensor", output);
  }
    
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}
