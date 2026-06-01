const int buttonPin = 2;
const int buzzerPin = A0; 
const int firstLed = 3;
const int lastLed = 12;

volatile int modeSirine = 1;         
volatile unsigned long lastDebounceTime = 0; 

void setup() {
  for (int i = firstLed; i <= lastLed; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), gantiMode, FALLING);
}

void loop() {
  matikanSemuaLed();
  noTone(buzzerPin);
  
  int modeAktif = modeSirine;

  if (modeAktif == 1) {
    sirinePemadam();
  } else if (modeAktif == 2) {
    sirineAmbulans();
  } else if (modeAktif == 3) {
    sirinePolisi();
  }
}

void gantiMode() {
  unsigned long currentTime = millis();
  if (currentTime - lastDebounceTime > 250) { 
    modeSirine++;
    if (modeSirine > 3) {
      modeSirine = 1;
    }
    lastDebounceTime = currentTime;
  }
}


void matikanSemuaLed() {
  for (int i = firstLed; i <= lastLed; i++) {
    digitalWrite(i, LOW);
  }
}


void sirinePemadam() { 
  int modeAwal = modeSirine; 
  
  for(int hz = 440; hz < 1000; hz += 25){
    if (modeSirine != modeAwal) return; 
    tone(buzzerPin, hz, 50);
    delay(5);
    for(int i = 3; i <= 7; i++) digitalWrite(i, HIGH); 
  }
  
  for(int hz = 1000; hz > 440; hz -= 25){
    if (modeSirine != modeAwal) return; 
    tone(buzzerPin, hz, 50);
    delay(5);
    for(int i = 3; i <= 7; i++) {
      digitalWrite(i, LOW);
      digitalWrite(i + 5, HIGH); 
    }
  }
}

void sirineAmbulans() { 
  int modeAwal = modeSirine;
  
  tone(buzzerPin, 440); 
  for(int i = 3; i <= 7; i++) digitalWrite(i, HIGH);
  
  for(int d = 0; d < 40; d++) {
    if (modeSirine != modeAwal) return;
    delay(10);
  }
  
  matikanSemuaLed();
  
  tone(buzzerPin, 523); 
  for(int i = 8; i <= 12; i++) digitalWrite(i, HIGH); 
  
  for(int d = 0; d < 40; d++) {
    if (modeSirine != modeAwal) return;
    delay(10);
  }
}

void sirinePolisi() { 
  int modeAwal = modeSirine;
  
  for(int i = 3; i <= 11; i += 2) digitalWrite(i, HIGH); 
  for(int hz = 600; hz < 1200; hz += 10){
    if (modeSirine != modeAwal) return;
    tone(buzzerPin, hz, 20);
    delay(2);
  }
  
  matikanSemuaLed();
  
  for(int i = 4; i <= 12; i += 2) digitalWrite(i, HIGH); 
  for(int hz = 1200; hz > 600; hz -= 10){
    if (modeSirine != modeAwal) return;
    tone(buzzerPin, hz, 20);
    delay(2);
  }
}