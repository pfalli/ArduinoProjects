#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Face
byte face[8] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

// Explosion 1
byte boom1[8] = {
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00100,
  B00000
};

// Explosion 2
byte boom2[8] = {
  B10001,
  B01010,
  B00100,
  B11111,
  B00100,
  B01010,
  B10001,
  B00000
};

// Wall
byte wall[8] = {
  B11111,
  B10101,
  B11111,
  B01010,
  B11111,
  B10101,
  B11111,
  B01010
};

void setup() {
  lcd.begin(16, 2);

  lcd.createChar(0, face);
  lcd.createChar(1, boom1);
  lcd.createChar(2, boom2);
  lcd.createChar(3, wall);
}

void loop() {

  // =========================
  // 1. Face enters
  // =========================

  for (int x = 0; x < 14; x++) {

    lcd.clear();

    lcd.setCursor(x, 0);
    lcd.write(byte(0));

    // wall
    lcd.setCursor(15, 0);
    lcd.write(byte(3));

    delay(300);
  }


  // =========================
  // 2. OH NO
  // =========================

  lcd.clear();

  lcd.setCursor(4, 1);
  lcd.print("OH NO!");

  lcd.setCursor(13, 0);
  lcd.write(byte(0));

  lcd.setCursor(15, 0);
  lcd.write(byte(3));

  delay(700);


  // =========================
  // 3. Explosion animation
  // =========================

  for (int i = 0; i < 6; i++) {

    lcd.clear();

    lcd.setCursor(14, 0);

    if (i % 2 == 0) {
      lcd.write(byte(1));
    } else {
      lcd.write(byte(2));
    }

    delay(150);
  }


  // =========================
  // 4. Dramatic pause
  // =========================

  lcd.clear();

  delay(700);


  // =========================
  // 5. Message scroll
  // =========================

  String text = " GAME OVER! ";

  for (int x = 16; x >= 1; x--) {

    lcd.clear();

    lcd.setCursor(x, 0);
    lcd.print(text);

    delay(120);
  }


  // =========================
  // 6. Final screen
  // =========================

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("SYSTEM ONLINE");

  lcd.setCursor(3, 1);
  lcd.print("READY!");

  delay(2000);


  // =========================
  // 7. Loading animation
  // =========================

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LOADING");

  for (int i = 0; i < 16; i++) {

    lcd.setCursor(i, 1);
    lcd.write(255);   // solid block

    delay(100);
  }

  delay(1000);
}