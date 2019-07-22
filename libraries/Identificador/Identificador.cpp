#include "Identificador.h"

void Identificador::begin(){
  SPI.begin();
  this->rfid.PCD_Init();
  for (byte i = 0; i < 6; i++) {
    this->key.keyByte[i] = 0xFF;
  }
}

long Identificador::Escanear(){
  // Buscar tarjetas
  if ( ! this->rfid.PICC_IsNewCardPresent())
    return 0;
  // Verificar si la tarjeta ha sido leída.
  if ( ! this->rfid.PICC_ReadCardSerial())
    return -1;

  Serial.print(F("Proximity Integrated Circuit Card (PICC). Tipo: "));
  piccType = this->rfid.PICC_GetType(this->rfid.uid.sak);
  Serial.println(this->rfid.PICC_GetTypeName(piccType));

  // Chequea si el tag es del tipo MIFARE Classic
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
      Serial.println(F("El tag no es del tipo MIFARE Classic."));
      return -1;
  }

  if (this->rfid.uid.uidByte[0] != nuidPICC[0] ||
      this->rfid.uid.uidByte[1] != nuidPICC[1] ||
      this->rfid.uid.uidByte[2] != nuidPICC[2] ||
      this->rfid.uid.uidByte[3] != nuidPICC[3] ) {
      Serial.println(F("Nueva tarjeta."));

      // Almacena NUID en la matriz nuidPICC
      for (byte i = 0; i < 4; i++) {
        nuidPICC[i] = this->rfid.uid.uidByte[i];
      }
      char buffer[16];
      sprintf(buffer, "%d%d%d%d", nuidPICC[0], nuidPICC[1], nuidPICC[2], nuidPICC[3]);
      tag_id = atol(buffer);
      //return tag_id;
  }else{
    Serial.println(F("Tarjeta leída previamente."));
    //return tag_id;
  }

  // Halt PICC
  this->rfid.PICC_HaltA();

  // Stop encryption on PCD
  this->rfid.PCD_StopCrypto1();

  return tag_id;
}
/*
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
*/
