// =========================================
// ADXL335 Accelerometer Project
// X -> A1
// Y -> A2
// Z -> A3
// =========================================

const int xPin = A1;
const int yPin = A2;
const int zPin = A3;

// Adjust these values after calibration
const int centerX = 512;
const int centerY = 512;
const int threshold = 50;

void setup() {
  Serial.begin(9600);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);

  Serial.println("==================================");
  Serial.println(" ADXL335 Accelerometer Started");
  Serial.println("==================================");
}

void loop() {

  int x = analogRead(xPin);
  int y = analogRead(yPin);
  int z = analogRead(zPin);

  Serial.print("X: ");
  Serial.print(x);

  Serial.print(" | Y: ");
  Serial.print(y);

  Serial.print(" | Z: ");
  Serial.print(z);

  Serial.print(" | Direction: ");

  if (x > centerX + threshold) {
    Serial.print("RIGHT");
  }
  else if (x < centerX - threshold) {
    Serial.print("LEFT");
  }
  else if (y > centerY + threshold) {
    Serial.print("FORWARD");
  }
  else if (y < centerY - threshold) {
    Serial.print("BACKWARD");
  }
  else {
    Serial.print("LEVEL");
  }

  Serial.println();

  delay(500);
}
