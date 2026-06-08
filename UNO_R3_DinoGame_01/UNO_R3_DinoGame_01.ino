// ==========================================================
// Dino Game — Arduino Uno + OLED SSD1306 0.96"
// Diperbaiki: Desain Sprite T-Rex yang Jauh Lebih Baik & Jelas
// ==========================================================

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define BUTTON_PIN 11 // Menggunakan Pin 11 untuk Arduino Uno

// ----------------------------------------------------------
// SPRITE T-REX BARU (22x20 pixel, bitmap, detail, profil samping)
// ----------------------------------------------------------
static const unsigned char PROGMEM trex_bmp[] = {
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
  0b11111111, 0b11111111, 0b11111111,
};

// Sprite kaktus (8x16) - Tetap sama
static const unsigned char PROGMEM cactus_bmp[] = {
  0b00011000,  // row 0
  0b00011000,  // row 1
  0b10011001,  // row 2
  0b11011011,  // row 3
  0b11111111,  // row 4
  0b01111110,  // row 5
  0b00011000,  // row 6
  0b00011000,  // row 7
  0b00011000,  // row 8
  0b00011000,  // row 9
  0b00011000,  // row 10
  0b00011000,  // row 11
  0b00011000,  // row 12
  0b00011000,  // row 13
  0b11111111,  // row 14
  0b11111111,  // row 15
};

// --- State ---
bool isJumping = false;
bool gameOver  = false;

// --- Posisi & Fisika Dino ---
int dinoY          = 36;
int velocity       = 0;
const int gravity  = 1;
const int groundY  = 36;   // disesuaikan tinggi sprite 20px (ground line di 56)

// --- Kaktus ---
int cactusX1 = 128;
int cactusX2 = 200;        // mulai lebih jauh, beri jarak awal lebih besar

// --- Difficulty & Score ---
int gameSpeed                   = 3;
unsigned long lastSpeedIncrease = 0;
unsigned long score             = 0;

// --- Frame timing ---
unsigned long lastFrame = 0;

// --- Debounce ---
bool buttonPressed = false;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

// ==========================================================
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while (1);
  display.clearDisplay();
  display.display();
  randomSeed(micros());
}

// ==========================================================
void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastFrame < 50) return;
  lastFrame = currentTime;

  int buttonState = digitalRead(BUTTON_PIN);

  // ----------------------------------------------------------
  // STATE: GAME OVER
  // ----------------------------------------------------------
  if (gameOver) {
    if (buttonState == LOW  && !buttonPressed) buttonPressed = true;
    if (buttonState == HIGH &&  buttonPressed) {
      buttonPressed = false;
      resetGame();
    }
    return;
  }

  // ----------------------------------------------------------
  // INPUT: LOMPAT
  // ----------------------------------------------------------
  if (buttonState == LOW && !buttonPressed && dinoY == groundY) {
    buttonPressed = true;
    isJumping = true;
    velocity  = -13;
  }
  if (buttonState == HIGH) buttonPressed = false;

  // ----------------------------------------------------------
  // FISIKA
  // ----------------------------------------------------------
  if (isJumping) {
    dinoY    += velocity;
    velocity += gravity;
    if (dinoY >= groundY) {
      dinoY     = groundY;
      isJumping = false;
      velocity  = 0;
    }
  }

  // ----------------------------------------------------------
  // UPDATE KAKTUS — Fix glitch
  // Setiap kaktus di-handle INDEPENDEN, tidak saling reset
  // ----------------------------------------------------------
  cactusX1 -= gameSpeed;
  cactusX2 -= gameSpeed;

  // Kaktus 1 respawn sendiri
  if (cactusX1 < -10) {
    cactusX1 = 128 + random(20, 60);
  }

  // Kaktus 2 respawn sendiri, pastikan tidak terlalu dekat kaktus 1
  if (cactusX2 < -10) {
    cactusX2 = 128 + random(40, 90);
    // Jaga jarak minimum dengan kaktus 1
    if (cactusX2 < cactusX1 + 25) {
      cactusX2 = cactusX1 + 25 + random(10, 30);
    }
  }

  // ----------------------------------------------------------
  // DIFFICULTY
  // ----------------------------------------------------------
  if (currentTime - lastSpeedIncrease > 3000) {
    gameSpeed++;
    lastSpeedIncrease = currentTime;
  }

  // ----------------------------------------------------------
  // SKOR
  // ----------------------------------------------------------
  score++;

  // ----------------------------------------------------------
  // RENDERING — pakai bitmap sprite
  // ----------------------------------------------------------
  display.clearDisplay();

  // T-Rex sprite 22x20
  display.drawBitmap(5, dinoY, trex_bmp, 22, 20, SSD1306_WHITE);

  // Kaktus sprite 8x16
  display.drawBitmap(cactusX1, groundY, cactus_bmp, 8, 16, SSD1306_WHITE);
  display.drawBitmap(cactusX2, groundY, cactus_bmp, 8, 16, SSD1306_WHITE);

  // Ground line
  display.drawLine(0, 56, 128, 56, SSD1306_WHITE);

  // Score
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score / 10);
  display.display();

  // ----------------------------------------------------------
  // COLLISION DETECTION (AABB)
  // Dino: x=5..27, y=dinoY..dinoY+20
  // Kaktus: x=cactusX..cactusX+8, y=groundY..groundY+16
  // ----------------------------------------------------------
  bool hitCactus1 = (cactusX1 < 27 && cactusX1 + 8 > 5 && dinoY + 20 > groundY);
  bool hitCactus2 = (cactusX2 < 27 && cactusX2 + 8 > 5 && dinoY + 20 > groundY);

  if (hitCactus1 || hitCactus2) {
    gameOver = true;
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(15, 15);
    display.print("GAME OVER");
    display.setTextSize(1);
    display.setCursor(10, 40);
    display.print("Score: ");
    display.print(score / 10);
    display.setCursor(15, 52);
    display.print("Press to restart");
    display.display();
  }
}

// ==========================================================
void resetGame() {
  isJumping  = false;
  dinoY      = groundY;
  velocity   = 0;
  cactusX1   = 128;
  cactusX2   = 200;
  gameSpeed  = 3;
  score      = 0;
  gameOver   = false;
  lastSpeedIncrease = millis();
  lastFrame         = millis();
  display.clearDisplay();
  display.display();
}