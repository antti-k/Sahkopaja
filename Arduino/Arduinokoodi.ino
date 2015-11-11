#include <Wire.h>
int addr= 0x23; // kun kytketty GND
void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  I2Cwrite(1);
  pinMode(17,OUTPUT); // 17=A3 Unolla
  digitalWrite(17,LOW); // kun kytketty GND
  I2Cwrite(0x10); // valitaan moodi
  Serial.println("Running...");
}
void I2Cwrite(int data){
  Wire.beginTransmission(addr); 
  Wire.write(data);
  Wire.endTransmission();
}
unsigned int I2Cread(){
  Wire.beginTransmission(addr);
  Wire.requestFrom(addr, 2);
  unsigned int intensity = Wire.read();
  intensity <<= 8;
  intensity += Wire.read();
  Wire.endTransmission();
  delay(200);
  return intensity;
}

void loop() {
  Serial.println(I2Cread());
}
