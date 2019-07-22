#include "MQTT.h"

void MQTT::begin(char* ssid, char* password, char* mqtt_server){
  this->ssid = ssid;
  this->password = password;
  this->mqtt_server = mqtt_server;
  this->client.setClient(this->esp);
  WiFi.begin(this->ssid, this->password);
  Serial.println();
  Serial.print("Conectando.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado, IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Servidor MQTT: ");
  Serial.println(mqtt_server);
  this->client.setServer(mqtt_server, 1883);
}

String MQTT::IP(){
  String buffer;
  ip = WiFi.localIP();
  return String(ip[0]) + String(".") +\
    String(ip[1]) + String(".") +\
    String(ip[2]) + String(".") +\
    String(ip[3]);
}

void MQTT::Reconectar(char* topic) {
  if (!this->client.connected()) {
    while (!this->client.connected()){
      Serial.print("Intentando conexion MQTT. ");
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
      if (this->client.connect(clientId.c_str())) {
        Serial.println("Conectado");
        //this->client.publish(topic, "PING");
        //delay(1000);
        //this->client.subscribe(topic);
      }else{
        Serial.print("Error, state: ");
        Serial.print(client.state());
        Serial.println(". Volviendo a intentar en 5 segundos");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }
  this->client.loop();
}

void MQTT::Publicar(char* topic, char* mensaje){
  Serial.println(client.state());
  if (this->client.connected()) {
    Serial.println(topic);
    Serial.println(mensaje);
    this->client.publish(topic, mensaje);
  }
}

void MQTT::Suscribir(char* topic){
  if (this->client.connect("ESP8266Client")) {
    Serial.println("connected");
    this->client.subscribe("casa/despacho/luz");
  }else{
    Serial.print("Error=");
    Serial.print(client.state());
    Serial.println(" intentando nuevamente en 5 segundos.");
    // Wait 5 seconds before retrying
    delay(5000);
  }
}
