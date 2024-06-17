#include <SoftPWM.h>
#include "SunFounder_AI_Camera.h"
#include "ultrasonic.h"
#include "string.h"
#include "motors.h"
/*
void setup() {
  Serial.begin(115200);
  Serial.println("--- Rover Script ---");

  SoftPWMBegin();

  motorsForward(10);

  delay(1000);

  motorsStop();
}

void loop() {

}*/

bool cam = false;

AiCamera aiCam = AiCamera("GalaxyRVR", "GalaxyRVR");

int leftMotor = 0;
int rightMotor = 0;

bool do360 = false;

void setup() {
  int m = millis();
  Serial.begin(115200);
  SoftPWMBegin();

  beginMotors();

  Serial.println("Starting Camera");
  aiCam.begin("Lutscher360", "12345678", WIFI_MODE_AP, "8765");
  aiCam.setOnReceived(onReceive);

  while (millis() - m < 500) {
    delay(1);
  }
}

void loop() {
  aiCam.loop();
  motorsSetMotors(leftMotor, rightMotor);
  if (do360) {
    motorsDo360(0, 100);
  }
}

void onReceive() {
  // TODO: Battery Voltage
  aiCam.sendDoc["BV"] = 1.0;

  // Fixme: IR is broken
  aiCam.sendDoc["N"] = 0;
  aiCam.sendDoc["P"] = 0;

  // Ultrasound distance
  float usDistance = int(usGetRead() * 100) / 100.0;
  aiCam.sendDoc["O"] = usDistance;

  Serial.println(aiCam.getButton(REGION_I));
  Serial.println(aiCam.getSwitch(REGION_E));
  Serial.println(aiCam.getSwitch(REGION_F));
  Serial.println(aiCam.getSwitch(REGION_M));

  if (aiCam.getSwitch(REGION_M) && !cam) {
    Serial.println("lamp on");
    aiCam.lamp_on(5);
    cam = true;
  } else if (!aiCam.getSwitch(REGION_M) && cam) {
    Serial.println("lamp off");
    aiCam.lamp_off();
    cam = false;
  }

  int temp = aiCam.getSlider(REGION_D);
  Serial.print("Servo: ");
  Serial.println(temp);

  int throttle_L = aiCam.getThrottle(REGION_K);
  int throttle_R = aiCam.getThrottle(REGION_Q);
  if (throttle_L != 0 || throttle_R != 0 || throttle_L != leftMotor || throttle_R != rightMotor) {
    leftMotor = throttle_L;
    rightMotor = throttle_R;
  }
  if (!aiCam.getSwitch(REGION_E) && do360) {
    motorsSetMotors(0,0);
  }
  do360 = aiCam.getSwitch(REGION_E);
}