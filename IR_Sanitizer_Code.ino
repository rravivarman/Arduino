const int flow_pot =14;
const int ir_sensor = 15;
const int solenoid_relay = 16;
int sensor_state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(ir_sensor,INPUT);
  pinMode(solenoid_relay,OUTPUT);
  digitalWrite(solenoid_relay,HIGH);
  Serial.println("System Ready");
}

void loop() {
  int flow_time_pot = analogRead(0);
  int flow_time = map(flow_time_pot,0,1024,0,5000);

  if(digitalRead(ir_sensor)==HIGH && sensor_state == LOW){
    sensor_state = HIGH;
    Serial.println("Pump ON");
    digitalWrite(solenoid_relay,LOW);
    Serial.print("Flow Time:");Serial.print((flow_time));Serial.println("ms");
    delay(flow_time);
    digitalWrite(solenoid_relay,HIGH);
    Serial.println("Pump OFF");
    Serial.println("System Ready");
  }
  if(digitalRead(ir_sensor)==LOW){
    sensor_state = LOW;
    delay(1000);
  }
}
