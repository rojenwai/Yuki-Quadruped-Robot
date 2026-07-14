/*
 * Yuki - AI Quadruped Robot
 * Copyright 2026 Rojen Wairokpam
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * ---------------------------------------------------------------------
 * NOTICE OF MODIFICATION (Apache-2.0, section 4(b))
 *
 * This file is a MODIFIED derivative of firmware/debugging-firmware/sesame-motor-tester.ino from the
 * Sesame Robot project by Dorian Todd (@dorianborian):
 *     https://github.com/dorianborian/sesame-robot
 * Original work Copyright Dorian Todd, licensed under Apache-2.0.
 *
 * Modifications by Rojen Wairokpam:
 *   - Drives servos through a PCA9685 (Adafruit_PWMServoDriver) instead of
 *     ESP32Servo direct-GPIO control, so the pin map and pulse-width
 *     constants are replaced by PCA9685 channel + pulse mapping.
 *   - Dropped the "stop" / detach command (the PCA9685 holds position).
 *   - Motors are centred to 90 degrees on startup.
 * ---------------------------------------------------------------------
 */

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