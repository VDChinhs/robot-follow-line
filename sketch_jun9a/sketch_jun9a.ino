#include <AFMotor.h>

// Khai báo đối tượng AF_DCMotor cho các động cơ
AF_DCMotor leftMotor(3);
AF_DCMotor rightMotor(2);

// Khai báo chân đầu vào cho các cảm biến
const int sensorPins[] = {A5, A4, A3, A2, A1};

// Khai báo các hằng số PID
float Kp = 0.04;
float Ki = 0.0006;
float Kd = 0.7;

// Khai báo biến lưu trữ giá trị cảm biến
int sensorValues[5];

// Khai báo biến PID
double lastError = 0;
double error = 0;
double I = 0;
double D = 0;


// Đặt tốc độ mặc định cho các động cơ
const int motorSpeed = 150;

void setup() {
  // Khởi động thư viện AFMotor
  Serial.begin(9600);

  // Đặt tốc độ mặc định cho các động cơ
  leftMotor.setSpeed(motorSpeed);
  rightMotor.setSpeed(motorSpeed);

  // Khai báo chân đầu vào cho các cảm biến
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void loop() {
  // Đọc giá trị từ các cảm biến
  for (int i = 0; i < 5; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
  }
  Serial.print(sensorValues[0]);
  Serial.print("    |    ");
  Serial.print(sensorValues[1]);
  Serial.print("    |    ");
  Serial.print(sensorValues[2]);
  Serial.print("    |    ");
  Serial.print(sensorValues[3]);
  Serial.print("    |    ");
  Serial.print(sensorValues[4]);
  
  

  // Tính toán giá trị error dựa trên giá trị đọc từ cảm biến
  double sobichia = (sensorValues[0] * 0 + sensorValues[1] * 10 + sensorValues[3] * 30 + sensorValues[4] * 40);
  Serial.print("    |    ");
  Serial.print(sobichia);
  error =  2 - ( sobichia/ (sensorValues[0] + sensorValues[1] + sensorValues[3] + sensorValues[4]));
  
  Serial.print("    |    ");
  Serial.print(error);
  // Tính toán các thành phần PID

  D = error - lastError;
  I = error + I;
  lastError = error;
  // float D = lastError - error;


  // Tính toán giá trị điều khiển PID
  float pidOutput = Kp * error + Ki * I + Kd * D;
  Serial.print("    |    ");
  Serial.print(pidOutput);
  
  
    
  // Điều chỉnh hướng di chuyển dựa trên giá trị điều khiển PID
  // Định nghĩa tolerance
  // float tolerance = 0.1;

  // if (abs(pidOutput) < tolerance) {
  //     // Điều khiển robot di chuyển thẳng
  //     leftMotor.run(FORWARD);
  //     rightMotor.run(FORWARD);
  // } 
  //  if (pidOutput > 0) {
  //     // Điều khiển robot di chuyển về phía trái
  //     Serial.print("re trai");
  //     leftMotor.run(BACKWARD);
  //     rightMotor.run(FORWARD);
  // } else {
  //     // Điều khiển robot di chuyển về phía phải
  //     Serial.print("re phai");
  //     leftMotor.run(FORWARD);
  //     rightMotor.run(BACKWARD);
  // }
  

  // Điều chỉnh tốc độ động cơ dựa trên giá trị tuyệt đối của điều khiển PID
  int motorSpeedAdjustment = abs(pidOutput);
  // leftMotor.setSpeed(motorSpeed - motorSpeedAdjustment);
  // rightMotor.setSpeed(motorSpeed + motorSpeedAdjustment);
  // pid > 0 re phai
  // pid < 0 re trai

  int motorA = motorSpeed + pidOutput * 1000 ;
  int motorB = motorSpeed - pidOutput * 1000;
  Serial.print("    |    ");
  Serial.print(motorSpeedAdjustment);
  Serial.print("    |    ");
  Serial.print(motorA);
  Serial.print("    |    ");
  Serial.print(motorB);
  Serial.println();

  if(motorA > 160){
    motorA = 160;
  }
  if(motorB > 160){
    motorB = 160;
  }
  if(motorA < -140){
    motorA = -140;
  }
  if(motorB < -140){
    motorB = -140;
  }
  forwardMovement(motorA,motorB);

  
}
// void fowark_movement(int speedA, int speedB){
//   if(speedA < 0){
//     speedA = 0 - speedA;
//     digitalWrite(4, HIGH);
//   }
//   else{
//     digitalWrite(4, LOW);
//   }
//   if(speedB < 0){
//     speedB = 0 - speedB;
//     digitalWrite(5, HIGH);
//   }
//   else{
//     digitalWrite(5, LOW);
//   }
//   analogWrite(1, speedA);
// }
void forwardMovement(int speedA, int speedB) {
  if (speedA < 0) {
    speedA = -speedA;
    leftMotor.setSpeed(speedA);
    leftMotor.run(BACKWARD);

  } else {
    leftMotor.setSpeed(speedA);
    leftMotor.run(FORWARD);
  }
  
  if (speedB < 0) {
    speedB = -speedB;
    rightMotor.setSpeed(speedB);
    rightMotor.run(BACKWARD);
  } else {
    rightMotor.setSpeed(speedB);
    rightMotor.run(FORWARD);
  }
}

