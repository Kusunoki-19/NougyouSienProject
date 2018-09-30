typedef struct Vector3 {
  float x;
  float y;
  float z;
};

Vector3 ACC = {
  0, //x
  0, //y
  0  //z
};
Vector3 GYRO = {
  0, //x
  0, //y
  0  //z
};
Vector3 ANGL = {
  0, //x
  0, //y
  0  //z
};
Vector3 GYRO_DRIFT = {
  0, //x
  0, //y
  0  //z
};
void DAConvert() {
  //単位はメートル毎秒毎秒[m/s^2]
  ACC.x = ((float)DIGITAL_16BIT[0] / 16384) * 9.81; //x加速度
  ACC.y = ((float)DIGITAL_16BIT[1] / 16384) * 9.81; //y加速度
  ACC.z = ((float)DIGITAL_16BIT[2] / 16384) * 9.81; //z加速度
  //単位はdegree毎秒[degree/s]
  GYRO.x = (float)DIGITAL_16BIT[4] / 131.072; //x角速度
  GYRO.y = (float)DIGITAL_16BIT[5] / 131.072; //y角速度
  GYRO.z = (float)DIGITAL_16BIT[6] / 131.072; //z角速度
}
void calcGyroDrift () {
  Serial.print("correcting GYRO Drifting");
  int i = 0;
  int correctCount = 100;
  for (i = 0; i < correctCount; i++) {
    getDigital();
    DAConvert();
    GYRO_DRIFT.x += GYRO.x;
    GYRO_DRIFT.y += GYRO.y;
    GYRO_DRIFT.z += GYRO.z;
    Serial.print(".");
    delay(10);
  }
  Serial.print("\n");
  GYRO_DRIFT.x /= correctCount;
  GYRO_DRIFT.y /= correctCount;
  GYRO_DRIFT.z /= correctCount;
  printGYRO_DRIFT();
  Serial.print("\n");
}

void calcANGL() {
  unsigned long static timeNow = 0;
  unsigned long static timePre = 0;
  double static timeDelta = 0;// 前回と今の時間の差[s]。積分で使う

  timeNow = micros();
  timeDelta = (timeNow - timePre) / pow(10, 6);
  //Serial.print("dt : "); Serial.print(timeDelta); Serial.print("\n");
  
  //回転速度 * 微小時間[s] で積分
  ANGL.x += (double)(GYRO.x - GYRO_DRIFT.x) * timeDelta;
  ANGL.y += (double)(GYRO.y - GYRO_DRIFT.y) * timeDelta;
  ANGL.z += (double)(GYRO.z - GYRO_DRIFT.z) * timeDelta;

  timePre = timeNow;

}

void printACC() {
  Serial.print(" ACC[g]:  ");
  Serial.print(ACC.x);    Serial.print("\t");
  Serial.print(ACC.y);    Serial.print("\t");
  Serial.print(ACC.z);    Serial.print("\t");
}
void printGYRO () {
  Serial.print("GYRO[deg/s]:  ");
  Serial.print(GYRO.x);    Serial.print("\t");
  Serial.print(GYRO.y);    Serial.print("\t");
  Serial.print(GYRO.z);    Serial.print("\t");
}
void printANGL () {
  Serial.print("ANGL[deg/s]:  ");
  Serial.print(ANGL.x);    Serial.print("\t");
  Serial.print(ANGL.y);    Serial.print("\t");
  Serial.print(ANGL.z);    Serial.print("\t");
}
void printGYRO_DRIFT () {
  Serial.print("GYRO_DRIFT[deg/s]:  ");
  Serial.print(GYRO_DRIFT.x);    Serial.print("\t");
  Serial.print(GYRO_DRIFT.y);    Serial.print("\t");
  Serial.print(GYRO_DRIFT.z);    Serial.print("\t");
}
void printNoDriftGYRO() {
  Serial.print("GYRO_DRIFT[deg/s]:  ");
  Serial.print(GYRO.x - GYRO_DRIFT.x);    Serial.print("\t");
  Serial.print(GYRO.y - GYRO_DRIFT.y);    Serial.print("\t");
  Serial.print(GYRO.z - GYRO_DRIFT.z);    Serial.print("\t");
}
