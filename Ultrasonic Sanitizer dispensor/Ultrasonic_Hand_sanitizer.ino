int trig = 15;
int echo = 17;
int pump = 19;
int light = 18;
int a, distance;

void setup(){
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);
  pinMode(echo, INPUT);
  digitalWrite(light, HIGH);
  delay(500);
  digitalWrite(light, LOW);
  delay(500);
  digitalWrite(light, HIGH);
  delay(500);
  digitalWrite(light, LOW);
  delay(500);
}

void loop(){
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  a = pulseIn(echo, HIGH);
  distance = a * 0.034 / 2;
  Serial.println(distance);
  
  if (distance < 20)
  {
    digitalWrite(pump, LOW);
    digitalWrite(light, HIGH);
    delay(200);
    digitalWrite(pump, HIGH);
    digitalWrite(light, LOW);
    delay(3000);
  }
  else
  {
    digitalWrite(pump, HIGH);
  }
  delay(200);
}
