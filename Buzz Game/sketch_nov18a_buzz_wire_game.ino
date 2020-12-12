#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int startPin = 2;
const int endPin = 3;
const int buzzer = 4;
int start, end_;
void setup(void)
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("** Buzz Game **");
  pinMode(buzzer, OUTPUT);
  pinMode(startPin, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP);
  delay(2000);
}
void loop(void)
{  
  start = digitalRead(startPin);
  end_ = digitalRead(endPin); 
  Serial.print(start);
  Serial.print("\n");
  Serial.print(end_);  
  if (start == LOW && end_== LOW ){
    digitalWrite(buzzer, HIGH);
    delay(1000); 
    digitalWrite(buzzer, LOW); 
    lcd.setCursor(0,0);
    lcd.print("** Try  Again **");     
    Serial.print("Try Again");        
  }
  else if (start == HIGH && end_== LOW){
    lcd.setCursor(0,0);
    lcd.print("** Well  Done **");
    Serial.print("Well Done");
  }
 delay(500); 
}
