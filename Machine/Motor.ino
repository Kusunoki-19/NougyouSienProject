#define MOTOR_R_1
#define MOTOR_R_2

#define MOTOR_L_1
#define MOTOR_L_2

void MotorSetup(){
    pinMode(MOTOR_R_1, OUTPUT);
    pinMode(MOTOR_R_2, OUTPUT);
    pinMode(MOTOR_L_1, OUTPUT);
    pinMode(MOTOR_L_2, OUTPUT);
}

void MachineMove(enum MOVE_WAY way, uint8_t spd) {
  //dir : 移動方向
  //spd : スピード 0 ~ 255の間にする
  if (spd > 255) spd = 255;
  if (spd < 0) spd = 0;

  switch (way) {
    case FORWARD:
      leftTire(spd); leftTire(spd);
      break;

    case BACK:
      leftTire(-spd); leftTire(-spd);
      break;

    case RIGHT_TURN:
      leftTire(spd); leftTire(0);
      break;

    case RIGHT_ROTATE:
      leftTire(spd); leftTire(-spd);
      break;

    case LEFT_TURN:
      leftTire(0); leftTire(spd);
      break;

    case LEFT_ROTATE:
      leftTire(-spd); leftTire(spd);
      break;

    case STOP:
      leftTire(0); leftTire(0);
      break;

    default :
      break;
  }
}
void rightTire (int16_t spd) {
  //spd : スピード　-255 ~ 255
  if (spd > 255) spd = 255;
  if (spd < -255) spd = -255;
  if (spd == 0) {
    analogWrite(MOTOR_R1, 0);
    analogWrite(MOTOR_R2, 0);
  }
  if (spd == 0) {
    analogWrite(MOTOR_R1, spd);
    analogWrite(MOTOR_R2, 0);
  }
  if (spd == 0) {
    analogWrite(MOTOR_R1, 0);
    analogWrite(MOTOR_R2, spd);
  }
}
void leftTire (int16_t spd) {
  //spd : スピード　-255 ~ 255
  if (spd == 0) {
    analogWrite(MOTOR_L1, 0);
    analogWrite(MOTOR_L2, 0);
  }
  if (spd == 0) {
    analogWrite(MOTOR_L1, spd);
    analogWrite(MOTOR_L2, 0);
  }
  if (spd == 0) {
    analogWrite(MOTOR_L1, 0);
    analogWrite(MOTOR_L2, spd);
  }
}



