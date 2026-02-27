void setup() {
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(A0);

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  delay(1000);
}
