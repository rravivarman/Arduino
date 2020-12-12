#include <LiquidCrystal.h>

int currentPin = 6;              //Assign CT input to pin 1
double kilos = 0;
int peakPower = 0;
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);  //Assign LCD screen pins, as per LCD shield requirements

void setup()
{
  lcd.begin(16, 2);             // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();
  lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
  lcd.print("    Arduino     ");
  lcd.setCursor(0, 1);          // set cursor to column 0, row 0 (the first row)
  lcd.print("  Energy Meter  ");
  delay(2000);
}

void loop()
{
  int current = 0;
  int maxCurrent = 0;
  int minCurrent = 1000;
  for (int i = 0 ; i <= 200 ; i++) //Monitors and logs the current input for 200 cycles to determine max and min current
  {
    current = analogRead(currentPin);    //Reads current input and records maximum and minimum current
    if (current >= maxCurrent)
      maxCurrent = current;
    else if (current <= minCurrent)
      minCurrent = current;
  }
  if (maxCurrent <= 517)
  {
    maxCurrent = 516;
  }
  double RMSCurrent = ((maxCurrent - 516) * 0.707) / 11.8337; //Calculates RMS current based on maximum value
  int RMSPower = 230 * RMSCurrent;  //Calculates RMS Power Assuming Voltage 220VAC, change to 110VAC accordingly
  if (RMSPower > peakPower)
  {
    peakPower = RMSPower;
  }
  kilos = kilos + (RMSPower * (2.05 / 60 / 60 / 1000)); //Calculate kilowatt hours used
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);          // Displays all current data
  lcd.print(RMSCurrent);
  lcd.print("A");
  lcd.setCursor(10, 0);
  lcd.print(RMSPower);
  lcd.print("W");
  lcd.setCursor(0, 1);
  lcd.print(kilos);
  lcd.print("kWh");
  lcd.setCursor(10, 1);
  lcd.print(peakPower);
  lcd.print("W");
}
