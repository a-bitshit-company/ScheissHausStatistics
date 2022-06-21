#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
//Wifi
char* ssid = "HTLInn"; 
char* password =  "kpalda";

//mqtt
char* mqtt_server = "69.69.69.69";
char* mqttUser = "eapcfltj";
char* mqttPassword = "3EjMIy89qzVn";

//time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

char* location = "HTL";
const int id = 0;
const int lvl = 1;

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

}

boolean occupied = false;
void loop(){
  if (!client.connected()) {
        reconnect();
    }
  client.loop();
  
  if(1==0){  //TODO: "1==0" code für Sensor wenn dieser gertriggered wird
    occupied = !occupied;
    client.publish(location, getData(occupied));
  }
}

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

time_t getLocalTime()
{
  struct tm * timeinfo;
  if(!getLocalTime(timeinfo)){
    Serial.println("Failed to obtain time");
    return NULL;
  }
    return mktime(timeinfo);
}

char* getData(boolean occ){
  char* curTime = "bla bla serverzeug";
  char* kData;
  sprintf(kData,"%s %b", curTime, occ);
  return kData;
} 

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESPClient")) {
      Serial.println("connected");
      client.subscribe(location);
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
}
