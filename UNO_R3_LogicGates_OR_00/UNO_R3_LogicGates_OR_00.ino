// GERBANG OR
// LED menyala jika Button A ATAU Button B ditekan (salah satu saja cukup)

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

  // OR → salah satu bernilai 1 sudah cukup
  bool C = A || B;

  digitalWrite(LED, C);
}