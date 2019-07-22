#ifndef __IDENTIFICADOR__h__
#define __IDENTIFICADOR__h__

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 5;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 4;     // Configurable, see typical pin layout above

enum Sistema{
    HEXA,
    DECI,
    IDU
};

class Identificador{
  MFRC522 rfid = MFRC522(SS_PIN, RST_PIN); // Instance of the class
  MFRC522::MIFARE_Key key;
  MFRC522::PICC_Type piccType;

  byte nuidPICC[4];
  long tag_id;

  public:
      Identificador() = default;
      void begin();
      long Escanear();
      ~Identificador() = default;
};

#endif
