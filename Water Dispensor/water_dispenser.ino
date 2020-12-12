#define trigger 17
#define echo 15
#define Relay 19
#define Light 2

float time=0,distance=0;
 
void setup()
{
Serial.begin(9600);
 pinMode(Light,OUTPUT);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(Relay,OUTPUT);

 delay(2000);
}
 
void loop()
{
 measure_distance();

 if(distance<5)
 {
   digitalWrite(Relay,LOW);
   digitalWrite(Light,HIGH);
 }
 else
 {
   digitalWrite(Relay,HIGH);
   digitalWrite(Light,LOW);
 }

 delay(500);
}

void measure_distance()
{
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);
 
 distance=time*200/20000;
}
