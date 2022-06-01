#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* ssid = "HTLInn"; // Enter your WiFi name
const char* password =  "kpalda"; // Enter WiFi password
const char* mqtt_server = "69.69.69.69";
const char* mqttUser = "eapcfltj";
const char* mqttPassword = "3EjMIy89qzVn";

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
	Serial.begin(9600);
	setup_wifi();
	client.setServer(mqtt_server, 1883);
  	client.setCallback(callback);

}



void loop(){
	if (!client.connected()) {
    		reconnect();
  	}
	client.loop();
}

void reconnect() {
 
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, status: ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

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
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

