// FLIP FLOP - SR Latch
// Simulasi perilaku SR Latch menggunakan variabel bool sebagai memori

const int BTN_S = 2;   // Set
const int BTN_R = 3;   // Reset
const int LED   = 7;

bool Q = false;        // Memori sistem (pengganti cross-coupled NAND)

void setup() {
  pinMode(BTN_S, INPUT);
  pinMode(BTN_R, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  bool S = digitalRead(BTN_S);
  bool R = digitalRead(BTN_R);

  if (S && !R) Q = true;    // Set   → Q = 1
  if (R && !S) Q = false;   // Reset → Q = 0
  // S=0, R=0 → Q tidak berubah (Hold)
  // S=1, R=1 → Q tidak berubah (mencegah Race Condition)

  digitalWrite(LED, Q);
}