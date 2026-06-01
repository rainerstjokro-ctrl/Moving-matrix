// QUIZ BELL - 4 Player + Buzzer
// Additional Challenge 1: Buzzer bunyi saat ada player yang menang

// ---- PIN DEFINITION ----
const int BTN_P1  = 2;
const int BTN_P2  = 3;
const int BTN_P3  = 4;
const int BTN_P4  = 5;
const int BTN_RST = 6;

const int LED_P1  = 10;
const int LED_P2  = 11;
const int LED_P3  = 12;
const int LED_P4  = 13;

const int BUZZER  = 9;   // ← tambahan baru

// ---- MEMORI SISTEM ----
bool state1 = false;
bool state2 = false;
bool state3 = false;
bool state4 = false;
bool locked = false;

void setup() {
  pinMode(BTN_P1,  INPUT_PULLUP);
  pinMode(BTN_P2,  INPUT_PULLUP);
  pinMode(BTN_P3,  INPUT_PULLUP);
  pinMode(BTN_P4,  INPUT_PULLUP);
  pinMode(BTN_RST, INPUT_PULLUP);

  pinMode(LED_P1,  OUTPUT);
  pinMode(LED_P2,  OUTPUT);
  pinMode(LED_P3,  OUTPUT);
  pinMode(LED_P4,  OUTPUT);
  pinMode(BUZZER,  OUTPUT);   // ← tambahan baru
}

void loop() {

  // ---- STEP 1: CEK INTERLOCK ----
  locked = state1 || state2 || state3 || state4;

  // ---- STEP 2: BACA INPUT PLAYER ----
  if (!locked) {
    if (!digitalRead(BTN_P1)) state1 = true;
    if (!digitalRead(BTN_P2)) state2 = true;
    if (!digitalRead(BTN_P3)) state3 = true;
    if (!digitalRead(BTN_P4)) state4 = true;
  }

  // ---- STEP 3: RESET OLEH HOST ----
  if (!digitalRead(BTN_RST)) {
    state1 = false;
    state2 = false;
    state3 = false;
    state4 = false;
    noTone(BUZZER);   // Matikan buzzer saat reset
  }

  // ---- STEP 4: UPDATE OUTPUT LED ----
  digitalWrite(LED_P1, state1);
  digitalWrite(LED_P2, state2);
  digitalWrite(LED_P3, state3);
  digitalWrite(LED_P4, state4);

  // ---- STEP 5: UPDATE BUZZER ----
  // Buzzer bunyi jika ada yang menang
  if (locked) {
    tone(BUZZER, 1000);   // Bunyi frekuensi 1000 Hz
  }
}