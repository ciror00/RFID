#include "Identificador.h"
#include "MQTT.h"

// Se tiene que descomentar y cargar con los datos correspondientes.
//char* red = "";
//char* pass = "";
//char* server = "";

char* topic_publish = "servidor/publicaciones";
char* topic_subscribe = "servidor/notificaciones";

char identificador[16];
