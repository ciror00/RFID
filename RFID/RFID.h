#include "Identificador.h"
#include "MQTT.h"

// Se tiene que descomentar y cargar con los datos correspondientes.
//char* red = "";
//char* pass = "";
//char* server = "";

char* topic_estado = "planta/circulo/rfid/autorizacion";
char* topic_rfid = "planta/circulo/rfid/id";

char identificador[16];
