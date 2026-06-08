// INTERLOCK - 3 Player
// Siapa duluan pencet → LED nya nyala
// Player lain langsung dikunci, tidak bisa menyalakan LED nya
// Hanya Reset yang bisa membuka kunci

const int BTN_P1  = 2;
const int BTN_P2  = 3;
const int BTN_P3  = 4;
const int BTN_RST = 5;
const int LED_P1  = 11;
const int LED_P2  = 12;
const int LED_P3  = 13;

bool state1 = false;
bool state2 = false;
bool state3 = false;
bool locked = false;   // Sinyal LOCKED → pengganti OR gate IC 7432

void setup() {
  pinMode(BTN_P1,  INPUT);
  pinMode(BTN_P2,  INPUT);
  pinMode(BTN_P3,  INPUT);
  pinMode(BTN_RST, INPUT);
  pinMode(LED_P1,  OUTPUT);
  pinMode(LED_P2,  OUTPUT);
  pinMode(LED_P3,  OUTPUT);
}

void loop() {
  // Cek apakah sistem sudah terkunci
  // Analogi IC: sinyal ini dihasilkan oleh IC 7432 (OR gate)
  locked = state1 || state2 || state3;

  // Hanya proses input jika belum ada yang aktif
  if (!locked) {
    if (digitalRead(BTN_P1)) state1 = true;
    if (digitalRead(BTN_P2)) state2 = true;
    if (digitalRead(BTN_P3)) state3 = true;
  }

  // Reset → buka kunci dan matikan semua
  if (digitalRead(BTN_RST)) {
    state1 = false;
    state2 = false;
    state3 = false;
  }

  digitalWrite(LED_P1, state1);
  digitalWrite(LED_P2, state2);
  digitalWrite(LED_P3, state3);
}