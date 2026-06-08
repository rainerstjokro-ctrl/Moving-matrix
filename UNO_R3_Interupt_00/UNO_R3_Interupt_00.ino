const int buttonPin = 2;
const int firstLed = 3;
const int lastLed = 12;

volatile int modeSirine = 1; 

void ISR_changeState() {
  modeSirine++;
  if (modeSirine > 4) modeSirine = 1;
}

void setup() {
  for (int i = firstLed; i <= lastLed; i++) pinMode(i, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), ISR_changeState, FALLING); 
}

void matikanSemua() {
  for (int i = firstLed; i <= lastLed; i++) digitalWrite(i, LOW);
}

void loop() {
  matikanSemua();
  
  if (modeSirine == 1) {
    for (int i = 3; i <= 5; i++) digitalWrite(i, HIGH);
    delay(100);
    for (int i = 3; i <= 5; i++) digitalWrite(i, LOW);
    delay(100);
  } else if (modeSirine == 2) {
    for (int i = 6; i <= 8; i++) digitalWrite(i, HIGH);
    delay(100);
    for (int i = 6; i <= 8; i++) digitalWrite(i, LOW);
    delay(100);
  } else if (modeSirine == 3) {
    for (int i = 9; i <= 12; i++) digitalWrite(i, HIGH);
    delay(100);
    for (int i = 9; i <= 12; i++) digitalWrite(i, LOW);
    delay(100);
  } else {
    for (int i = 3; i <= 12; i++) digitalWrite(i, LOW);
  }
}

