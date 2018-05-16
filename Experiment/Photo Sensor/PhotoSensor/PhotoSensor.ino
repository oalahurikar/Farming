int Photopin = A1;
int Light_level = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Light_level = analogRead(Photopin);
  Serial.println(Light_level);
  delay(1000);
}
