#include <Stepper.h>
int serialSensor = 0;
int serialTemp = 1;
int soilVal = 0;
int soilPin = 2;
int soilPower = 7;
int counter = 0;
<<<<<<< HEAD
int ledOut = 4;
=======
float interval = 1000;
bool setInterval = false;
>>>>>>> b07618d269730a44b7ad699ce0ba79ac5526c90c

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

  pinMode(soilPower, OUTPUT);
  digitalWrite(soilPower,LOW);
<<<<<<< HEAD

  pinMode(ledOut, OUTPUT);
  digitalWrite(ledOut, LOW);
=======
  while(Serial.available() == 0){}
  interval = Serial.parseFloat() * 1000;
>>>>>>> b07618d269730a44b7ad699ce0ba79ac5526c90c
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.print("Soil:");
    Serial.println(readSoil());
    counter = 0;
    int rawLight = analogRead(serialSensor);
    int rawTemp = analogRead(serialTemp);
    Serial.print("Light: ");
    Serial.println(rawLight);
    
    float R = 1023.0/rawTemp-1.0;
    float B = 4275;
    float temperature = 1.0/(log(R)/B+1/298.15)-273.15;
    Serial.print("Temperature: ");
    Serial.println(temperature);
  
    if (rawLight > 100) {
      Serial.println("BRIGHT");
    }
  
  delay(interval);
}
int readSoil(){
  digitalWrite(soilPower, HIGH);
  soilVal=analogRead(soilPin);
  digitalWrite(soilPower,LOW);
  return soilVal;
}
