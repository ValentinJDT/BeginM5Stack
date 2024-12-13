#include <Arduino.h>

#include <M5Stack.h>
#include <SPI.h>
#include <MFRC522.h>
#include <GoPlus2.h>
#include <MODULE_GRBL13.2.h>
#include <WiFi.h>
#include <Dolibarr.h>
#include <ArduinoJson.h>

MFRC522 mfrc522(0x28);
// GoPlus2 goPlus;

// Paramètres du moteur
const float angle_pas = 1.8;                      // Angle de pas du moteur en degrés
const int steps_per_revolution = 360 / angle_pas; // Nombre de pas par révolution
const int steps_for_360 = steps_per_revolution;   // Nombre de pas pour un tour complet
const float duration = 0.5;                       // Durée du mouvement en secondes
int value = 0;
int old = -1;

Dolibarr dolibarr("http://86.202.221.234:8088");
// GRBL stepper_motor_driver = GRBL(0x70);

void setText(String text, int size, int x, int y)
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(size);
  M5.Lcd.println(text);
}

// MFRC522 mfrc522(0x28); // Instance de la classe MFRC522

String readerCard(MFRC522 *mfrc522)
{
  String rfid_read = "";

  Serial.print(mfrc522->PICC_IsNewCardPresent());
  Serial.print(" ");
  Serial.println(mfrc522->PICC_ReadCardSerial());

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

void setup()
{
  M5.begin();

  // Wire.begin(21, 22);
  Wire.begin();
  //goPlus.begin();
  mfrc522.PCD_Init(21, 22);
  // stepper_motor_driver.Init(&Wire);
  // stepper_motor_driver.setMode("absolute");
  Serial.begin(115200);

  WiFi.begin("VAL-PORTABLE 8610", "n2460F;0");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  dolibarr.connect("admin", "admin");
  Serial.println("Connected to Dolibarr !");

  setText("Retirez tous les colis du tapis avant le lancement.", 2, 0, 0);
}


void loop()
{
  readerCard(&mfrc522);
}

// void loop()
// {
//   M5.update();
//   if (M5.BtnA.isPressed())
//   {
    
//   }
// }


// void loop()
// {
//   M5.update();

//   if (M5.BtnA.pressedFor(2000))
//   {
//     value += 20;
//   }
//   else if (M5.BtnA.isPressed())
//   {
//     value += 10;
//   }

//   if (old != value)
//   {
//     old = value;

//     goPlus.Servo_write_angle(SERVO_NUM0_PW, value);
//     Serial.println(value);
//   }

//   delay(100);
// }
