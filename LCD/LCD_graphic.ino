#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

byte smiley[8] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, smiley);
}

void loop() {

  // Move across the top row
  for (int col = 0; col <= 3; col++) {
    lcd.clear();

    lcd.setCursor(col, 0);
    lcd.print("Hello there!");

    lcd.write(byte(0));

    delay(300);
  }

  // Move back across the bottom row
  for (int col = 3; col >= 0; col--) {
    lcd.clear();

    lcd.setCursor(col, 1);
    lcd.print("Hello there!");

    lcd.write(byte(0));

    delay(300);
  }
}