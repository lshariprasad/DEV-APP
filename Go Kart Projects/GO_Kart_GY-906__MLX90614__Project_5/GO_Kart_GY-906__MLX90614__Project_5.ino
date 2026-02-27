#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  Serial.println("MLX90614 Testing...");

  if (!mlx.begin()) {
    Serial.println("Sensor not found. Check wiring!");
    while (1);
  }
}

void loop() {
  Serial.print("Ambient Temp = ");
  Serial.print(mlx.readAmbientTempC());
  Serial.print(" °C");

  Serial.print(" | Object Temp = ");
  Serial.print(mlx.readObjectTempC());
  Serial.println(" °C");

  delay(1000);
}
