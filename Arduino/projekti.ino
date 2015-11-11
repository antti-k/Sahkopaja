#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define Smin 0
#define Smax 89
int addr= 0x23; // kun kytketty GND
Servo serv;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  serv.attach(9); // servo alustus
  serv.write(Smin); // servo alkutilaan
  pinMode(13, OUTPUT); // LED alustus
  digitalWrite(13, LOW);// LED pois päältä
  lcd.begin(16,2);
  pinMode(7,INPUT); // Esim nappi (mittauksen käynnistys)
  Wire.begin(); 
  I2Cwrite(1);
  pinMode(17,OUTPUT); // 17=A3 Unolla
  digitalWrite(17,LOW); // kun kytketty GND
  I2Cwrite(0x10); // valitaan moodi
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
char i = 0;
char kaanna(){
  serv.write(i);
  delay(50);
  i++;
  if (i>Smax)
    return -1;
}
char progress;
char aloitus(){
  if (digitalRead(7)==HIGH){
    digitalWrite(13, HIGH);// LED päälle
    progress=0;
    lcd.setCursor(0,0);
    lcd.print(progress);
    return 1;
  }
}

void mittaus(unsigned int Noise){
  char t=1;
  while (t!=-1){
    t=kaanna();
    Serial.println(I2Cread()-Noise);
    progress=i/Smax*100; // jos se näyttö niin kirjota progress näyttöön
    lcd.setCursor(0,0);
    lcd.print(progress);
    if (t==-1){
      i=0;
      digitalWrite(13,LOW);
    }
  }
}

void loop() {
  unsigned int NInt = I2Cread(); // tausta kirkkaus 
  if (aloitus()==1)
    mittaus(NInt);  
}
