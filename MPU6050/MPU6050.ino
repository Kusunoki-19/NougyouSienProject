#include <Wire.h>
#include <math.h>

#define MPU_6050_ADDR 0x68 //MPU6050, MPU6000, MPU9250で変わらないはず

uint8_t DIGITAL_8BIT[14] = {0};
int16_t DIGITAL_16BIT[7] = {0};

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

void setRegister(uint8_t slaveAddr, uint8_t registAddr, uint8_t registValue) {
  Wire.beginTransmission(slaveAddr);
  Wire.write(registAddr);
  Wire.write(registValue);
  Wire.endTransmission();
}
void getDigital() {
  int requestDataLen = 14;
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  //データリクエスト
  Wire.requestFrom(0x68, requestDataLen);
  int i = 0;

  //デジタル値の取得
  while (Wire.available()) {
    DIGITAL_8BIT[i++] = Wire.read();
  }

  //デジタル値8bitの連結
  for (i = 0; i < (requestDataLen / 2); i++) {
    DIGITAL_16BIT[i] = (int16_t)(DIGITAL_8BIT[i * 2] << 8  | DIGITAL_8BIT[i * 2 + 1]);
  }
}

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

void calcANGL() {
  uint8_t static timeNow = 0;
  uint8_t static timePre = 0;
  double static timeDelta = 0;// 前回と今の時間の差[s]。積分で使う

  timeNow = micros();

  //回転速度 * 微小時間[s] で積分
  ANGL.x += GYRO.x * timeDelta;
  ANGL.y += GYRO.y * timeDelta;
  ANGL.z += GYRO.z * timeDelta;

  timePre = timeNow;

  timeDelta = (timeNow - timePre) / pow(10, 6);
}

void printlnACC() {
  Serial.print(" ACC[g]:  ");
  Serial.print(ACC.x);    Serial.print("\t");
  Serial.print(ACC.y);    Serial.print("\t");
  Serial.print(ACC.z);    Serial.print("\t");
}
void printlnGYRO () {
  Serial.print("GYRO[deg/s]:  ");
  Serial.print(GYRO.x);    Serial.print("\t");
  Serial.print(GYRO.y);    Serial.print("\t");
  Serial.print(GYRO.z);    Serial.print("\t");
}
void printlnANGL () {
  Serial.print("GYRO[deg/s]:  ");
  Serial.print(GYRO.x);    Serial.print("\t");
  Serial.print(GYRO.y);    Serial.print("\t");
  Serial.print(GYRO.z);    Serial.print("\t");
}
void setup() {
  Serial.begin(115200);
  Serial.println("Start");

  //0x1B : 速度のフルスケール設定があるレジスタ
  //0b00000000 : 4,3bitを01に指定することで250degree/secまで測れる
  setRegister(MPU_6050_ADDR, 0x1B , 0b00000000);

  //0x1C : 加速度のスケールレンジ設定があるレジスタ
  //0b00000000 : 4,3bitを00に指定することで+-2gまで測れる。gが重力加速度
  setRegister(MPU_6050_ADDR, 0x1C , 0b00000000);

  //0x6B : クロック設定があるレジスタ
  //0b00000000 : 2,1,0bitを000に指定することで、20MHz振動に設定
  setRegister(MPU_6050_ADDR, 0x6B , 0b00000000);

  delay(1000);
}

void loop() {
  getDigital();
  DAConvert();
  calcANGL();

  //printlnACC();
  //printlnGYRO();
  printlnANGL();
  Serial.print("\n");
  delay(100);
}
