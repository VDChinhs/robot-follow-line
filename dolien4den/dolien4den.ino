const int motorRspeed = 5;  // kết nối chân ENA với chân 5 arduino
const int R1      = 6;  // kết nối chân IN1 với chân 3 arduino
const int R2      = 7;  // kết nối chân IN2 với chân 4 arduino
const int L1      = 8; // kết nối chân IN3 với chân 7 arduino
const int L2      = 9; // kết nối chân IN4 với chân 8 arduino
const int motorLspeed = 10;  // kết nối chân ENB với chân 6 arduino

const int Rs2 = A0;
const int Rs1 = A1;
const int Ls1 = A2;
const int Ls2 = A3;

int r2 = 0;
int r1 = 0;
int l1 = 0;
int l2 = 0;

int tocdo = 250;
int dogiat = 110;
int error = 0;

const unsigned long stopDuration = 500; 
unsigned long stopStartTime = 0;


const float wheelDiameter = 6.8; // Đường kính bánh xe (đơn vị: cm)
const float trackWidth = 13; // Khoảng cách giữa hai bánh xe (đơn vị: cm)


unsigned long time;
bool check = false;


void setup() {
  // put your setup code here, to run once:

  pinMode(Rs2, INPUT);
  pinMode(Rs1, INPUT);
  pinMode(Ls1, INPUT);
  pinMode(Ls2, INPUT);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(motorRspeed, OUTPUT);
  pinMode(motorLspeed, OUTPUT);

  analogWrite(motorRspeed, tocdo); 
  analogWrite(motorLspeed, tocdo);

  Serial.begin(9600);
  int time = millis();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  int r2 = analogRead(Rs2);
  int r1 = analogRead(Rs1);
  int l1 = analogRead(Ls1);
  int l2 = analogRead(Ls2);
  Serial.print(r2);
  Serial.print("  |  ");
  Serial.print(r1);
  Serial.print("  |  ");
  Serial.print(l1);
  Serial.print("  |  ");
  Serial.print(l2);

////////////////////////////////////////////////
    // digitalWrite(R1, HIGH); 
    // digitalWrite(R2, LOW);
    // digitalWrite(L1, HIGH);
    // digitalWrite(L2, LOW);


    // MILLIS
  int tocdokhiquay = 200;
  if(r2 > 100){
    
    analogWrite(motorRspeed, tocdokhiquay); 
    analogWrite(motorLspeed, tocdokhiquay);
  
    quayphai();

    // unsigned long startTime = millis();
    // unsigned long quayDelayTime = 170; 
    // while (millis() - startTime < quayDelayTime) {
    //   if(l1 > 100 || r1 > 100){
    //     quayDelayTime = 1;
    //     digitalWrite(L1, LOW);
    //     digitalWrite(L2, HIGH);
    //     digitalWrite(R1, HIGH);
    //     digitalWrite(R2, LOW);
    //     dithangtung();
    //   }
    //   digitalWrite(L1, HIGH);
    //   digitalWrite(L2, LOW);
    //   digitalWrite(R1, LOW);
    //   digitalWrite(R2, HIGH);
    // }

    // digitalWrite(R1, LOW);
    // digitalWrite(R2, LOW);delay(100);
    // analogWrite(motorRspeed, tocdokhiquay); 
    // analogWrite(motorLspeed, tocdokhiquay);
    // digitalWrite(R1, LOW);
    // digitalWrite(R2, HIGH); delay(150);
    // digitalWrite(R1, LOW);
    // digitalWrite(R2, LOW);
    // tocdoL225();delay(245); 
  }
  
  if(l2 > 100){
    analogWrite(motorRspeed, tocdokhiquay); 
    analogWrite(motorLspeed, tocdokhiquay);
  
    quaytrai();

    // unsigned long startTime = millis();
    // unsigned long quayDelayTime = 170;
    // while (millis() - startTime < quayDelayTime) {
    //   if(l1 > 100 || r1 > 100){
    //     quayDelayTime = 1;
    //     digitalWrite(L1, HIGH);
    //     digitalWrite(L2, LOW);
    //     digitalWrite(R1, LOW);
    //     digitalWrite(R2, HIGH);
    //     dithangtung();
    //   }
    //   digitalWrite(L1, LOW);
    //   digitalWrite(L2, HIGH);
    //   digitalWrite(R1, HIGH);
    //   digitalWrite(R2, LOW);
    // }


    // digitalWrite(L1, LOW);
    // digitalWrite(L2, LOW);delay(100);
    // analogWrite(motorRspeed, tocdokhiquay); 
    // analogWrite(motorLspeed, tocdokhiquay);
    // digitalWrite(L1, LOW);
    // digitalWrite(L2, HIGH); delay(120);
    // digitalWrite(L1, LOW);
    // digitalWrite(L2, LOW);
    // tocdoR225();delay(260);    
  }


  // Đi 2 LED NGOÀI
  // if(r2 > dogiat && l2 < dogiat){
  //   // re phai
  //   back();delay(150);
  //   stop();
  //   digitalWrite(R1, LOW); 
  //   digitalWrite(R2, HIGH);delay(45);
  //   dichuyen(250,0);delay(280);
  //   // stop();delay(100);
  //   Serial.println("re phai");
  // }

  // if(l2 > dogiat && r2 < dogiat){
  //   // re trai
  //   back();delay(150);
  //   stop();
  //   digitalWrite(L1, LOW);
  //   digitalWrite(L2, HIGH);delay(45);
  //   dichuyen(0,250);delay(280);
  //   // stop();delay(100);
  //   Serial.println("re trai");
  // }

  // if(r2 < 100 && l2 < 100){
  //   Serial.println("di");
  //   analogWrite(motorRspeed, tocdo); 
  //   analogWrite(motorLspeed, tocdo);
  //   digitalWrite(R1, HIGH); 
  //   digitalWrite(R2, LOW);
  //   digitalWrite(L1, HIGH);
  //   digitalWrite(L2, LOW);
  // }


  // Đi 2 LED TRONG 
  // if(r1 > dogiat && l1 < dogiat){
  //   // re phai
  //   // analogWrite(motorRspeed, 90);
  //   digitalWrite(R1, LOW); 
  //   digitalWrite(R2, HIGH);
  //   // Serial.println("re phai");

  // }
  // if(l1 > dogiat && r1 < dogiat){
  //   // re trai
  //   // analogWrite(motorLspeed, 90);
  //   digitalWrite(L1, LOW); 
  //   digitalWrite(L2, HIGH);
  //   // Serial.println("re trai");

  // }
  // if((r1 > dogiat && l1 > dogiat) || (r1 < dogiat && l1 < dogiat)){
  //   // Serial.println("di");
  //   analogWrite(motorRspeed, tocdo); 
  //   analogWrite(motorLspeed, tocdo);
  //   digitalWrite(R1, HIGH); 
  //   digitalWrite(R2, LOW);
  //   digitalWrite(L1, HIGH);
  //   digitalWrite(L2, LOW);
  // }


// ĐI THẲNG
  // dithangtung();
  if(r1 > dogiat && l1 < dogiat){
    // re phai
    // Serial.println("re phai");
    error = 160;
  }
  if(l1 > dogiat && r1 < dogiat){
    // re trai
    // Serial.println("re trai");
    error = -160;
  }
  if((r1 > dogiat && l1 > dogiat) || (r1 < dogiat && l1 < dogiat)) {
    error = 0;
  }
  int left = tocdo + error;
  int right =  tocdo - error;
  if(left > 250){
    left = 250;
  }
  if(left < 0){
    left = 0;
  }
  if(right > 250){
    right = 250;
  }
  if(right < 0){
    right = 0;
  }
  // dichuyen(left, right);
  analogWrite(motorRspeed, right); 
  analogWrite(motorLspeed, left);
  digitalWrite(R1, HIGH); 
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  Serial.println();

}
void dichuyen(int L, int R){
    analogWrite(motorRspeed, R); 
    analogWrite(motorLspeed, L);
    digitalWrite(R1, HIGH); 
    digitalWrite(R2, LOW);
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
}
void tocdoR225(){
    analogWrite(motorRspeed, 230); 
    digitalWrite(R1, HIGH); 
    digitalWrite(R2, LOW);
}
void tocdoL225(){
    analogWrite(motorLspeed, 230); 
    digitalWrite(L1, HIGH); 
    digitalWrite(L2, LOW);
}


