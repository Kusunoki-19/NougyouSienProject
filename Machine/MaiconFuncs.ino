void setRegister(uint8_t slaveAddr, uint8_t registAddr, uint8_t registValue) {
  Wire.beginTransmission(slaveAddr);
  Wire.write(registAddr);
  Wire.write(registValue);
  Wire.endTransmission();
}


