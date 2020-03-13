void setup() {
  // put your setup code here, to run once:
pinMode(3, OUTPUT);
pinMode(A0, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0) / 2 * 2);
  analogWrite(3, analogRead(A0) / 2 * 2);
  delay(100);
}
