void (*resetFunc)(void) = 0;

unsigned long previousMillis = 0UL;
unsigned long interval = 500UL;
unsigned long storeInterval = 500UL;
int score1 = 0;
int score2 = 0;
int soundA = 800;
int soundB = 1000;
int bounce = 0;
//494

int startDir[] = { -1, 1 };
int LED[] = { 13, 12, 11, 10, 9, 8, 7, 6, 5 };
const int button1 = 4;  // the number of the pushbutton pin
const int button2 = 3;  // the number of the pushbutton pin
int dir = 1;
int pos = 4;
int A = 0;
int B = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  for (int i = 0; i <= 8; i = i + dir) {
    pinMode(LED[i], OUTPUT);
  }
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  dir = random(-1, 2);
  if (dir == 0) dir = 1;
}

// the loop function runs over and over again forever
void loop() {


  unsigned long currentMillis = millis();
  int buttonState = digitalRead(button1);
  int buttonState2 = digitalRead(button2);
  Serial.print(buttonState);
  Serial.print(",");
  Serial.print(buttonState2);
  Serial.print(",");
  Serial.print(dir);
  Serial.print(",");
  Serial.print(pos);
  Serial.print(",");
  Serial.print(score1);
  Serial.print(",");
  Serial.print(score2);
  Serial.print(",");
  Serial.println(interval);


  //change direction when pushed blue button
  if (buttonState == 0 and pos > 4 and A == 1) {

    dir = -1;
    A = 0;

    if (bounce == 1) {
      interval = storeInterval;
      bounce = 0;
    }



    if (interval > 40) interval = interval - 5;

    //speed bounce
    if (pos == 7) {
      bounce = 1;
      storeInterval = interval;
      interval = 60;
    }
  }

  //change direction when pushed red button
  if (buttonState2 == 0 and pos < 4 and B == 1) {
    dir = 1;
    B = 0;

    if (bounce == 1) {
      interval = storeInterval;
      bounce = 0;
    }
    //reset speed after bounce

    if (interval > 40) interval = interval - 5;
    if (pos == 1) {
      bounce = 1;
      storeInterval = interval;
      interval = 60;
    }
  }





  //reset the push button
  if (buttonState == 1) A = 1;
  if (buttonState2 == 1) B = 1;




  if (currentMillis - previousMillis > interval) {

    if (dir == 1) tone(2, soundB, 50);
    if (dir == -1) tone(2, soundA, 50);
    buttonState = digitalRead(button1);
    buttonState2 = digitalRead(button2);


    /* The Arduino executes this code once every second
  *  (interval = 1000 (ms) = 1 second).
  */

    // Don't forget to update the previousMillis value
    digitalWrite(LED[pos], LOW);


    if (pos > -1 and pos < 9) pos = pos + dir;

    if (pos == 0)  //score
    {
      interval = storeInterval;


      // flash the led for the goal
      for (int i = 0; i <= 5; i++) {

        digitalWrite(LED[pos], HIGH);
        delay(50);
        tone(2, soundA, 50);
        digitalWrite(LED[pos], LOW);
        delay(50);
        tone(2, soundA, 50);
      }

      // show the score

      for (int i = 8; i >= 8 - score2; i--) {
        digitalWrite(LED[i], HIGH);
        delay(50);
      }
      delay(1000);  //wait one second

      //clear the score
      for (int i = 8 - score2; i <= 8; i++) {
        digitalWrite(LED[i], LOW);
        delay(50);
      }


      // show the led will come again
      digitalWrite(LED[pos], HIGH);
      delay(1000);
      //change direction and increase score by one
      dir = 1;
      score2 = score2 + 1;
    }

    if (pos == 8) {
      interval = storeInterval;  //reset the speed after a fast bounce

      // flash the score for player 1
      for (int i = 0; i <= 5; i++) {

        digitalWrite(LED[pos], HIGH);
        delay(50);
        tone(2, soundB, 50);
        digitalWrite(LED[pos], LOW);
        delay(50);
        tone(2, soundB, 50);
      }


      //show the score
      for (int i = 0; i <= score1; i++) {
        digitalWrite(LED[i], HIGH);
        delay(50);
      }
      delay(1000);  //wait a second

      //clear the score
      for (int i = score1; i >= 0; i--) {
        digitalWrite(LED[i], LOW);
        delay(50);
      }
      digitalWrite(LED[pos], HIGH);
      delay(1000);

      dir = -1;
      score1 = score1 + 1;
    }


    //end of game reached 9 points
    if (score1 == 9 or score2 == 9) {

      digitalWrite(LED[pos], LOW);
      for (int i = 0; i <= 5; i++) {

        if (score1 == 9) {
          digitalWrite(LED[0], HIGH);
          delay(100);
          digitalWrite(LED[0], LOW);
          delay(100);
        }

        if (score2 == 9) {
          digitalWrite(LED[8], HIGH);
          delay(100);
          digitalWrite(LED[8], LOW);
          delay(100);
        }

        tone(2, 800, 100);
        tone(2, 900, 100);

        delay(200);
        noTone(2);
      }
      resetFunc();
    }
    digitalWrite(LED[pos], HIGH);
    previousMillis = currentMillis;
  }
}
