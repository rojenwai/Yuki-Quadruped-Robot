#pragma once
#include <Arduino.h>

enum ServoName : uint8_t {
  L2 = 0,
  L1 = 1,
  R2 = 2,
  R1 = 3,
  L4 = 4,
  L3 = 5,
  R4 = 6,
  R3 = 7
};

const String ServoNames[]={"L2","L1","R2","R1","L4","L3","R4","R3"};

inline int servoNameToIndex(const String& servo) {
  if (servo == "L1") return L1;
  if (servo == "L2") return L2;
  if (servo == "L3") return L3;
  if (servo == "L4") return L4;
  if (servo == "R1") return R1;
  if (servo == "R2") return R2;
  if (servo == "R3") return R3;
  if (servo == "R4") return R4;
  return -1;
}

// Face enum kept so original code compiles

// External globals
extern int frameDelay;
extern int walkCycles;

extern void setServoAngle(uint8_t channel, int angle);
extern bool pressingCheck(String cmd, int ms);


// -------- DISPLAY SYSTEM DISABLED --------



// Pose/animation prototypes
void runRestPose();
void runStandPose();
void runWavePose();
void runDancePose();
void runSwimPose();
void runPointPose();
void runPushupPose();
void runBowPose();
void runCutePose();
void runFreakyPose();
void runWormPose();
void runShakePose();
void runShrugPose();
void runDeadPose();
void runCrabPose();
void runWalkPose();
void runWalkBackward();
void runTurnLeft();
void runTurnRight();

// ====== POSES ======
inline void runRestPose() { 
  Serial.println(F("REST")); 
  for (int i = 0; i < 8; i++) setServoAngle(i, 90); 
}

inline void runStandPose() { 
  Serial.println(F("STAND")); 
  setServoAngle(R1, 135); 
  setServoAngle(R2, 45); 
  setServoAngle(L1, 45); 
  setServoAngle(L2, 135); 
  setServoAngle(R4, 0); 
  setServoAngle(R3, 180); 
  setServoAngle(L3, 0); 
  setServoAngle(L4, 180); 
}

inline void runWavePose() { 
  Serial.println(F("WAVE")); 
  runStandPose(0); 
  delay(200);
  setServoAngle(R4, 80); setServoAngle(L3, 180); 
  setServoAngle(L2, 60); setServoAngle(R1, 100); 
  delay(200);
  setServoAngle(L3, 180); 
  delay(300); 
  for (int i = 0; i < 4; i++) { 
    setServoAngle(L3, 180); delay(300); 
    setServoAngle(L3, 100); delay(300); 
  } 
  runStandPose(1); 
  if (currentCommand == "wave") currentCommand = "";
}

inline void runDancePose() { 
  Serial.println(F("DANCE")); 
  setServoAngle(R1, 90); setServoAngle(R2, 90); 
  setServoAngle(L1, 90); setServoAngle(L2, 90); 
  setServoAngle(R4, 160); setServoAngle(R3, 160); 
  setServoAngle(L3, 10); setServoAngle(L4, 10); 
  delay(300); 
  for (int i = 0; i < 5; i++) { 
    setServoAngle(R4, 115); setServoAngle(R3, 115); 
    setServoAngle(L3, 10); setServoAngle(L4, 10); 
    delay(300); 
    setServoAngle(R4, 160); setServoAngle(R3, 160); 
    setServoAngle(L3, 65); setServoAngle(L4, 65); 
    delay(300); 
  } 
  runStandPose(1); 
  if (currentCommand == "dance") currentCommand = "";
}

inline void runSwimPose() { 
  Serial.println(F("SWIM")); 
  for (int i = 0; i < 8; i++) setServoAngle(i, 90); 
  for (int i = 0; i < 4; i++) { 
    setServoAngle(R1, 135); setServoAngle(R2, 45); 
    setServoAngle(L1, 45); setServoAngle(L2, 135); 
    delay(400); 
    setServoAngle(R1, 90); setServoAngle(R2, 90); 
    setServoAngle(L1, 90); setServoAngle(L2, 90); 
    delay(400); 
  } 
  runStandPose(1); 
  if (currentCommand == "swim") currentCommand = "";
}

inline void runPointPose() { 
  Serial.println(F("POINT")); 
  setServoAngle(L2, 60); setServoAngle(R1, 135); 
  setServoAngle(R2, 100); setServoAngle(L4, 180); 
  setServoAngle(L1, 25); setServoAngle(L3, 145);
  setServoAngle(R4, 80); setServoAngle(R3, 170); 
  delay(2000); 
  runStandPose(1); 
  if (currentCommand == "point") currentCommand = "";
}

