#include <Wire.h>
#include <math.h>

typedef struct POS {
  float x,
  float y
};

POS INIT_POS = {0, 0};
POS MARK_POS = {0, 0};
POS NOW_POS  = {0, 0};

enum MACHINE_STATE {
  NONACTIVE,
  ACTIVE,
  GO_TO_MARK_POS,
  GO_TO_INIT_POS
} machine_state;

enum MOVE_WAY {
  FORWARD,
  BACK,
  RIGHT_TURN,
  RIGHT_ROTATE,
  LEFT_TURN,
  LEFT_ROTATE,
  STOP
};

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  
  EncoderSetup();
  MotorSetup();
  MPU6050Setup();
}

void loop() {
  MPU6050GetDigital();
  DAConvert();
  calcANGL();
  switch (machine_state) {
    case NONACTIVE:
      break;
    case ACTIVE:
      break;
    case GO_TO_MARK_POS:
      break;
    case GO_TO_INIT_POS:
      break;
    default:
      break;
  }
  //printACC();
  //printNoDriftGYRO();
  printANGL();

  Serial.print("\n");
  delay(100);
}
