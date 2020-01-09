#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <LoRa.h>

////LoRa
#define LORA_SS D8
#define LORA_RST D3
#define LORA_DIO D2

//wifi
#define ssid "giangduong"
#define password "vunguyen"

//Thingsboard
#define TOKEN "QjyfH4v5ny59zIfUuqre"
#define DEVICE_ID "acf96040-05c2-11ea-92a6-551aaa17a065"
//LoRa
#define LORA_SF 12 // 12
#define LORA_CR 4
#define LORA_BW 125E3 //62.5E3 41.7E3 125E3
#define LORA_PREAMBLE_LENGTH 8
#define LORA_FREQ 433E6

#define BAUD_RATE 115200
