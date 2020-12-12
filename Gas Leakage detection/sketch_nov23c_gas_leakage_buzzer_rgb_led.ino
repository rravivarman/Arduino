void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void green() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  Serial.println(", GREEN");
}

void blue() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  Serial.println(", BLUE");
}

void red() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  Serial.println(", RED");
}
void loop() {
  int gas_value = analogRead(7);
  Serial.print(gas_value);

  if (gas_value > 200)
    red();
  else if (gas_value > 150)
    blue();
  else
    green();

    delay(1000);
}
