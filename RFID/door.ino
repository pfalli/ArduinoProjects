#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Servo.h>

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

// ----------------------
// SERVO
// ----------------------
#define SERVO_PIN 8

Servo doorServo;

const int LOCKED_POSITION = 0;
const int UNLOCKED_POSITION = 90;

// ----------------------
// Known cards
// ----------------------
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
// Show UID
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


// ----------------------
// Unlock door
// ----------------------
void unlockDoor() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DOOR UNLOCKED");

  lcd.setCursor(0, 1);
  lcd.print("Welcome!");

  // Move servo
  doorServo.write(UNLOCKED_POSITION);

  Serial.println("Door unlocked");

  // Keep door unlocked for 3 seconds
  delay(3000);


  // Lock again
  doorServo.write(LOCKED_POSITION);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DOOR LOCKED");

  Serial.println("Door locked");

  delay(1000);
}


// ----------------------
// Setup
// ----------------------
void setup() {

  Serial.begin(9600);

  // LCD
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Starting...");


  // Servo
  doorServo.attach(SERVO_PIN);

  // Start locked
  doorServo.write(LOCKED_POSITION);


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

  // Look for new card
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read card immediately
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }


  // ----------------------
  // Card detected
  // ----------------------

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Card detected!");

  lcd.setCursor(0, 1);
  lcd.print("Reading...");

  delay(400);


  // ----------------------
  // Show UID
  // ----------------------

  showUID();

  delay(1200);


  // ----------------------
  // Check authorization
  // ----------------------

  if (checkUID(card1)) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ACCESS GRANTED");

    lcd.setCursor(0, 1);
    lcd.print("CARD 1");

    Serial.println("ACCESS GRANTED - CARD 1");

    delay(1000);

    unlockDoor();
  }

  else if (checkUID(card2)) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ACCESS GRANTED");

    lcd.setCursor(0, 1);
    lcd.print("CARD 2");

    Serial.println("ACCESS GRANTED - CARD 2");

    delay(1000);

    unlockDoor();
  }

  else {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ACCESS DENIED");

    lcd.setCursor(0, 1);
    lcd.print("UNKNOWN CARD");

    Serial.println("ACCESS DENIED");

    delay(2000);
  }


  // ----------------------
  // Finish RFID transaction
  // ----------------------

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();


  // Ready for next card
  showReady();
}