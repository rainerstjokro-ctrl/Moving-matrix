// SELF HOLDING - 2 Player
// Setiap player punya tombol sendiri
// LED tetap menyala walau tombol dilepas
// Hanya Reset yang bisa mematikan

const int BTN_P1  = 2;
const int BTN_P2  = 3;
const int BTN_RST = 4;
const int LED_P1  = 12;
const int LED_P2  = 13;

bool state1 = false;   // Memori Player 1
bool state2 = false;   // Memori Player 2

void setup() {
  pinMode(BTN_P1,  INPUT);
  pinMode(BTN_P2,  INPUT);
  pinMode(BTN_RST, INPUT);
  pinMode(LED_P1,  OUTPUT);
  pinMode(LED_P2,  OUTPUT);
}

void loop() {
  // Self Holding: state dipertahankan oleh dirinya sendiri
  // state = state yang lama ATAU tombol baru ditekan
  if (digitalRead(BTN_P1)) state1 = true;
  if (digitalRead(BTN_P2)) state2 = true;

  // Reset → matikan semua
  if (digitalRead(BTN_RST)) {
    state1 = false;
    state2 = false;
  }

  digitalWrite(LED_P1, state1);
  digitalWrite(LED_P2, state2);
}