inline void runPushupPose() {
  Serial.println(F("PUSHUP"));
  runStandPose(0); 
  delay(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 90);
  setServoAngle(R3, 90);
  delay(500);
  for (int i = 0; i < 4; i++) {
    setServoAngle(L3, 0);
    setServoAngle(R3, 180);
    delay(600);
    setServoAngle(L3, 90);
    setServoAngle(R3, 90);
    delay(500);
  }
  runStandPose(1);
  if (currentCommand == "pushup") currentCommand = "";
}

inline void runBowPose() {
  Serial.println(F("BOW"));
  runStandPose(0); 
  delay(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 0);
  setServoAngle(R3, 180);
  setServoAngle(L2, 180);
  setServoAngle(R2, 0);
  setServoAngle(R4, 0);
  setServoAngle(L4, 180);
  delay(600);
  setServoAngle(L3, 90);
  setServoAngle(R3, 90);
  delay(3000);
  runStandPose(1);
  if (currentCommand == "bow") currentCommand = "";
}

inline void runCutePose() {
  Serial.println(F("CUTE"));
  runStandPose(0); 
  delay(200);
  setServoAngle(L2, 160);
  setServoAngle(R2, 20);
  setServoAngle(R4, 180);
  setServoAngle(L4, 0);

  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 180);
  setServoAngle(R3, 0);
  delay(200);
  for (int i = 0; i < 5; i++) {
    setServoAngle(R4, 180);
    setServoAngle(L4, 45);
    delay(300);
    setServoAngle(R4, 135);
    setServoAngle(L4, 0);
    delay(300);
  }
  runStandPose(1);
  if (currentCommand == "cute") currentCommand = "";
}

inline void runFreakyPose() {
  Serial.println(F("FREAKY"));
  runStandPose(0); 
  delay(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L2, 180);
  setServoAngle(R2, 0);
  setServoAngle(R4, 90);
  setServoAngle(R3, 0);
  delay(200);
  for (int i = 0; i < 3; i++) {
    setServoAngle(R3, 25);
    delay(400);
    setServoAngle(R3, 0);
    delay(400);
  }
  runStandPose(1);
  if (currentCommand == "freaky") currentCommand = "";
}

