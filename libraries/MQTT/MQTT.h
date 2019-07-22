#ifndef __MQTT__h__
#define __MQTT__h__

//#include <WiFi.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


class MQTT{
  char* ssid;
  char* password;
  char* mqtt_server;

  WiFiClient esp;
  PubSubClient client;

  IPAddress ip;

  long lastMsg = 0;
  char msg[50];

public:
    MQTT() = default;
    void begin(char* ssid, char* password, char* mqtt);
    String IP();
    void Reconectar(char* topic);
    void Publicar(char* topic, char* mensaje);
    void Suscribir(char* topic);
    ~MQTT() = default;
};

#endif
