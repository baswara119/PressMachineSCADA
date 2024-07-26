#include <PZEM004Tv30.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial pzemSWSerial(11, 12);
PZEM004Tv30 pzem; // Software Serial pin 8 (RX) & 9 (TX)
void setup() {
  pinMode(A0, INPUT);
  Serial.begin(115200);
  while(!Serial);

  pzem = PZEM004Tv30(pzemSWSerial);
}
void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  Serial.println("[1," + String(voltage, 2) + "," + String(current, 3) + "," + String(power, 2) + "," + String(energy, 2) + "," + String(frequency, 2) + "," + String(pf, 2) +  "," + String(analogRead(0), DEC) + "]");

  delay(100);
}