void back(){
  analogWrite(motorRspeed, 255); 
  analogWrite(motorLspeed, 255);
  digitalWrite(R1, LOW); 
  digitalWrite(R2, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
}
void stop(){
  digitalWrite(R1, LOW); 
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
}

void quaytrai(){
  digitalWrite(L1, LOW); 
    digitalWrite(L2, HIGH);

  unsigned long startTime = millis();
    unsigned long quayDelayTime = 210;
    while (millis() - startTime < quayDelayTime) {
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      if(l1 > 100 || r1 > 100){
        quayDelayTime = 1;
        digitalWrite(L1, HIGH);
        digitalWrite(L2, LOW);
        digitalWrite(R1, LOW);
        digitalWrite(R2, HIGH);
        dithangtung();
      }
      if(r2 > 200){
        quayDelayTime = 1;
        quayphai();
      }
    }
}
void quayphai(){
    digitalWrite(R1, LOW); 
    digitalWrite(R2, HIGH);

  unsigned long startTime = millis();
    unsigned long quayDelayTime = 210; 
    while (millis() - startTime < quayDelayTime) {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      if(l1 > 100 || r1 > 100){
        quayDelayTime = 1;
        digitalWrite(L1, LOW);
        digitalWrite(L2, HIGH);
        digitalWrite(R1, HIGH);
        digitalWrite(R2, LOW);
        dithangtung();
      }
      if(l2 > 200){
        quayDelayTime = 1;
        quaytrai();
      }
    }
}

void dithangtung(){
  if(r1 > dogiat && l1 < dogiat){
    // re phai
    // Serial.println("re phai");
    error = 160;
  }
  if(l1 > dogiat && r1 < dogiat){
    // re trai
    // Serial.println("re trai");
    error = -160;
  }
  if((r1 > dogiat && l1 > dogiat) || (r1 < dogiat && l1 < dogiat)) {
    error = 0;
  }
  int left = tocdo + error;
  int right =  tocdo - error;
  if(left > 250){
    left = 250;
  }
  if(left < 0){
    left = 0;
  }
  if(right > 250){
    right = 250;
  }
  if(right < 0){
    right = 0;
  }
  // dichuyen(left, right);
  analogWrite(motorRspeed, right); 
  analogWrite(motorLspeed, left);
  digitalWrite(R1, HIGH); 
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}