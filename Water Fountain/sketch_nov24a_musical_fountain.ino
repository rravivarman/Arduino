int microphone = 14;
int multi_color_led_1 = 5;
int multi_color_led_2 = 6;
int water_pump = 19;

#define REF 0

void setup()
{
  Serial.begin(9600);
  pinMode(microphone,INPUT);
  pinMode(multi_color_led_1,OUTPUT);
  pinMode(multi_color_led_2,OUTPUT);
  pinMode(water_pump,OUTPUT);
 
}
void loop()
{
  
  int microphone_value = digitalRead(microphone);
  Serial.println(microphone_value);
  if (microphone_value>0)
  {
    digitalWrite(multi_color_led_2,HIGH);
    digitalWrite(multi_color_led_1,HIGH);
    digitalWrite(water_pump,LOW);
    delay(500);
   }
   else
   {
    digitalWrite(multi_color_led_2,LOW);
    digitalWrite(multi_color_led_1,LOW);
    digitalWrite(water_pump,HIGH);
    delay(100);
   }
}
