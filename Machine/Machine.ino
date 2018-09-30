#include <Wire.h>
#include <math.h>
#define MPU_6050_ADDR 0x68

enum MACHINE_STATE {
  NONACTIVE,
  ACTIVE,
  FORWARDING,
  TURNING,
  TURNING_RIGHT,
  TURNING_LEFT,
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
    case FORWARDING:
      break;
    case TURNING:
      break;
    case TURNING_RIGHT:
      break;
    case TURNING_LEFT:
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
