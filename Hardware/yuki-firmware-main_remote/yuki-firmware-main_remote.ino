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

int walkCycles = 1;

bool pressingCheck(String cmd, int ms){
  delay(ms);
  return currentCommand == cmd;
}

// Servo pulse limits
#define SERVO_MIN 110
#define SERVO_MAX 490

void setServoAngle(uint8_t channel,int angle){

  if(channel < 16){

    angle = constrain(angle,0,180);

    // invert mirrored servos
    // if(channel == 4 || channel == 5 ){   // M5 M6
    //   angle = 180 - angle;
    // }

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

void setup(){

  Serial.begin(115200);

  WiFi.mode(WIFI_AP);

  WiFi.softAP(AP_SSID,AP_PASS);

  IPAddress ip = WiFi.softAPIP();

  Serial.print("AP IP: ");
  Serial.println(ip);

  dnsServer.start(DNS_PORT,"*",ip);

  server.on("/",handleRoot);

  server.on("/cmd",handleCommandWeb);

  server.onNotFound(handleRoot);

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