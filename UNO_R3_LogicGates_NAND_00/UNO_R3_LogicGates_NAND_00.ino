// GERBANG NAND
// LED menyala KECUALI jika Button A DAN Button B ditekan bersamaan
// Kebalikan dari AND

const int BTN_A = 2;
const int BTN_B = 3;
const int LED   = 13;

void setup() {
  pinMode(BTN_A, INPUT);
  pinMode(BTN_B, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  bool A = digitalRead(BTN_A);
  bool B = digitalRead(BTN_B);

  // NAND → kebalikan dari AND
  bool C = !(A && B);

  digitalWrite(LED, C);
}