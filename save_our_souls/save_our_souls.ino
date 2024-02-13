#define LED_PIN 8
#define BUTTON_PIN 7
#define BUZZER_PIN 9

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {

    int timeUnit = 100;

    int dot = timeUnit;
    int dash = timeUnit * 3;
    int space = timeUnit;
    int endLetter = timeUnit * 3;

    int soundFreq = 300;

    // . . .
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq); // tone, duration, no third paramter->delay right after
    delay(dot);
    noTone(BUZZER_PIN);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq);
    delay(dot);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq);
    delay(dot);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);

    delay(endLetter);

    // _ _ _
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq);
    delay(dash);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq);
    delay(dash);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq);
    delay(dash);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);

    delay(endLetter);

    // . . .
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq); // tone, duration, no third paramter->delay right after
    delay(dot);
    noTone(BUZZER_PIN);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq);
    delay(dot);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, soundFreq);
    delay(dot);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(space);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
}




