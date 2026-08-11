#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int TEMP_PIN = A0;

const float R_FIXED = 100000.0;
const float R0 = 100000.0;
const float BETA = 3950.0;
const float T0 = 25.0 + 273.15;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  int adc = analogRead(TEMP_PIN);

  // Correct if thermistor is connected to 5V
  // and fixed 100k resistor is connected to GND
  float resistance =
      R_FIXED * adc / (1023.0 - adc);

  float tempK = 1.0 / (
    (1.0 / T0) +
    (1.0 / BETA) * log(resistance / R0)
  );

  float tempC = tempK - 273.15;

  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  lcd.setCursor(0, 1);
  lcd.print(tempC, 1);
  lcd.write((byte)223);
  lcd.print("C    ");

  Serial.print("ADC=");
  Serial.print(adc);
  Serial.print(" R=");
  Serial.print(resistance);
  Serial.print(" Temp=");
  Serial.println(tempC);

  delay(500);
}