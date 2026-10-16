
#include <Servo.h>

Servo myservo;

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

long duration;
float distance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  myservo.attach(6);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo, with a timeout
  duration = pulseIn(echoPin, HIGH, 30000UL);

  // Calculate the distance
  distance = (duration * 0.0343) / 2.0;

  // Display the distance
  if (duration == 0) {
    Serial.println("No echo detected");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Move servo and control buzzer according to distance
  if (duration == 0) {
    // No echo detected
    myservo.write(0);
    tone(buzzerPin, 2000);
    delay(200);
    noTone(buzzerPin);
    delay(200);
    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);

  } else if (distance <= 10 && distance > 0) {
    // Object is very close
    myservo.write(90);
    tone(buzzerPin, 1000);

  } else if (distance > 10 && distance <= 30) {
    // Object is at a medium distance
    myservo.write(45);
    noTone(buzzerPin);

  } else if (distance > 30) {
    // Object is far away: two short beeps
    myservo.write(0);

    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
    delay(200);

    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
  }

  // Wait before the next measurement
  delay(2000);
}
