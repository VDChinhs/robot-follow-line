// Khai báo chân kết nối cảm biến đường line
const int Rs2 = A0;
const int Rs1 = A1;
const int Ls1 = A2;
const int Ls2 = A3;
const int sensor5Pin = A5;

// Khai báo chân kết nối module motorLspeed98N
const int motorLspeed = 10;   // Chân PWM động cơ trái
const int L1 = 8;   // Chân điều khiển động cơ trái tiến
const int L2 = 9;   // Chân điều khiển động cơ trái lùi
const int motorRspeed = 5;  // Chân PWM động cơ phải
const int R1 = 6;   // Chân điều khiển động cơ phải tiến
const int R2 = 7;   // Chân điều khiển động cơ phải lùi

// Khai báo các hằng số PID
const float Kp = 0.2;  // Hệ số lỗi tỷ lệ
const float Ki = 0.1;  // Hệ số lỗi tích phân
const float Kd = 0.1;  // Hệ số lỗi vi phân

// Khai báo biến PID
float error = 0;
float lastError = 0;
float totalError = 0;
float pidValue = 0;

void setup() {
  // Cấu hình chân động cơ và PWM
  pinMode(motorLspeed, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(motorRspeed, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  
  // Cấu hình chân cảm biến đường line là đầu vào
  pinMode(Rs2, INPUT);
  pinMode(Rs1, INPUT);
  pinMode(Ls1, INPUT);
  pinMode(Ls2, INPUT);
  pinMode(sensor5Pin, INPUT);
  
  // Cấu hình tần số PWM cho động cơ
  analogWrite(motorLspeed, 120);
  analogWrite(motorRspeed, 120);
  Serial.begin(9600);
}

void loop() {
  // Đọc giá trị từ cảm biến đường line
  int sensor1Value = analogRead(Rs2);
  int sensor2Value = analogRead(Rs1);
  int sensor3Value = analogRead(Ls1);
  int sensor4Value = analogRead(Ls2);
   
  // Serial.println("sadsadsad");
   Serial.print(sensor4Value);
   Serial.print("  |  ");
   Serial.print(sensor3Value);
   Serial.print("  |  ");
   Serial.print(sensor2Value);
    Serial.print("  |  ");
    Serial.print(sensor1Value);
    Serial.print("  |  ");
    Serial.println();



  Tính toán giá trị lỗi PID
  error = (sensor1Value * 0.1 + sensor2Value * 0.3 + sensor3Value * 0.5 - sensor4Value * 0.5 - sensor5Value * 0.3 - sensor5Value * 0.1) / 5.0;
  totalError += error;

  // Áp dụng điều khiển PID
  pidValue = Kp * error + Ki * totalError + Kd * (error - lastError);

  // Lưu giá trị lỗi cho lần lặp tiếp theo
  lastError = error;

  // Điều khiển động cơ dựa trên giá trị PID
  int leftMotorSpeed = 100 - pidValue;
  int rightMotorSpeed = 100 + pidValue;

  // Giới hạn giá trị tốc độ động cơ
  if (leftMotorSpeed < 0) {
    leftMotorSpeed = 0;
  } else if (leftMotorSpeed > 255) {
    leftMotorSpeed = 255;
  }
  if (rightMotorSpeed < 0) {
    rightMotorSpeed = 0;
  } else if (rightMotorSpeed > 255) {
    rightMotorSpeed = 255;
  }

  // Điều khiển động cơ bằng module motorLspeed98N
  analogWrite(motorLspeed, leftMotorSpeed);
  analogWrite(motorRspeed, rightMotorSpeed);

  // Điều khiển hướng di chuyển của động cơ
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}
