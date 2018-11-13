#define ENCODER 2
//attach interrupt pin is pin2(int.0) or pin3(int.1)

int encoderCount = 0;

void setup() {
  pinMode(ENCODER, INPUT_PULLUP);
  Serial.begin(115200);
  attachInterrupt(0, CountEncoderPalse, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(encoderCount);
  delay(100);
}

void CountEncoderPalse() {
  static int timePre = 0;
  static int timeNow = 0;
  static const int TIME_COUNT_LIMIT = 10000;

  timeNow = millis() % TIME_COUNT_LIMIT;
  
  if (abs(timeNow - timePre) >= 100) {
    //ノイズで短期間に割り込みが多発することがある
    //その場合は、カウントしないようにする
    encoderCount++;
  }
  
  timePre = timeNow;
  return 0;
}

