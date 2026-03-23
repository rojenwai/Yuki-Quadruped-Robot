#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <Adafruit_PWMServoDriver.h>

#include "captive-portal.h"
#include "movement-sequences.h"

#define AP_SSID "Yuki's-Controller"
#define AP_PASS "12345678"

WebServer server(80);
DNSServer dnsServer;
const byte DNS_PORT = 53;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

String currentCommand="";

int frameDelay=100;
int motorCurrentDelay=20;

int servoHome[8] = {99, 90, 90, 90, 90, 90, 90, 90};

int walkCycles = 1;

bool pressingCheck(String cmd, int ms){
  delay(ms);
  return currentCommand == cmd;
}

// Servo pulse limits
#define SERVO_MIN 110
#define SERVO_MAX 490

void setServoAngle(uint8_t channel,int angle){
  if(channel < 8){
    angle = angle + (servoHome[channel] - 90);

    // invert mirrored servos
    // if(channel == 4 || channel == 5 ){   // M5 M6
    // angle = 180 - angle;
    // }
    angle = constrain(angle,0,180);
    
    int pulse = map(angle,0,180,SERVO_MIN,SERVO_MAX);

    pwm.setPWM(channel,0,pulse);

    delay(motorCurrentDelay);
  }

}

void handleRoot(){

  server.send(200,"text/html",index_html);

}

void handleCommandWeb(){

  if(server.hasArg("pose")){

    currentCommand = server.arg("pose");

    server.send(200,"text/plain","OK");

  }

  else if(server.hasArg("go")){

    currentCommand = server.arg("go");

    server.send(200,"text/plain","OK");

  }

  else if(server.hasArg("stop")){

    currentCommand="";

    server.send(200,"text/plain","OK");

  }

  else if(server.hasArg("motor") && server.hasArg("value")){

    int motor = server.arg("motor").toInt();

    int angle = server.arg("value").toInt();

    if(motor>=1 && motor<=8){

      setServoAngle(motor-1,angle);

      server.send(200,"text/plain","OK");

    }

  }

  else{

    server.send(400,"text/plain","Bad Args");

  }

}

void handleGetSettings() {
  String json = "{";
  json += "\"frameDelay\":" + String(frameDelay) + ",";
  json += "\"walkCycles\":" + String(walkCycles) + ",";
  json += "\"motorCurrentDelay\":" + String(motorCurrentDelay) + ",";
  json += "\"motorSpeed\":\"medium\"";
  json += "}";
  
  server.send(200, "application/json", json);
}

void handleSetSettings() {

  if (server.hasArg("frameDelay"))
    frameDelay = server.arg("frameDelay").toInt();

  if (server.hasArg("walkCycles"))
    walkCycles = server.arg("walkCycles").toInt();

  if (server.hasArg("motorCurrentDelay"))
    motorCurrentDelay = server.arg("motorCurrentDelay").toInt();

  server.send(200, "text/plain", "OK");
}

void setup(){

  Serial.begin(115200);


  // WiFi.mode(WIFI_AP);
  // WiFi.softAP(AP_SSID, AP_PASS);
  
  //start
  const char* ssid = "iPhone";
  const char* password = "abcdefgh";

  // Enable BOTH AP + STA
  WiFi.mode(WIFI_AP_STA);

  // Start Access Point (your robot WiFi)
  WiFi.softAP(AP_SSID, AP_PASS);

  // Connect to phone hotspot (internet)
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  // Show both IPs
  Serial.print("STA IP (internet): ");
  Serial.println(WiFi.localIP());

  Serial.print("AP IP (robot): ");
  Serial.println(WiFi.softAPIP());

  // Start captive portal DNS
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  
  //end
  
  server.on("/",handleRoot);
  server.on("/cmd",handleCommandWeb);
  server.onNotFound(handleRoot);
  server.on("/getSettings", handleGetSettings);
  server.on("/setSettings", handleSetSettings);

  server.begin();

  // I2C
  Wire.begin(21,22);

  // PCA9685 init
  pwm.begin();

  pwm.setPWMFreq(50);

  delay(10);

  // center all servos
  for(int i=0;i<8;i++){

    setServoAngle(i,90);

  }

}

void loop(){

  dnsServer.processNextRequest();

  server.handleClient();

  if(currentCommand=="forward"){

    runWalkPose();

  }

  else if(currentCommand=="backward"){

    runWalkBackward();

  }

  else if(currentCommand=="left"){

    runTurnLeft();

  }

  else if(currentCommand=="right"){

    runTurnRight();

  }

  else if(currentCommand=="rest"){

    runRestPose();

    currentCommand="";

  }

  else if(currentCommand=="stand"){

    runStandPose(1);

    currentCommand="";

  }

  else if(currentCommand=="wave"){

    runWavePose();

  }

  else if(currentCommand=="dance"){

    runDancePose();

  }

  else if(currentCommand=="swim"){

    runSwimPose();

  }

  else if(currentCommand=="point"){

    runPointPose();

  }

  else if(currentCommand=="pushup"){

    runPushupPose();

  }

  else if(currentCommand=="bow"){

    runBowPose();

  }

  else if(currentCommand=="cute"){

    runCutePose();

  }

  else if(currentCommand=="freaky"){

    runFreakyPose();

  }

  else if(currentCommand=="worm"){

    runWormPose();

  }

  else if(currentCommand=="shake"){

    runShakePose();

  }

  else if(currentCommand=="shrug"){

    runShrugPose();

  }

  else if(currentCommand=="dead"){

    runDeadPose();

  }

  else if(currentCommand=="crab"){

    runCrabPose();

  }

}