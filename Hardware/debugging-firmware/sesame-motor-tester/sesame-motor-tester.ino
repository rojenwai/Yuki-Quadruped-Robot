#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// ======================================================
// PCA9685 SETUP
// ======================================================

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo pulse range
#define SERVOMIN 110
#define SERVOMAX 490

// ======================================================
// SERVO FUNCTION
// ======================================================

void moveServo(int id, int angle) {

  if (id < 0 || id > 15) {
    Serial.println("Invalid channel");
    return;
  }

  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);

  pwm.setPWM(id, 0, pulse);

  Serial.print("Servo ");
  Serial.print(id);
  Serial.print(" -> ");
  Serial.println(angle);
}

// ======================================================
// SETUP
// ======================================================

void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println("-----------------------------------");
  Serial.println("   PCA9685 Motor Tester Interface  ");
  Serial.println("-----------------------------------");
  Serial.println("Commands:");
  Serial.println("id,angle   -> example: 0,90");
  Serial.println("all,angle  -> example: all,90");
  Serial.println("-----------------------------------");

  Wire.begin();
  pwm.begin();

  pwm.setPWMFreq(50); // servo frequency

  delay(10);

  Serial.println("PCA9685 Ready.");

  // Center all motors on startup
  Serial.println("Centering motors (M0-M7) to 90°");

  for (int i = 0; i < 8; i++) {
    moveServo(i, 90);
  }

  Serial.println("Ready for commands.");
}

// ======================================================
// MAIN LOOP
// ======================================================

void loop() {

  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');
    input.trim();

    int commaIndex = input.indexOf(',');

    if (commaIndex == -1) {
      Serial.println("Invalid command format");
      return;
    }

    String cmd = input.substring(0, commaIndex);
    int angle = input.substring(commaIndex + 1).toInt();

    angle = constrain(angle, 0, 180);

    if (cmd == "all") {

      for (int i = 0; i < 8; i++) {
        moveServo(i, angle);
      }

    } else {

      int id = cmd.toInt();
      moveServo(id, angle);

    }
  }
}