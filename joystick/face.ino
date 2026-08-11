#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int JOY_X = A0;
const int JOY_Y = A1;
const int JOY_SW = 2;

int smileX = 7;
int smileY = 0;

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

  pinMode(JOY_SW, INPUT_PULLUP);

  lcd.setCursor(smileX, smileY);
  lcd.write(byte(0));
}

void loop() {
  int xValue = analogRead(JOY_X);
  int yValue = analogRead(JOY_Y);

  // Remove old smile
  lcd.setCursor(smileX, smileY);
  lcd.print(" ");

  // LEFT
  if (xValue < 300) {
    smileX--;

    if (smileX < 0) {
      smileX = 0;
    }
  }

  // RIGHT
  if (xValue > 700) {
    smileX++;

    if (smileX > 15) {
      smileX = 15;
    }
  }

  // UP
  if (yValue < 300) {
    smileY = 0;
  }

  // DOWN
  if (yValue > 700) {
    smileY = 1;
  }

  // Draw smile in new position
  lcd.setCursor(smileX, smileY);
  lcd.write(byte(0));

  delay(150);
}