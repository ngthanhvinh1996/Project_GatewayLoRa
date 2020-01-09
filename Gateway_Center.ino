#include "Gateway_Center.h"

byte localAddress = 0xFF; //dia chi gateway 
byte destination = 0xA2; //dia chi muon gui
byte recipient;
byte recipient1;
byte sender;

int bien, bien1;


char control, control1;
int value_gas;
int value_Light;
int tem;
int hum;

unsigned long lastSend;
long lastMsg = 0;
char msg[5];
int value = 0;
char thingsboardServer[] = "demo.thingsboard.io";

WiFiClient wifiClient;

int status = WL_IDLE_STATUS;

PubSubClient client(wifiClient);

boolean gpioStatus[] = {false,false,false,false,false,false,false};
void setup() {
  Serial.begin(BAUD_RATE);
  delay(100);
  setupWiFi();
  delay(100);
  setupLoRa();
  lastSend = 0;
  client.setServer(thingsboardServer,1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()){
    reconnect();
  }
  SendThingsboard();
  client.loop();
}

void SendThingsboard(){
  String message = receiveLoRaMessage();
  if(message != ""){
    message += "\"R\":";message += String(LoRa.packetRssi());message += ",";
    message += "\"S\":";message += String(LoRa.packetSnr());message += "}";
    char attributes[100];
    message.toCharArray(attributes, 100);
    Serial.println(message);
    client.publish("v1/devices/me/telemetry", attributes);
    Serial.println(attributes);
  }
}
