#include <Arduino.h>

#include <M5Stack.h>
#include <SPI.h>
#include <MFRC522.h>
#include <GoPlus2.h>

MFRC522 mfrc522(0x28); // Instance de la classe MFRC522
GoPlus2 goPlus;
String readerCard(MFRC522 *mfrc522);

void setup()
{
  mfrc522.PCD_Init();
  // goPlus.begin();
  Serial.begin(115200);
}

void loop()
{
  readerCard(&mfrc522);
}

String readerCard(MFRC522 *mfrc522)
{
  String rfid_read = "";
  if (!mfrc522->PICC_IsNewCardPresent() || !mfrc522->PICC_ReadCardSerial())
  {
    delay(200);

    return rfid_read;
  }

  if (mfrc522->uid.size > 0)
  {
    for (byte i = 0; i < mfrc522->uid.size; i++)
    {
      rfid_read += String(mfrc522->uid.uidByte[i], HEX);
    }
  }

  Serial.println(rfid_read);

  return rfid_read;
}

// void loop()
// {
//   goPlus.Servo_write_angle(SERVO_NUM0_PW, 180);
//   // goPlus.Servo_write_angle(SERVO_NUM1_PW, 180);
//   // goPlus.Servo_write_angle(SERVO_NUM2_PW, 180);
//   // goPlus.Servo_write_angle(SERVO_NUM3_PW, 180);
//   Serial.println("Servo 180");
//   delay(1000);
//   goPlus.Servo_write_angle(SERVO_NUM0_PW, 0);
//   // goPlus.Servo_write_angle(SERVO_NUM1_PW, 0);
//   // goPlus.Servo_write_angle(SERVO_NUM2_PW, 0);
//   // goPlus.Servo_write_angle(SERVO_NUM3_PW, 0);
//   Serial.println("Servo 0");
//   delay(1000);
// }