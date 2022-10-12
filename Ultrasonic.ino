#include <HCSR04.h>
#include <Wire.h>

UltraSonicDistanceSensor distanceSensor(2, 3, 400);  // Initialize sensor that uses digital pins 13 and 12.
int buzzerPin = 12;
float startingDistanceCm = -1;

void setup() {
  pinMode(buzzerPin, OUTPUT);

  delay(1000);
  
  double value = distanceSensor.measureDistanceCm();
  startingDistanceCm = value > 0 ? value : 400;

  // Cut 2% to avoid inaccuracies to click.
  startingDistanceCm *= 0.98;
}

void loop() {
  double value = distanceSensor.measureDistanceCm();
  if(value < 0)
    value = 400;

  double closeness = 1.0 - (value / startingDistanceCm);
  // If further away than startingDistance, set to 0.
  closeness = closeness < 0 ? 0 : closeness;
  if(closeness > 0)
    click(closeness);
  
  delay(50);
  // Wait longer the further away. Clicking faster the closer.
  delay((int)(450 * (1 - closeness)));
}

void click(double closeness) {
  // Generate a clicking sound.
  for (int j = 0; j < 2; j++) {
    digitalWrite(buzzerPin, HIGH);
    delay(1);
    digitalWrite(buzzerPin, LOW);
    delay(1);
  }
}