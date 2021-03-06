#include <Stepper.h>
#define LED 2
int serialSensor = 0;
int serialTemp = 1;
int soilVal = 0;
int soilPin = 4;
int soilPower = 7;
int counter = 0;
float interval = 1000;
bool setInterval = false;
int threshold = 500;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

  pinMode(soilPower, OUTPUT);
  digitalWrite(soilPower, LOW);

  pinMode(LED, OUTPUT);
 
  while(Serial.available() == 0){}
  threshold = Serial.parseInt();
  
  while(Serial.available() == 0){}
  interval = Serial.parseFloat() * 1000;
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.print("Soil:");
    int soilMoist = readSoil();
    Serial.println(soilMoist);
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

    if (soilMoist < threshold){
      digitalWrite(LED, LOW);
    } else {
      digitalWrite(LED, HIGH);
    }
  
  delay(interval);
}
int readSoil(){
  digitalWrite(soilPower, HIGH);
  soilVal=analogRead(soilPin);
  digitalWrite(soilPower,LOW);
  return soilVal;
}
