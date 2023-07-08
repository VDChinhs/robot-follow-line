const int motorRspeed  = 10;  // kết nối chân ENA với chân 5 arduino
const int R1      = 9;  // kết nối chân IN1 với chân 3 arduino
const int R2      = 8;  // kết nối chân IN2 với chân 4 arduino
const int L1      = 7; // kết nối chân IN3 với chân 7 arduino
const int L2      = 6; // kết nối chân IN4 với chân 8 arduino
const int motorLspeed  = 5;  // kết nối chân ENB với chân 6 arduino


const int R_s = A0;
const int L_s = A1;

int tocdo = 140;
int dogiat = 90;
int error = 0;


const int threshold = 200;

enum State {
  LINE_DETECTED,
  LINE_NOT_DETECTED
};

volatile State currentState = LINE_NOT_DETECTED;

void setup() {
  // put your setup code here, to run once:

  pinMode(R_s, INPUT);
  pinMode(L_s, INPUT);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(motorRspeed, OUTPUT);
  pinMode(motorLspeed, OUTPUT);

  Serial.begin(9600);

  analogWrite(motorRspeed, tocdo); 
  analogWrite(motorLspeed, tocdo);

  attachInterrupt(digitalPinToInterrupt(R_s), handleInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(L_s), handleInterrupt, CHANGE);

}

void loop() {

  // int RS = analogRead(R_s);
  // int LS = analogRead(L_s);
  // Serial.print(RS);
  // Serial.print("  |  ");
  // Serial.println(LS);
  
  switch (currentState) {
      case LINE_DETECTED:
        // Đi qua line
        setMotorSpeed(255);  // Điều chỉnh tốc độ động cơ
        break;

      case LINE_NOT_DETECTED:
        // Không đi qua line
        stopMotors();
        break;
    }
  }

  // Xử lý ngắt
  void handleInterrupt() {
    currentState = LINE_DETECTED;

  
  
  


  // if(RS > dogiat && LS < dogiat){
  //   // re phai
  //   analogWrite(motorRspeed, 160);
  //   digitalWrite(R1, LOW); 
  //   digitalWrite(R2, HIGH);
  //   // Serial.println("re phai");

  // }
  // if(LS > dogiat && RS < dogiat){
  //   // re trai
  //   analogWrite(motorLspeed, 160);
  //   digitalWrite(L1, LOW); 
  //   digitalWrite(L2, HIGH);
  //   // Serial.println("re trai");

  // }
  // if((RS > dogiat && LS > dogiat) || (RS < dogiat && LS < dogiat)){
  //   // Serial.println("di");
  //   analogWrite(motorRspeed, tocdo); 
  //   analogWrite(motorLspeed, tocdo);
  //   digitalWrite(R1, HIGH); 
  //   digitalWrite(R2, LOW);
  //   digitalWrite(L1, HIGH);
  //   digitalWrite(L2, LOW);
  // }
}

void dichuyen(int L, int R){
    analogWrite(motorRspeed, R); 
    analogWrite(motorLspeed, L);
    digitalWrite(R1, HIGH); 
    digitalWrite(R2, LOW);
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
}
void stop(){
    analogWrite(motorRspeed, 0); 
    analogWrite(motorLspeed, 0);
    digitalWrite(R1, LOW); 
    digitalWrite(R2, LOW);
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
}
void Rnguoc(){
    digitalWrite(R1, LOW); 
    digitalWrite(R2, HIGH);
}
void Lnguoc(){
    digitalWrite(L1, LOW); 
    digitalWrite(L2, HIGH);
}

void setMotorSpeed(int speed) {
  analogWrite(motorRspeed, speed);
  analogWrite(motorLspeed, speed);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}

// Dừng động cơ
void stopMotors() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
}
