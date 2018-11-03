#include <Stepper.h>
int serialSensor = 0;
int serialTemp = 1;
int soilVal = 0;
int soilPin = 2;
int soilPower = 7;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

  pinMode(soilPower, OUTPUT);
  digitalWrite(soilPower,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (counter == 2000) {
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
  }
  
  delay(10);
  counter += 10;
}
int readSoil(){
  digitalWrite(soilPower, HIGH);
  soilVal=analogRead(soilPin);
  digitalWrite(soilPower,LOW);
  return soilVal;
}
