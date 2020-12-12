void setup() {
  pinMode(6, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(6, LOW);
  digitalWrite(2, HIGH);
}

void loop() {
  digitalWrite(6, !digitalRead(2));
}
