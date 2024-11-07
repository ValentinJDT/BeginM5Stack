#include <Arduino.h>

#include <M5Stack.h>
#include <SPI.h>
#include <MFRC522.h>
#include <GoPlus2.h>
#include <MODULE_GRBL13.2.h>
#include <WiFi.h>
#include <DolibarrClient.h>
#include <ArduinoJson.h>

// MFRC522 mfrc522(40); // Instance de la classe MFRC522
// GoPlus2 goPlus;
// String readerCard(MFRC522 *mfrc522);

// Paramètres du moteur
const float angle_pas = 1.8;                      // Angle de pas du moteur en degrés
const int steps_per_revolution = 360 / angle_pas; // Nombre de pas par révolution
const int steps_for_360 = steps_per_revolution;   // Nombre de pas pour un tour complet
const float duration = 0.5;                       // Durée du mouvement en secondes

// GRBL stepper_motor_driver = GRBL(0x70);

void setup()
{
  M5.begin();

  // Wire.begin(21, 22);
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

  Dolibarr dolibarr("http://86.202.221.234:8088");
  String resp = dolibarr.connect("admin", "admin");

  String doc = dolibarr.getProductWarehouse("1");

  Serial.println("Warehouse : " + doc);
}


void loop()
{
  // M5.update();
  // if (M5.BtnA.isPressed())
  // {
  //   float speed = steps_for_360 / duration;

  //   stepper_motor_driver.setMotor(1800 * 2, 1800 * 2, 1800 * 2, speed);
  // }
}

/*
void loop()
{
  M5.update();

  if (M5.BtnA.pressedFor(2000))
  {
    value += 10;
  }
  else if (M5.BtnA.pressedFor(500))
  {
    value += 5;
  }

  if (old != value)
  {
    old = value;

    goPlus.Servo_write_angle(SERVO_NUM0_PW, value);
  }

  delay(1000);
}
*/