// defines pins numbers
const int trigPin = 4;
const int echoPin = 2;
// defines variables
long duration;
int distance;

/****/

//velocity
#define M1 10  // Enable Pin for motor 1
#define M2 11  // Enable Pin for motor 2

//direction
//Motor 1
#define M1dir1 7  // Control pin 1 for motor 1
#define M1dir2 8  // Control pin 2 for motor 1
//Motor 2
#define M2dir1 12  // Control pin 1 for motor 2
#define M2dir2 13  // Control pin 2 for motor 2

float vel;
float velM1;
float velM2;

//int forward = 1;
//int reverse = 2;
//int turn = 3;
//int stoped = 4;
//int state = stoped;

const float LED1 = 3;
float luz;

const int SenOut = A4;
int sensorValue = 0;

int noise = 0;
int noise0;
int noise1;

#include <Servo.h>
Servo servo;
int angle = 91;

void setup() {

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  pinMode(LED1, OUTPUT);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  pinMode(M1dir1, OUTPUT);
  pinMode(M1dir2, OUTPUT);
  pinMode(M2dir1, OUTPUT);
  pinMode(M2dir2, OUTPUT);

  pinMode(SenOut, INPUT);

  servo.attach(5);
  servo.write(angle);
}

void loop() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.println();

  luz = map(distance, 0, 255, 10, 255);

  analogWrite(LED1, luz);

  if (distance <= 30) {
    velM1 = 0;
    velM2 = 0;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, LOW);
    digitalWrite(M1dir2, LOW);

    digitalWrite(M2dir1, LOW);
    digitalWrite(M2dir2, LOW);
    
    velM1 = 85;
    velM2 = 85;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, LOW);
    digitalWrite(M1dir2, HIGH);

    digitalWrite(M2dir1, LOW);
    digitalWrite(M2dir2, HIGH);

    delay(1000);
  }
  if (distance > 30 && distance < 50) {
    velM1 = 0;
    velM2 = 0;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, LOW);
    digitalWrite(M1dir2, LOW);

    digitalWrite(M2dir1, LOW);
    digitalWrite(M2dir2, LOW);

    velM1 = 0;
    velM2 = 85;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, LOW);
    digitalWrite(M1dir2, LOW);

    digitalWrite(M2dir1, LOW);
    digitalWrite(M2dir2, HIGH);

    delay(500);
  }
  if (distance >= 50 && distance <= 100) {
    velM1 = 85;
    velM2 = 85;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, HIGH);
    digitalWrite(M1dir2, LOW);

    digitalWrite(M2dir1, HIGH);
    digitalWrite(M2dir2, LOW);
    
    velM1 = 0;
    velM2 = 85;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, LOW);
    digitalWrite(M1dir2, LOW);

    digitalWrite(M2dir1, HIGH);
    digitalWrite(M2dir2, LOW);

    delay(500);
  }
  if (distance >= 100) {
    velM1 = 85;
    velM2 = 85;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, HIGH);
    digitalWrite(M1dir2, LOW);

    digitalWrite(M2dir1, HIGH);
    digitalWrite(M2dir2, LOW);
  }

  if (noise == 0) {
    sensorValue = analogRead(SenOut);
    noise0 = sensorValue;
    noise = 1;
  }

  if (noise == 1) {
    noise0 = noise0;
    sensorValue = analogRead(SenOut);
    noise1 = sensorValue;
  }

  Serial.print("Ruido0: ");
//  Serial.println(noise0);
  Serial.print("Ruido1: ");
  Serial.println(noise1);
  Serial.println();
  delay(300);

  //if ((noise1 - noise0) > 20) {
  if (noise1 > 1023) {

    velM1 = 0;  
    velM2 = 0;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, LOW);
    digitalWrite(M1dir2, LOW);

    digitalWrite(M2dir1, LOW);
    digitalWrite(M2dir2, LOW);

    angle = 0;
    servo.write(angle);
    delay(1000);
    angle = 90;
    servo.write(angle);
    delay(1000);

    velM1 = 85;
    velM2 = 85;

    analogWrite(M1, velM1);
    analogWrite(M2, velM2);

    digitalWrite(M1dir1, LOW);
    digitalWrite(M1dir2, HIGH);

    digitalWrite(M2dir1, LOW);
    digitalWrite(M2dir2, HIGH);
  }
}
