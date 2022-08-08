#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
 
const char *MQTT_HOST = "YOUR _IP";
const int MQTT_PORT = 1883;
const char *MQTT_CLIENT_ID = "ESP8266 NodeMCU"; 
const char *MQTT_USER = "user";
const char *MQTT_PASSWORD = "password";
const char *TOPIC = "esp/pir/topic";

const int ledPin = 2;
 
WiFiClient client;
PubSubClient mqttClient(client);
 
void callback(char* topic, byte* payload, unsigned int length)
{   
    String message;
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }   

    if (String(topic) == "esp/pir/topic") {
      if(message == "ON"){
        Serial.println("on");
        digitalWrite(ledPin, HIGH);
      }
      else if(message == "OFF"){
        Serial.println("off");
        digitalWrite(ledPin, LOW);
      }
    }   
}
 
void setup()
{
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
 
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("Connected to Wi-Fi");
 
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
    mqttClient.setCallback(callback);
 
    while (!client.connected()) {
        if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("Connected to MQTT broker");
        } else {
            delay(500);
            Serial.print(".");
        }
    }
 
    mqttClient.subscribe(TOPIC);
}
 
void loop()
{
    mqttClient.loop();
}
