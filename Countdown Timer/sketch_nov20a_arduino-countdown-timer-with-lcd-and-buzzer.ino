#include <LiquidCrystal.h>
#include<EEPROM.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int stsp = A5;
const int inc = A4;
const int dec = A3;
const int set = A2;
const int buzz = 9;
const int relay = 8;
int hrs = 0;
int Min = 0;
int sec = 0;
unsigned int check_val = 50;
int add_chk = 0;
int add_hrs = 1;
int add_min = 2;
int add_sec = 3;
bool RUN = true;
bool sec_flag = true;
bool min_flag = true;
bool hrs_flag = true;
void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   ELECTRONIC");
  lcd.setCursor(0, 1);
  lcd.print("COUNTDOWN TIMER");
  pinMode(stsp, INPUT_PULLUP);
  pinMode(inc, INPUT_PULLUP);
  pinMode(dec, INPUT_PULLUP);
  pinMode(set, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  digitalWrite(buzz, LOW);
  if (EEPROM.read(add_chk) != check_val)
  {
    EEPROM.write(add_chk, check_val);
    EEPROM.write(add_hrs, 0);
    EEPROM.write(add_min, 1);
    EEPROM.write(add_sec, 2);
  }
  else
  {
    hrs = EEPROM.read(add_hrs);
    Min = EEPROM.read(add_min);
    sec = EEPROM.read(add_sec);
  }
  delay(1500);
  INIT();
}

void loop()
{
  if (digitalRead(stsp) == LOW)
  {
    lcd.clear();
    delay(100);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    RUN = true;
    while (RUN)
    {
      if (digitalRead(stsp) == LOW)
      {
        delay(500);
        if (digitalRead(stsp) == LOW)
        {
          digitalWrite(relay, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  TIMER STOPPED");
          lcd.setCursor(0, 1);
          lcd.print("                ");
          delay(2000);
          RUN = false;
          INIT();
          break;
        }
      }
      digitalWrite(relay, HIGH);
      sec = sec - 1;
      delay(1000);
      if (sec == -1)
      {
        sec = 59;
        Min = Min - 1;
      }
      if (Min == -1)
      {
        Min = 59;
        hrs = hrs - 1;
      }
      if (hrs == -1) hrs = 0;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(4, 0);
      if (hrs <= 9)
      {
        lcd.print('0');
      }
      lcd.print(hrs);
      lcd.print(':');
      if (Min <= 9)
      {
        lcd.print('0');
      }
      lcd.print(Min);
      lcd.print(':');
      if (sec <= 9)
      {
        lcd.print('0');
      }
      lcd.print(sec);
      if (hrs == 0 && Min == 0 && sec == 0)
      {
        digitalWrite(relay, LOW);
        lcd.setCursor(4, 0);
        RUN = false;
        for (int i = 0; i < 5; i++)
        {
          digitalWrite(buzz, HIGH);
          delay(100);
          digitalWrite(buzz, LOW);
          delay(100);
        }
        INIT();
      }
    }
  }
  if (digitalRead(set) == LOW)
  {
    delay(500);
    while (sec_flag)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SET SECONDS: ");
      lcd.print(sec);
      delay(100);
      if (digitalRead(inc) == LOW)
      {
        sec = sec + 1;
        if (sec >= 60) sec = 0;
        delay(100);
      }
      if (digitalRead(dec) == LOW)
      {
        sec = sec - 1;
        if (sec <= -1) sec = 0;
        delay(100);
      }
      if (digitalRead(set) == LOW)
      {
        sec_flag = false;
        delay(250);
      }
    }
    while (min_flag)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SET MINUTE: ");
      lcd.print(Min);
      delay(100);
      if (digitalRead(inc) == LOW)
      {
        Min = Min + 1;
        if (Min >= 60) Min = 0;
        delay(100);
      }
      if (digitalRead(dec) == LOW)
      {
        Min = Min - 1;
        if (Min <= -1) Min = 0;
        delay(100);
      }
      if (digitalRead(set) == LOW)
      {
        min_flag = false;
        delay(250);
      }
    }
    while (hrs_flag)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SET HOUR: ");
      lcd.print(hrs);
      delay(100);
      if (digitalRead(inc) == LOW)
      {
        hrs = hrs + 1;
        if (hrs > 23) hrs = 0;
        delay(100);
      }
      if (digitalRead(dec) == LOW)
      {
        hrs = hrs - 1;
        if (hrs <= -1) hrs = 0;
        delay(100);
      }
      if (digitalRead(set) == LOW)
      {
        hrs_flag = false;
        delay(250);
      }
    }
    if (hrs == 0 && Min == 0 && sec == 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  INVALID TIME");
      delay(2000);
    }
    else
    {
      EEPROM.write(add_hrs, hrs);
      EEPROM.write(add_min, Min);
      EEPROM.write(add_sec, sec);
    }
    INIT();
  }
}

void INIT()
{
  hrs = EEPROM.read(add_hrs);
  Min = EEPROM.read(add_min);
  sec = EEPROM.read(add_sec);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start / Set Time");
  lcd.setCursor(4, 1);
  if (hrs <= 9)
  {
    lcd.print('0');
  }
  lcd.print(hrs);
  lcd.print(':');
  if (Min <= 9)
  {
    lcd.print('0');
  }
  lcd.print(Min);
  lcd.print(':');
  if (sec <= 9)
  {
    lcd.print('0');
  }
  lcd.print(sec);
  sec_flag = true;
  min_flag = true;
  hrs_flag = true;
  delay(500);
}
