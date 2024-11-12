#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int pos = 0;
int y = 1;
const int buttonPin = 13;
bool buttonPressed = false;
bool gameOver = false;
int score = 0;

byte dino[8] = {
  0b00011,
  0b00011,
  0b00010,
  0b00010,
  0b01110,
  0b01110,
  0b01110,
  0b01010,
};

byte kaktus[8] = {
  0b00100,
  0b01110,
  0b11110,
  0b01111,
  0b01110,
  0b11110,
  0b01111,
  0b01110,
};

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, dino);
  lcd.createChar(1, kaktus);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Bersihkan layar dan tampilkan kaktus
  lcd.clear();

  if (gameOver && digitalRead(buttonPin) == LOW) {
    gameOver = false;
    score = 0;
    pos = 0;
  }

  for(int i = 0; i < 4; i++) {
    int posObstacle = 3 + (i * 3);

    if (posObstacle == pos && y == 1) {
      gameOver = true;
      break;
    }

    lcd.setCursor(posObstacle, 1);
    lcd.write((byte)1);
  }

  if (gameOver) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Over!");
    lcd.setCursor(0, 1);
    lcd.print("Score : ");
    lcd.setCursor(8, 1);
    lcd.print(score);
    delay(500);
    return;
  }
  
  // Cek apakah tombol ditekan untuk membuat dino melompat
  if (digitalRead(buttonPin) == LOW) {
    y = 0;
  } else {
    y = 1;
  }

  lcd.setCursor(14, 0);
  lcd.print(score);

  // Tampilkan dino di posisi tertentu
  lcd.setCursor(pos, y);
  lcd.write((byte)0);

  // Gerakkan dino ke kanan
  pos++;
  if (pos > 15) {
    pos = 0;
  }

  score++;

  // Delay untuk mengontrol kecepatan animasi
  delay(500);
}