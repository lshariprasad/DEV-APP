#include <TinyGPS++.h>

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);   // GPS baud rate
  Serial.println("GPS Testing Started...");
}

void loop() {
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());

    if (gps.location.isUpdated()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);

      Serial.print("Satellites: ");
      Serial.println(gps.satellites.value());

      Serial.println("-------------------");
    }
  }
}
