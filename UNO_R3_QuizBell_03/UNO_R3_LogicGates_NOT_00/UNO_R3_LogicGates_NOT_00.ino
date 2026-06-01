// GERBANG NOT
// LED menyala jika Button A TIDAK ditekan (kebalikan dari input)
// Button B tidak digunakan karena NOT hanya punya 1 input

const int BTN_A = 2;
const int LED   = 13;

void setup() {
  pinMode(BTN_A, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  bool A = digitalRead(BTN_A);

  // NOT → kebalikan dari A
  bool C = !A;

  digitalWrite(LED, C);
}