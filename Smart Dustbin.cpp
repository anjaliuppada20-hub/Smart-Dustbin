#include <Servo.h>

// Ultrasonic sensor pins
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

// Servo pin
const int SERVO_PIN = 6;

// LED pins
const int GREEN_LED = 4;
const int RED_LED = 5;

Servo lidServo;

// Distance at which lid opens
const int OPEN_DISTANCE = 20;

// Time before closing the lid
const unsigned long OPEN_TIME = 3000;


long getDistance() {

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  long duration = pulseIn(
    ECHO_PIN,
    HIGH,
    30000
  );

  if (duration == 0) {
    return 999;
  }

  // Calculate distance in cm
  long distance = duration * 0.034 / 2;

  return distance;
}


void openLid() {

  lidServo.write(90);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  Serial.println("Lid: OPEN");
}


void closeLid() {

  lidServo.write(0);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  Serial.println("Lid: CLOSED");
}


void setup() {

  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  lidServo.attach(SERVO_PIN);

  // Start with lid closed
  closeLid();

  Serial.println(
    "Smart Dustbin Started"
  );
}


void loop() {

  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= OPEN_DISTANCE) {

    openLid();

    delay(OPEN_TIME);

    closeLid();

  }

  delay(200);
}
