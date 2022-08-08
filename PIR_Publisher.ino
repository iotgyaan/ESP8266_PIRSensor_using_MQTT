#include <ESP8266WiFi.h>
#include <PubSubClient.h>
      
int inputPin = 2;           
int pirState = LOW;             
int val = 0; 

const int redledPin = 12;

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const char* mqtt_server = "YOUR IP";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
      client.subscribe("room/lamp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  
  Serial.begin(115200);
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(redledPin, OUTPUT);
  
  setup_wifi();
  client.setServer(mqtt_server, 21080);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  val = digitalRead(inputPin);  
  
  if (val == HIGH) {           
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      digitalWrite(redledPin, HIGH);
      pirState = HIGH;

      client.publish("esp/pir/topic", "ON");      
    }
  } else {  
    if (pirState == HIGH) {
      Serial.println("Motion ended!");
      digitalWrite(redledPin, LOW);
      pirState = LOW;

      client.publish("esp/pir/topic", "OFF");
    }
  }   
} 
