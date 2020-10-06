#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

int relay[8] = {4, 5, 6, 7, 8, 9, 10, 11};

String voice;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(relay[i], OUTPUT);
    digitalWrite(relay[i], HIGH);
  }
  Serial.println("SYSTEM STARTED");
}

void loop() {
  serialEvent();
}

void serialEvent() {
  while (mySerial.available()) {
    delay(10);
    char c = mySerial.read();
    Serial.print(c);
    if (c == '#') {
      break;
    }
    voice += c;
  }
  if (voice.length() > 0) {
    int relay_no = int(voice[0])-49;
    int relay_state = int(voice[1])-49;
    Serial.print("Relay :"); Serial.print(relay_no); Serial.print(" - ");
    Serial.print("State :"); Serial.println(relay_state);
    digitalWrite(relay[relay_no], relay_state);
    Serial.println("ON");
    voice = "";
  }
}
