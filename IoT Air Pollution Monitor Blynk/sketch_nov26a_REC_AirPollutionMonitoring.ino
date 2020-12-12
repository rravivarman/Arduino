#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "RN4YnhY3cpc7wpc_vcKBfb78bi2q3Uuk";
char ssid[] = "embedded";
char pass[] = "embedded";

#include <LiquidCrystal.h>
const int rs = D6, en = D5, d4 = D4, d5 = D3, d6 = D2, d7 = D1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

double air_quality;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Pollution:");
  air_quality = ((analogRead(A0) / 512.0) * 100.0);
  lcd.print(air_quality);
  lcd.print("%");
  Serial.print(air_quality);
  Serial.print(", ");
  lcd.setCursor(0, 1);
  Blynk.virtualWrite(V0, air_quality);
  if (air_quality <= 20.0 ) {
    lcd.print("State : Normal  ");
    Serial.println("Normal");
    Blynk.virtualWrite(V1, "NORMAL");
  } else if (air_quality > 20.0 && air_quality < 70.0) {
    lcd.print("State : Medium  ");
    Serial.println("Medium");
    Blynk.virtualWrite(V1, "MEDIUM");
  } else {
    lcd.print("State : Danger  ");
    Serial.println("Danger");
    Blynk.virtualWrite(V1, "DANGER");
  }
   Blynk.run();
   delay(500);
}
