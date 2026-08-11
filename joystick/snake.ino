#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int JOY_X  = A0;
const int JOY_Y  = A1;
const int JOY_SW = 2;

const int WIDTH  = 16;
const int HEIGHT = 2;
const int MAX_SNAKE = 32;

// Snake positions
int snakeX[MAX_SNAKE];
int snakeY[MAX_SNAKE];

int snakeLength = 3;

// Food
int foodX;
int foodY;

// Horizontal movement
int directionX = 1;

// Requested vertical lane change
int nextRow = -1;

bool gameOver = false;

unsigned long lastMove = 0;
int moveDelay = 350;


// Snake head
byte headChar[8] = {
  B00000,
  B01110,
  B10101,
  B11111,
  B11111,
  B10101,
  B01110,
  B00000
};

// Snake body
byte bodyChar[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000
};

// Food
byte foodChar[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};


void setup() {

  lcd.begin(16, 2);

  lcd.createChar(0, headChar);
  lcd.createChar(1, bodyChar);
  lcd.createChar(2, foodChar);

  pinMode(JOY_SW, INPUT_PULLUP);

  randomSeed(analogRead(A2));

  startGame();
}


void startGame() {

  lcd.clear();

  snakeLength = 3;

  snakeX[0] = 5;
  snakeY[0] = 0;

  snakeX[1] = 4;
  snakeY[1] = 0;

  snakeX[2] = 3;
  snakeY[2] = 0;

  directionX = 1;
  nextRow = -1;

  gameOver = false;

  createFood();

  drawGame();
}


void loop() {

  if (gameOver) {

    lcd.clear();

    lcd.setCursor(3, 0);
    lcd.print("GAME OVER");

    lcd.setCursor(1, 1);
    lcd.print("Press joystick");

    while (digitalRead(JOY_SW) == HIGH) {
      delay(20);
    }

    delay(300);

    startGame();

    return;
  }


  readJoystick();


  if (millis() - lastMove >= moveDelay) {

    lastMove = millis();

    moveSnake();

    drawGame();
  }
}


void readJoystick() {

  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  // LEFT
  if (x < 300) {
    directionX = -1;
  }

  // RIGHT
  if (x > 700) {
    directionX = 1;
  }

  // UP -> top row
  if (y < 300) {
    nextRow = 0;
  }

  // DOWN -> bottom row
  if (y > 700) {
    nextRow = 1;
  }
}


void moveSnake() {

  int newX = snakeX[0] + directionX;
  int newY = snakeY[0];


  // Change row when joystick is moved up/down
  if (nextRow != -1) {

    newY = nextRow;

    nextRow = -1;
  }


  // Wrap around screen
  if (newX < 0) {
    newX = WIDTH - 1;
  }

  if (newX >= WIDTH) {
    newX = 0;
  }


  // Check if snake hits itself
  for (int i = 0; i < snakeLength; i++) {

    if (snakeX[i] == newX &&
        snakeY[i] == newY) {

      gameOver = true;
      return;
    }
  }


  // Check if food is eaten
  bool ateFood =
    (newX == foodX && newY == foodY);


  if (ateFood && snakeLength < MAX_SNAKE) {
    snakeLength++;
  }


  // Move body backwards
  for (int i = snakeLength - 1; i > 0; i--) {

    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }


  // New head
  snakeX[0] = newX;
  snakeY[0] = newY;


  if (ateFood) {

    createFood();

    // Make it slightly faster
    if (moveDelay > 100) {
      moveDelay -= 15;
    }
  }
}


void createFood() {

  bool valid = false;

  while (!valid) {

    foodX = random(0, WIDTH);
    foodY = random(0, HEIGHT);

    valid = true;

    // Don't place food inside snake
    for (int i = 0; i < snakeLength; i++) {

      if (snakeX[i] == foodX &&
          snakeY[i] == foodY) {

        valid = false;
        break;
      }
    }
  }
}


void drawGame() {

  lcd.clear();

  // Food
  lcd.setCursor(foodX, foodY);
  lcd.write(byte(2));


  // Snake body
  for (int i = 1; i < snakeLength; i++) {

    lcd.setCursor(snakeX[i], snakeY[i]);
    lcd.write(byte(1));
  }


  // Snake head
  lcd.setCursor(snakeX[0], snakeY[0]);
  lcd.write(byte(0));
}