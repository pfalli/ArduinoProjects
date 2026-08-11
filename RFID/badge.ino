#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

byte card1[] = {0x03, 0xE6, 0xB8, 0xF7};
byte card2[] = {0x89, 0xFD, 0xF9, 0x03};

bool checkUID(byte expected[]) {
  if (rfid.uid.size != 4)
    return false;

  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != expected[i])
      return false;
  }

  return true;
}

void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("Access system ready");
  Serial.println("Scan RFID...");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  Serial.print("UID: ");

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10)
      Serial.print("0");

    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }

  Serial.println();

  // Check cards
  if (checkUID(card1)) {
    Serial.println("ACCESS GRANTED - CARD 1");
  }

  else if (checkUID(card2)) {
    Serial.println("ACCESS GRANTED - CARD 2");
  }

  else {
    Serial.println("ACCESS DENIED");
  }

  Serial.println("--------------------");

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1000);
}