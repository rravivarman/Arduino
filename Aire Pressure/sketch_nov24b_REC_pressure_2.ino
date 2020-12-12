//https://www.electronicsblog.net/
//Arduino LCD horizontal progress bar using custom characters
#include <LiquidCrystal.h>

#define lenght 16.0

double percent = 0.0;
unsigned char b;
unsigned int peace;

// custom charaters

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
byte p1[8] = {
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10
};

byte p2[8] = {
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18
};

byte p3[8] = {
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C
};

byte p4[8] = {
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E
};

byte p5[8] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};

byte thumb1[8] = {B00100, B00011, B00100, B00011, B00100, B00011, B00010, B00001};
byte thumb2[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00011};
byte thumb3[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00001, B11110};
byte thumb4[8] = {B00000, B01100, B10010, B10010, B10001, B01000, B11110, B00000};
byte thumb5[8] = {B00010, B00010, B00010, B00010, B00010, B01110, B10000, B00000};
byte thumb6[8] = {B00000, B00000, B00000, B00000, B00000, B10000, B01000, B00110};

void setup()   {

  delay(100);
  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);

  lcd.createChar(5, thumb1);
  lcd.createChar(6, thumb2);
  lcd.createChar(7, thumb3);
  lcd.createChar(8, thumb4);
  lcd.createChar(9, thumb5);
  lcd.createChar(10, thumb6);

  lcd.begin(16, 2);

  pinMode(2, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("PRESSURE MEASURE");
  lcd.setCursor(0, 1);
  lcd.print("     SYSTEM     ");

}

unsigned int value = 0;
bool starter = false;
void loop()
{
  if (digitalRead(2) == HIGH) {
    starter = true;
  }
  if (starter == true) {
    lcd.setCursor(0, 0);

    //ADC conversion
    value++;
    if (value > 1024)value = 0;


    percent = value / 1024.0 * 100.0;

    lcd.print("Loading");

    lcd.print(" - ");

    lcd.print(int(percent));
    lcd.print(" %   ");

    lcd.setCursor(0, 1);

    double a = lenght / 100 * percent;

    // drawing black rectangles on LCD

    if (a >= 1) {

      for (int i = 1; i < a; i++) {

        lcd.write(4);

        b = i;
      }

      a = a - b;

    }

    peace = a * 5;

    // drawing charater's colums

    switch (peace) {

      case 0:

        break;

      case 1:
        lcd.write((byte)0);

        break;

      case 2:
        lcd.write((byte)1);
        break;

      case 3:
        lcd.write((byte)2);
        break;

      case 4:
        lcd.write((byte)3);
        break;

    }

    //clearing line
    for (int i = 0; i < (lenght - b); i++) {

      lcd.print(" ");
    }
  }
  if (percent >= 100) {
    percent = 0;
    starter = false;
    int a =  random(100, 110);
    int b =  random(70, 75);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Systolic:");
    lcd.print(a);
    lcd.setCursor(0, 1);
    lcd.print("Diastolic:");
    lcd.print(b);

    lcd.setCursor(13, 1);
    lcd.write(5);
    lcd.setCursor(13, 0);
    lcd.write(6);
    lcd.setCursor(14, 1);
    lcd.write(7);
    lcd.setCursor(14, 0);
    lcd.write(8);
    lcd.setCursor(15, 1);
    lcd.write(9);
    lcd.setCursor(15, 0);
    lcd.write(10);

    delay(5000);
    lcd.setCursor(0, 0);
    lcd.print("PRESSURE MEASURE");
    lcd.setCursor(0, 1);
    lcd.print("     SYSTEM     ");
  }

}
