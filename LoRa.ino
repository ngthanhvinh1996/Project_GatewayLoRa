
void setupLoRa(){
  Serial.println("[LoRa] Setting up LoRa");

  SPI.begin();
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO);
  while(!LoRa.begin(LORA_FREQ)){
    Serial.println("[LoRa] Starting LoRa failed");
    delay(1000);
  }

  LoRa.setSpreadingFactor(LORA_SF);
  LoRa.setCodingRate4(LORA_CR);
  LoRa.setSignalBandwidth(LORA_BW);
  LoRa.setPreambleLength(LORA_PREAMBLE_LENGTH);

  LoRa.enableCrc();
}

String receiveLoRaMessage(){
  int packetSize = LoRa.parsePacket();
  if(packetSize == 0) return "";

  recipient = LoRa.read();
  sender = LoRa.read();
  if(recipient != localAddress){
    Serial.println("This message not for me.");
    return "";
  }
  String incoming = "";
  while(LoRa.available()){
    incoming += (char)LoRa.read();
  }
  
    Serial.println("Received from: 0x"+String(sender,HEX));
    Serial.println("Send to: 0x"+String(recipient,HEX));
    Serial.println("RSSI: " + String(LoRa.packetRssi()));
    Serial.println("Snr: " + String(LoRa.packetSnr()));
//  }
  return incoming;
}

void sendLoRaMessage(){
//  Serial.println("[GW] Sending Packet: " + outgoing);
  LoRa.beginPacket();
  LoRa.write(destination);
  LoRa.write(localAddress);
  LoRa.write(control);
  LoRa.write(control1); 
//  LoRa.print(outgoing);
  LoRa.endPacket();
}