inline void runWormPose() {
  Serial.println(F("WORM"));
  runStandPose(0);
  delay(200);
  setServoAngle(R1, 180); setServoAngle(R2, 0); setServoAngle(L1, 0); setServoAngle(L2, 180);
  setServoAngle(R4, 90); setServoAngle(R3, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  delay(200);
  for(int i=0; i<5; i++) {
    setServoAngle(R3, 45); setServoAngle(L3, 135); setServoAngle(R4, 45); setServoAngle(L4, 135);
    delay(300);
    setServoAngle(R3, 135); setServoAngle(L3, 45); setServoAngle(R4, 135); setServoAngle(L4, 45);
    delay(300);
  }
  runStandPose(1);
  if (currentCommand == "worm") currentCommand = "";
}

inline void runShakePose() {
  Serial.println(F("SHAKE"));
  runStandPose(0);
  delay(200);
  setServoAngle(R1, 135); setServoAngle(L1, 45); setServoAngle(L3, 90); setServoAngle(R3, 90);
  setServoAngle(L2, 90); setServoAngle(R2, 90);
  delay(200);
  for(int i=0; i<5; i++) {
    setServoAngle(R4, 45); setServoAngle(L4, 135);
    delay(300);
    setServoAngle(R4, 0); setServoAngle(L4, 180);
    delay(300);
  }
  runStandPose(1);
  if (currentCommand == "shake") currentCommand = "";
}

inline void runShrugPose() {
  Serial.println(F("SHRUG"));
  runStandPose(0);
  delay(200);
  setServoAngle(R3, 90); setServoAngle(R4, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  delay(1000);
  setServoAngle(R3, 0); setServoAngle(R4, 180); setServoAngle(L3, 180); setServoAngle(L4, 0);
  delay(1500);
  runStandPose(1);
  if (currentCommand == "shrug") currentCommand = "";
}

inline void runDeadPose() {
  Serial.println(F("DEAD"));
  runStandPose(0);
  delay(200);
  setServoAngle(R3, 90); setServoAngle(R4, 90); setServoAngle(L3, 90); setServoAngle(L4, 90);
  if (currentCommand == "dead") currentCommand = "";
}

inline void runCrabPose() {
  Serial.println(F("CRAB"));
  runStandPose(0);
  delay(200);
  setServoAngle(R1, 90); setServoAngle(R2, 90); setServoAngle(L1, 90); setServoAngle(L2, 90);
  setServoAngle(R4, 0); setServoAngle(R3, 180); setServoAngle(L3, 45); setServoAngle(L4, 135);
  for(int i=0; i<5; i++) {
    setServoAngle(R4, 45); setServoAngle(R3, 135); setServoAngle(L3, 0); setServoAngle(L4, 180);
    delay(300);
    setServoAngle(R4, 0); setServoAngle(R3, 180); setServoAngle(L3, 45); setServoAngle(L4, 135);
    delay(300);
  }
  runStandPose(1);
  if (currentCommand == "crab") currentCommand = "";
}

// --- MOVEMENT ANIMATIONS ---
inline void runWalkPose() {
  Serial.println(F("WALK FWD"));
  // Initial Step
  setServoAngle(R3, 135); setServoAngle(L3, 45);
  setServoAngle(R2, 100); setServoAngle(L1, 25);
  if (!pressingCheck("forward", frameDelay)) return;
  
  for (int i = 0; i < walkCycles; i++) {
    setServoAngle(R3, 135); setServoAngle(L3, 0);
    if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(L4, 135); setServoAngle(L2, 90);
    setServoAngle(R4, 0); setServoAngle(R1, 180);
    if (!pressingCheck("forward", frameDelay)) return;    
    setServoAngle(R2, 45); setServoAngle(L1, 90);
    if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(R4, 45); setServoAngle(L4, 180);
    if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L3, 45);
    setServoAngle(R2, 90); setServoAngle(L1, 0);
    if (!pressingCheck("forward", frameDelay)) return;  
    setServoAngle(L2, 135); setServoAngle(R1, 90);
    if (!pressingCheck("forward", frameDelay)) return;
  }
  runStandPose(1);
}

// Logic reversed from Walk
inline void runWalkBackward() {
  Serial.println(F("WALK BACK"));
  if (!pressingCheck("backward", frameDelay)) return;
  
  for (int i = 0; i < walkCycles; i++) {
    setServoAngle(R3, 135); setServoAngle(L3, 0);
    if (!pressingCheck("backward", frameDelay)) return;
    setServoAngle(L4, 135); setServoAngle(L2, 135);
    setServoAngle(R4, 0); setServoAngle(R1, 90);
    if (!pressingCheck("backward", frameDelay)) return;    
    setServoAngle(R2, 90); setServoAngle(L1, 0);
    if (!pressingCheck("backward", frameDelay)) return;
    setServoAngle(R4, 45); setServoAngle(L4, 180);
    if (!pressingCheck("backward", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L3, 45);
    setServoAngle(R2, 45); setServoAngle(L1, 90);
    if (!pressingCheck("backward", frameDelay)) return;  
    setServoAngle(L2, 90); setServoAngle(R1, 180);
    if (!pressingCheck("backward", frameDelay)) return;
  }
  runStandPose(1);
}

// Simple turn logic
inline void runTurnLeft() {
  Serial.println(F("TURN LEFT"));
  for (int i = 0; i < walkCycles; i++) {
    //legset 1 (R1 L2)
    setServoAngle(R3, 135); setServoAngle(L4, 135); 
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R1, 180); setServoAngle(L2, 180); 
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L4, 180); 
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R1, 135); setServoAngle(L2, 135);
    if (!pressingCheck("left", frameDelay)) return;
      //legset 2 (R2 L1)
    setServoAngle(R4, 45); setServoAngle(L3, 45); 
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R2, 90); setServoAngle(L1, 90); 
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R4, 0); setServoAngle(L3, 0); 
    if (!pressingCheck("left", frameDelay)) return;
    setServoAngle(R2, 45); setServoAngle(L1, 45);
    if (!pressingCheck("left", frameDelay)) return;  
  }
  runStandPose(1);
}

inline void runTurnRight() {
  Serial.println(F("TURN RIGHT"));
  for (int i = 0; i < walkCycles; i++) {
    //legset 2 (R2 L1)
    setServoAngle(R4, 45); setServoAngle(L3, 45); 
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R2, 0); setServoAngle(L1, 0); 
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R4, 0); setServoAngle(L3, 0); 
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R2, 45); setServoAngle(L1, 45);
    if (!pressingCheck("right", frameDelay)) return;  
    //legset 1 (R1 L2)
    setServoAngle(R3, 135); setServoAngle(L4, 135); 
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R1, 90); setServoAngle(L2, 90); 
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L4, 180); 
    if (!pressingCheck("right", frameDelay)) return;
    setServoAngle(R1, 135); setServoAngle(L2, 135);
    if (!pressingCheck("right", frameDelay)) return;
  }
  runStandPose(1);
}
