// QUIZ BELL - 4 Player + Buzzer + Auto Reset + Serial Monitor
// Additional Challenge 3: Tampilkan pemenang di Serial Monitor

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

const int BUZZER  = 9;

// ---- MEMORI SISTEM ----
bool state1 = false;
bool state2 = false;
bool state3 = false;
bool state4 = false;
bool locked = false;

// ---- TIMER ----
unsigned long waktuMenang = 0;
bool timerAktif = false;
const unsigned long BATAS = 5000;

// ---- TRACKING PEMENANG ----
int pemenang = 0;   // ← menyimpan nomor player yang menang

void resetSemua() {
  state1     = false;
  state2     = false;
  state3     = false;
  state4     = false;
  timerAktif = false;
  pemenang   = 0;
  noTone(BUZZER);
  Serial.println("[ RESET ] Sistem kembali ke kondisi awal.");
  Serial.println("------------------------------------------");
}

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
  pinMode(BUZZER,  OUTPUT);

  Serial.begin(9600);   // ← aktifkan Serial Monitor
  Serial.println("========== QUIZ BELL SIAP ==========");
  Serial.println("Menunggu player menekan tombol...");
}

void loop() {

  // ---- STEP 1: CEK INTERLOCK ----
  locked = state1 || state2 || state3 || state4;

  // ---- STEP 2: BACA INPUT PLAYER ----
  if (!locked) {
    if (!digitalRead(BTN_P1)) { state1 = true; pemenang = 1; }
    if (!digitalRead(BTN_P2)) { state2 = true; pemenang = 2; }
    if (!digitalRead(BTN_P3)) { state3 = true; pemenang = 3; }
    if (!digitalRead(BTN_P4)) { state4 = true; pemenang = 4; }
  }

  // ---- STEP 3: JALANKAN TIMER + TAMPILKAN PEMENANG ----
  if (locked && !timerAktif) {
    waktuMenang = millis();
    timerAktif  = true;
    tone(BUZZER, 1000);

    // Tampilkan pemenang di Serial Monitor
    Serial.println("==========================================");
    Serial.print  ("  PLAYER ");
    Serial.print  (pemenang);
    Serial.println(" MENEKAN TOMBOL PERTAMA!");
    Serial.println("  Sistem akan auto reset dalam 5 detik...");
    Serial.println("==========================================");
  }

  // ---- STEP 4: CEK APAKAH SUDAH 5 DETIK ----
  if (timerAktif) {
    // Tampilkan hitung mundur
    unsigned long sisaWaktu = BATAS - (millis() - waktuMenang);
    static unsigned long lastPrint = 0;

    if (millis() - lastPrint >= 1000) {
      lastPrint = millis();
      Serial.print("  Reset dalam : ");
      Serial.print(sisaWaktu / 1000);
      Serial.println(" detik...");
    }

    if (millis() - waktuMenang >= BATAS) {
      resetSemua();
    }
  }

  // ---- STEP 5: RESET MANUAL OLEH HOST ----
  if (!digitalRead(BTN_RST)) {
    resetSemua();
  }

  // ---- STEP 6: UPDATE OUTPUT LED ----
  digitalWrite(LED_P1, state1);
  digitalWrite(LED_P2, state2);
  digitalWrite(LED_P3, state3);
  digitalWrite(LED_P4, state4);
}