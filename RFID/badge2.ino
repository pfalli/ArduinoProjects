#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

// ----------------------
// RFID
// ----------------------
#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

// ----------------------
// LCD
// RS, E, D4, D5, D6, D7
// ----------------------
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Known cards
byte card1[] = {0x03, 0xE6, 0xB8, 0xF7};
byte card2[] = {0x89, 0xFD, 0xF9, 0x03};


// ----------------------
// Compare UID
// ----------------------
bool checkUID(byte expected[]) {

  if (rfid.uid.size != 4) {
    return false;
  }

  for (byte i = 0; i < 4; i++) {

    if (rfid.uid.uidByte[i] != expected[i]) {
      return false;
    }
  }

  return true;
}


// ----------------------
// Show UID on LCD
// ----------------------
void showUID() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("UID:");

  lcd.setCursor(0, 1);

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      lcd.print("0");
    }

    lcd.print(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1) {
      lcd.print(":");
    }
  }
}


// ----------------------
// Ready screen
// ----------------------
void showReady() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("RFID ACCESS");

  lcd.setCursor(0, 1);
  lcd.print("Scan card...");
}


void setup() {

  Serial.begin(9600);

  // LCD
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Starting...");

  // RFID
  SPI.begin();
  rfid.PCD_Init();

  delay(1000);

  showReady();

  Serial.println("RFID Access System Ready");
}


// ----------------------
// Main loop
// ----------------------
void loop() {

  // Is there a new card?
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read it IMMEDIATELY
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Now we know we have successfully read it
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card detected!");

  lcd.setCursor(0, 1);
  lcd.print("Reading...");

  delay(400);

  // Show UID
  showUID();

  delay(1200);

  // Check authorization
  if (checkUID(card1)) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS GRANTED");
    lcd.setCursor(0, 1);
    lcd.print("CARD 1");

  } 
  else if (checkUID(card2)) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS GRANTED");
    lcd.setCursor(0, 1);
    lcd.print("CARD 2");

  } 
  else {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS DENIED");
    lcd.setCursor(0, 1);
    lcd.print("UNKNOWN CARD");
  }

  delay(2000);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  showReady();
}