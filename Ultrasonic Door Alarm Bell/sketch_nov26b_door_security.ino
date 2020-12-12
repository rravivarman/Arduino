int trig = 19;
int echo = 18;
int light = 17;
int buzzer = 16;

int a, distance;



void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  a = pulseIn(echo, HIGH);
  distance = a * 0.034 / 2;
  Serial.println(distance);
  if (distance < 20)  {
    digitalWrite(light, HIGH);
    int i;
    for (i = 0; i < 10; i++) {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(25);
    }
    
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(light, LOW);
  }
  delay(100);
}
