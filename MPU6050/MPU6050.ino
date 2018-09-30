#include <Wire.h>
#include <math.h>
#define MPU_6050_ADDR 0x68 //MPU6050, MPU6000, MPU9250で変わらないはず
uint8_t DIGITAL_8BIT[14] = {0};
int16_t DIGITAL_16BIT[7] = {0};

void getDigital() {
  int requestDataLen = 14;
  Wire.beginTransmission(MPU_6050_ADDR);
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

  calcGyroDrift();
}

void loop() {
  getDigital();
  DAConvert();
  calcANGL();

  //printACC();
  printNoDriftGYRO();
  printANGL();
  Serial.print("\n");
  delay(100);
}
