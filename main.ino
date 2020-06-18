#include "AIS_NB_SIM7020E.h"
#include <SHT3x.h>
#include <TinyGPS++.h>
#include "HardwareSerial.h"
#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 1800
static const uint32_t GPSBaud = 9600;
AIS_NB_SIM7020E application;
SHT3x Sensor;
TinyGPSPlus gps;
HardwareSerial ss(1);
String toupload;
float Temperature = 0, Humidity = 0;
String latgps = "0", longgps = "0";
String Dervice_key = "Key on web site"; //get key on web site https://pmsiot.com/devicelist /
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Sensor.Begin();
  ss.begin(GPSBaud, SERIAL_8N1, 13, 14);



  application.tcp = false;
  application.udp = false;
  application.debug = false;

  application.setupDevice_fast(); // not have set soket
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");


}
void loop() {

  Sensor.UpdateData();

  Serial.print(Sensor.GetTemperature()); //Celsius
  Serial.write("\xC2\xB0"); //The Degree symbol
  Serial.print("C");
  Serial.print(" | ");
  Temperature = Sensor.GetTemperature();
  Serial.print(Sensor.GetRelHumidity());
  Serial.print("%");
  Serial.print(" | ");
  Humidity = Sensor.GetRelHumidity();
  while (ss.available() > 0)
    if (gps.encode(ss.read())) {

      if (gps.location.isValid())
      {
        latgps = String(gps.location.lat(), 6);
        longgps = String(gps.location.lng(), 6);
      }
      else
      {

        latgps = "0";
        longgps = "0";
      }

    }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
  }
  Serial.print( latgps);
  Serial.print(" | ");
  Serial.print( longgps);
  if (latgps == "0" &&  longgps == "0") {
    Serial.println(F("\nGPS NOT signal"));
  } else {
    Serial.println();
  }
  application.http_get("http://34.87.128.17/", "/api", "key=" + Dervice_key + "&temp=" + String(Temperature) + "&moisture=" + String(Humidity) + "&pos_lat=" + latgps + "&pos_long=" + longgps);

  delay(5000);
  Serial.println("Going to sleep now");

  Serial.flush();
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
}
