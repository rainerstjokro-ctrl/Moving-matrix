const int buttonPin = 2;
const int firstLed = 3;
const int lastLed = 12;
int modeSirine = 1;
int lastButtonState = HIGH;

void setup() {
  for (int i = firstLed; i <= lastLed; i++) pinMode(i, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void matikanSemua() {
  for (int i = firstLed; i <= lastLed; i++) digitalWrite(i, LOW);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    modeSirine++;
    if (modeSirine > 3) modeSirine = 1;
    delay(200);
  }
  lastButtonState = buttonState;

  matikanSemua();
  if (modeSirine == 1) {
    for (int i = 3; i <= 5; i++) digitalWrite(i, HIGH);
  } else if (modeSirine == 2) {
    for (int i = 6; i <= 8; i++) digitalWrite(i, HIGH);
  } else if (modeSirine == 3) {
    for (int i = 9; i <= 12; i++) digitalWrite(i, HIGH);
  } else {
    for (int i = 9; i <= 12; i++) digitalWrite(i, HIGH);
  }
}
