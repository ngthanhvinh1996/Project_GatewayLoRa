
void setupWiFi(){
  Serial.println("Connecting to AP ....");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void callback(const char* topic, byte* payload, unsigned int length){
  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';

   Serial.println("Topic: ");
   Serial.println(topic);

   Serial.println("Message: ");

   Serial.println(json);

   StaticJsonBuffer<200> jsonBuffer;

   JsonObject &data = jsonBuffer.parseObject((char*)json);

   if(!data.success()){
    Serial.println("parseObject() failed");
    return;
   }

   String methodName = String((const char*)data["method"]);
   if(methodName.equals("R1")){
    if(data["params"]==true){
      control = 'A';
      sendLoRaMessage();
      gpioStatus[0] = true;
    }
    else{
      control = 'a';
      sendLoRaMessage();
      gpioStatus[0]=false;
    }
   }
/*******************************************/
  if(methodName.equals("R2")){
    if(data["params"]==true){
      control1 = 'B';
      sendLoRaMessage();
      gpioStatus[1] = true;
    }
    else{
      control1 = 'b';
      sendLoRaMessage();
      gpioStatus[1]=false;
    }
   }
/*******************************************/
  if(methodName.equals("R3")){
    if(data["params"]==true){
      control1 = 'C';
      sendLoRaMessage();
      gpioStatus[2] = true;
    }
    else{
      control1 = 'c';
      sendLoRaMessage();
      gpioStatus[2]=false;
    }
   } 
/*******************************************/
  if(methodName.equals("R4")){
    if(data["params"]==true){
      control1 = 'D';
      sendLoRaMessage();
      gpioStatus[3] = true;
    }
    else{
      control1 = 'd';
      sendLoRaMessage();
      gpioStatus[3]=false;
    }
   }
/*******************************************/
  if(methodName.equals("R5")){
    if(data["params"]==true){
      control1 = 'E';
      sendLoRaMessage();
      gpioStatus[4] = true;
    }
    else{
      control1 = 'e';
      sendLoRaMessage();
      gpioStatus[4]=false;
    }
   }
/*******************************************/
  if(methodName.equals("R6")){
    if(data["params"]==true){
      control1 = 'F';
      sendLoRaMessage();
      gpioStatus[5] = true;
    }
    else{
      control1 = 'f';
      sendLoRaMessage();
      gpioStatus[5]=false;
    }
   }
/*******************************************/
if(methodName.equals("R7")){
    if(data["params"]==true){
      control = 'G';
      sendLoRaMessage();
      gpioStatus[6] = true;
    }
    else{
      control = 'g';
      sendLoRaMessage();
      gpioStatus[6]=false;
    }
   }
/*******************************************/
  client.publish("v1/devices/me/attributes", get_gpio_status().c_str());
   
}

void reconnect(){
  while(!client.connected()){
    status = WiFi.status();
    if(status != WL_CONNECTED){
      WiFi.begin(ssid, password);
      while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.println("Connecting to Thingsboard node...");
    if(client.connect(DEVICE_ID, TOKEN, NULL)){
      Serial.println("[DONE]");
      client.subscribe("v1/devices/me/rpc/request/+");
      client.publish("v1/devices/me/attributes", get_gpio_status().c_str());
    }
    else{
      Serial.print("[FAILED] [rc = ");
      Serial.print(client.state());
      Serial.println(" : retrying 5 seconds]");
      delay(5000);
    }
  }
}

String get_gpio_status(){
  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& data = jsonBuffer.createObject();

  data["R1"] = gpioStatus[0] ? true : false;
  data["R2"] = gpioStatus[1] ? true : false;
  data["R3"] = gpioStatus[2] ? true : false;
  data["R4"] = gpioStatus[3] ? true : false;
  data["R5"] = gpioStatus[4] ? true : false;
  data["R6"] = gpioStatus[5] ? true : false;
  data["R7"] = gpioStatus[6] ? true : false;
  char payload[256];
  data.printTo(payload, sizeof(payload));
  String strPayload = String(payload);
  Serial.println("Get gpio status: ");
  Serial.println(strPayload);
  return strPayload;
}
