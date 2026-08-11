const int RED_PIN = 5;
const int YELLOW_PIN = 6;
const int GREEN_PIN = 9;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void blinkLED(int color) {
  digitalWrite(color, HIGH);
  delay(1000);

  digitalWrite(color, LOW);
  delay(1000);
}

void loop() {
  blinkLED(RED_PIN);
  blinkLED(YELLOW_PIN);
  blinkLED(GREEN_PIN);
}