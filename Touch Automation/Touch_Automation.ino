#include <Adafruit_GFX_AS.h>
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define YP A1
#define XM A2
#define YM 7
#define XP 6

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int gear_state = 0;

uint16_t g_identifier;

const int relay1 = 19;
const int relay2 = 10;
const int relay4 = 11;
const int relay3 = 12;

void setup(void) {
  Serial.begin(9600);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  tft.reset();
  delay(10);
  g_identifier = tft.readID();
  tft.begin(g_identifier);
  update_display("SYSTEM STARTED");
}
void update_display(String gear) {
  tft.fillScreen(WHITE);
  tft.setRotation(0);

  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.setCursor(30, 15);
  tft.println("AUTOMATION");

  //ON-BUTTONS-TEMPLATE
  //tft.fillCircle(40, 90, 25, GREEN);
  tft.fillRoundRect(25, 60, 80, 70, 10, GREEN);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(38, 88);
  tft.println("DEV-1");

  tft.fillRoundRect(130, 60, 80, 70, 10, GREEN);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(143, 88);
  tft.println("DEV-2");

  tft.fillRoundRect(25, 150, 80, 70, 10, GREEN);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(38, 173);
  tft.println("DEV-3");

  tft.fillRoundRect(130, 150, 80, 70, 10, GREEN);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(143, 173);
  tft.println("DEV-4");
  
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(35, 270);
  tft.println(gear);
}
void loop(){
  Point p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > 0 && p.z < 500) {
    Serial.print(p.x); Serial.print(","); Serial.print(p.y); Serial.print(","); Serial.println(p.z);

    if((p.y>330 && p.y<460) && (p.x>633 && p.x<846)){
      if(digitalRead(relay1)==HIGH){
        update_display("DEVICE 1 OFF");
        digitalWrite(relay1,LOW);
        Serial.println("DEVICE 1 OFF");
        delay(500);
      }else{
        update_display("DEVICE 1 ON");
        digitalWrite(relay1,HIGH);
        Serial.println("DEVICE 1 ON");
        delay(500);
      }
    }

      if((p.y>330 && p.y<460) && (p.x>250 && p.x<500)){
      if(digitalRead(relay2)==HIGH){
        update_display("DEVICE 2 OFF");
        digitalWrite(relay2,LOW);
        Serial.println("DEVICE 2 OFF");
        delay(500);
      }else{
        update_display("DEVICE 2 ON");
        digitalWrite(relay2,HIGH);
        Serial.println("DEVICE 2 ON");
        delay(500);
      }
    }

    if((p.y>540 && p.y<700) && (p.x>250 && p.x<500)){
      if(digitalRead(relay3)==HIGH){
        update_display("DEVICE 4 OFF");
        digitalWrite(relay3,LOW);
        Serial.println("DEVICE 4 OFF");
        delay(500);
      }else{
        update_display("DEVICE 4 ON");
        digitalWrite(relay3,HIGH);
        Serial.println("DEVICE 4 ON");
        delay(500);
      }
    }

    if((p.y>540 && p.y<700) && (p.x>633 && p.x<846)){
      if(digitalRead(relay4)==HIGH){
        update_display("DEVICE 3 OFF");
        digitalWrite(relay4,LOW);
        Serial.println("DEVICE 3 OFF");
        delay(500);
      }else{
        update_display("DEVICE 3 ON");
        digitalWrite(relay4,HIGH);
        Serial.println("DEVICE 3 ON");
        delay(500);
      }
    }
  }
}
