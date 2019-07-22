#include "RFID.h"
#include "server.h" // Se agrega esta linea para datos de ssidd, password y servidor MQTT

MQTT mqtt;
Identificador sensor;

int id;

void setup(){
  Serial.begin(115200);
  mqtt.begin(red, pass, server);
  mqtt.IP();
  mqtt.Reconectar(topic_publish);
  sensor.begin();
}

void loop(){
  mqtt.Reconectar(topic_publish);
  id = sensor.Escanear();
  if(id != 0){
    Serial.print("Identificador: ");
    Serial.println(id);
    sprintf(identificador, "Objeto. ID: %d", id);
    mqtt.Publicar(topic_publish, identificador);
  }else if(id == -1){
    Serial.print("Tarjeta ya leida");
  }
}
