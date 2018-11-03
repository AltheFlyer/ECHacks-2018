#include <Stepper.h>
int serialSensor = 0;
int serialTemp = 1;
int t = 0;
const int stepsPerRevolution = 4096;
int stepCount = 0;
Stepper myStepper(stepsPerRevolution,8,9,10,11);

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawLight = analogRead(serialSensor);
  int rawTemp = analogRead(serialTemp);
  Serial.print("Light: ");
  Serial.println(rawLight);

  myStepper.setSpeed(8);
  myStepper.step(stepsPerRevolution / 100);
  
float R = 1023.0/rawTemp-1.0;
float B = 4275;
float temperature = 1.0/(log(R)/B+1/298.15)-273.15;
Serial.print("Temperature: ");
Serial.println(temperature);

  if (rawLight > 100) {
    Serial.println("BRIGHT");
  }
  Serial.println("rotates");
  delay(10);
}
