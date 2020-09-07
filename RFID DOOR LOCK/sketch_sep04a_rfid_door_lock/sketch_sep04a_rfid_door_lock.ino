#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  pinMode(19, OUTPUT); //Relay
  pinMode(16, OUTPUT); //Buzzer
  SPI.begin();
  mfrc522.PCD_Init();
  digitalWrite(16, HIGH);
  delay(750);
  digitalWrite(16, LOW);
}
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if ((content.substring(1) == "37 26 22 26") || (content.substring(1) == "87 EE 12 26"))
  {
    digitalWrite(16, HIGH);
    Serial.println("Authorized access");
    digitalWrite(19, !digitalRead(19));
    Serial.println();
    delay(200);
    digitalWrite(16, LOW);
    delay(1000);
  }

  else   {
    Serial.println(" Access denied");
    digitalWrite(16, HIGH);
    delay(750);
    digitalWrite(16, LOW);
  }
}
