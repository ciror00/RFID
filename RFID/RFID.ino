#include "RFID.h"
#include "server.h" // Se agrega esta linea para datos de ssidd, password y servidor MQTT

MQTT mqtt;
Identificador sensor;

int id;

void setup(){
  Serial.begin(115200);
  mqtt.begin(red, pass, server);
  mqtt.IP();
  sensor.begin();
  mqtt.Publicar(topic_estado, "RFID Conectado");
}

void loop(){
  mqtt.Reconectar(topic_estado);
  id = sensor.Escanear();
  if(id != 0){
    Serial.print("Identificador: ");
    Serial.println(id);
    sprintf(identificador, "%d", id);
    mqtt.Publicar(topic_rfid, identificador);
  }else if(id == -1){
    Serial.print("Tarjeta ya leida");
  }
}
