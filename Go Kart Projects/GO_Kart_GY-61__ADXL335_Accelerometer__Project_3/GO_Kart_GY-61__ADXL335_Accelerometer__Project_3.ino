void setup() {
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(A1);
  int y = analogRead(A2);
  int z = analogRead(A3);

  Serial.print("X: "); Serial.print(x);
  Serial.print(" | Y: "); Serial.print(y);
  Serial.print(" | Z: "); Serial.println(z);

  delay(500);
}
