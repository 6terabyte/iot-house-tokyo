// Copyright[2021] <rin>

#include <Arduino.h>

  int pinLed1 = 2;
  int pinLed2 = 3;

  int pinSwich = 9;
  int pinDoor = 8;

String morse() {
  unsigned long time = 0;
  unsigned long count[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 10; i++) {
      time = pulseIn(pinSwich, LOW, 3000000);
      if (time == 0) break;  // タイムアウト
      if (time <1000) {  // チャタリングを無視
        i--;
        continue;
      }
      // Serial.println(time);
      count[i] = time;
    }

    String morse = "";
    for (int i = 0; i < 10; i++) {
      if (count[i] == 0) break;
      if ( (count[i] == 0) ) {
        morse += "";
      } else if (count[i] < 250000) {
        morse += "･";
      } else {
        morse += "-";
      }
    }
    return morse;
}

void setup() {
  Serial.begin(9600);

  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinSwich, INPUT_PULLUP);

  digitalWrite(pinLed1, HIGH);
  digitalWrite(pinLed2, HIGH);
}

void loop() {
  String m = morse();
  // switchはString扱えない?要確認
  Serial.println(m);
  if (m == "-") {
    digitalWrite(pinLed1, HIGH);
    digitalWrite(pinLed2, HIGH);
  } else if (m == "･･" || m == "･") {
    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);
  } else if (m == "--･") {
    digitalWrite(pinLed1, HIGH);
    digitalWrite(pinLed2, LOW);
  } else if (m == "-･-") {
    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, HIGH);
  } else if (m == "---") {
    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);
  }
}
