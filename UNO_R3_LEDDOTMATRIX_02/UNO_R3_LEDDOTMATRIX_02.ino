#include <MD_MAX72xx.h>
#include <SPI.h>
#define CS_PIN 10
#define NUM_DEV 4
int refreshRate = 0;
MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::FC16_HW, CS_PIN, NUM_DEV);
const byte FONT[36][5] PROGMEM = {
  { B01111110, B00001001, B00001001, B00001001, B01111110 },  // A
  { B01111111, B01001001, B01001001, B01001001, B00110110 },  // B
  { B00111110, B01000001, B01000001, B01000001, B00100010 },  // C
  { B01111111, B01000001, B01000001, B01000001, B00111110 },  // D
  { B01111111, B01001001, B01001001, B01001001, B01000001 },  // E
  { B01111111, B00001001, B00001001, B00001001, B00000001 },  // F
  { B00111110, B01000001, B01001001, B01001001, B00111010 },  // G
  { B01111111, B00001000, B00001000, B00001000, B01111111 },  // H
  { B00000000, B01000001, B01111111, B01000001, B00000000 },  // I
  { B00110000, B01000000, B01000001, B00111111, B00000001 },  // J
  { B01111111, B00001000, B00010100, B00100010, B01000001 },  // K
  { B01111111, B01000000, B01000000, B01000000, B01000000 },  // L
  { B01111111, B00000010, B00001100, B00000010, B01111111 },  // M
  { B01111111, B00000100, B00001000, B00010000, B01111111 },  // N
  { B00111110, B01000001, B01000001, B01000001, B00111110 },  // O
  { B01111111, B00001001, B00001001, B00001001, B00000110 },  // P
  { B00111110, B01000001, B01010001, B00100001, B01011110 },  // Q
  { B01111111, B00001001, B00011001, B00101001, B01000110 },  // R
  { B01000110, B01001001, B01001001, B01001001, B00110001 },  // S
  { B00000001, B00000001, B01111111, B00000001, B00000001 },  // T
  { B00111111, B01000000, B01000000, B01000000, B00111111 },  // U
  { B00000111, B00011000, B01100000, B00011000, B00000111 },  // V
  { B00111111, B01000000, B00110000, B01000000, B00111111 },  // W
  { B01100011, B00010100, B00001000, B00010100, B01100011 },  // X
  { B00000111, B00001000, B01110000, B00001000, B00000111 },  // Y
  { B01100001, B01010001, B01001001, B01000101, B01000011 },  // Z

  { B00111110, B01010001, B01001001, B01000101, B00111110 },  // 0
  { B00000000, B01000010, B01111111, B01000000, B00000000 },  // 1
  { B01000010, B01100001, B01010001, B01001001, B01000110 },  // 2
  { B00100001, B01000001, B01001001, B01001101, B00110011 },  // 3
  { B00011000, B00010100, B00010010, B01111111, B00010000 },  // 4
  { B00100111, B01000101, B01000101, B01000101, B00111001 },  // 5
  { B00111100, B01001010, B01001001, B01001001, B00110000 },  // 6
  { B00000001, B01110001, B00001001, B00000101, B00000011 },  // 7
  { B00110110, B01001001, B01001001, B01001001, B00110110 },  // 8
  { B00000110, B01001001, B01001001, B00101001, B00011110 },  // 9


};
byte frameBuffer[32];
void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 3);
  mx.clear();
}
byte reverseBits(byte b) {
  byte r = 0;
  for (int i = 0; i < 8; i++) {
    r = (r << 1) | (b & 1);
    b >>= 1;
  }
  return r;
}

int keIndeks(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A';
  if (c >= 'a' && c <= 'z') return c - 'a';
  if (c >= '0' && c <= '9') return (c - '0') + 26;
  return -1;
}
void ghb(int pos, char c) {
  int idx = keIndeks(c);
  if (idx < 0) return;
  for (int k = 0; k < 5; k++) {
    int tk = pos + k;
    if (tk >= 0 && tk < 32) {
      frameBuffer[tk] = reverseBits(pgm_read_byte(&FONT[idx][k]));
    }
  }
}
void fb() {
  for (int col = 0; col < 32; col++) mx.setColumn(col, frameBuffer[col]);
}

void teksBerjalan(const char* teks) {
  int pjg = strlen(teks);
  int lebarTotal = pjg * 6;

  for (int pos = 32; pos > -lebarTotal; pos--) {
    memset(frameBuffer, 0, sizeof(frameBuffer));
    int p = pos;
    for (int i = 0; i < pjg; i++) {
      ghb(p, teks[i]);
      p += 6;
    }
    fb();
    delay(refreshRate);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  teksBerjalan("xy");
  delay(1000);
}
