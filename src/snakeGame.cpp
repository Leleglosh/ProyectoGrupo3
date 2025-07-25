#include <iostream>

void handleGameStates() 
{
  if (gameOver || win) {
    unrollSnake();

    showScoreMessage(snakeLength - initialSnakeLength);
    if (gameOver) showGameOverMessage();
    else if (win) showWinMessage();
    win = false;
    gameOver = false;
    snake.row = random(8);
    snake.col = random(8);
    food.row = -1;
    food.col = -1;
    snakeLength = initialSnakeLength;
    snakeDirection = 0;
    memset(gameboard, 0, sizeof(gameboard[0][0]) * 8 * 8);
    matrix.clearDisplay(0);
  }
}

void unrollSnake() {
  matrix.setLed(0, food.row, food.col, 0);
  delay(800);

  for (int i = 0; i < 5; i++) {

    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        matrix.setLed(0, row, col, gameboard[row][col] == 0 ? 1 : 0);
      }
    }

    delay(20);

    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        matrix.setLed(0, row, col, gameboard[row][col] == 0 ? 0 : 1);
      }
    }

    delay(50);
  }

  delay(600);

  for (int i = 1; i <= snakeLength; i++) {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (gameboard[row][col] == i) {
          matrix.setLed(0, row, col, 0);
          delay(100);
        }
      }
    }
  }
}

void calibrateJoystick() 
{
  Coordinate values;
  for (int i = 0; i < 10; i++) {

    values.x += analogRead(Pin::joystickX);

    values.y += analogRead(Pin::joystickY);
  }
  joystickHome.x = values.x / 10;

  joystickHome.y = values.y / 10;
}

void initialize() 
{
  pinMode(Pin::joystickVCC, OUTPUT);
  digitalWrite(Pin::joystickVCC, HIGH);
  pinMode(Pin::joystickGND, OUTPUT);
  digitalWrite(Pin::joystickGND, LOW);
  matrix.shutdown(0, false);
  matrix.setIntensity(0, intensity);
  matrix.clearDisplay(0);
  randomSeed(analogRead(A5));
  snake.row = random(8);
  snake.col = random(8);
}

void dumpGameBoard() {
  String buff = "\n\n\n";

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (gameboard[row][col] < 10) buff += " ";
      if (gameboard[row][col] != 0) buff += gameboard[row][col];
      else if (col == food.col && row == food.row) buff += "@";
      else buff += "-";
      buff += " ";
    }
    buff += "\n";
  }
  Serial.println(buff);
}
