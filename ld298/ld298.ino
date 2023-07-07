const int motorRspeed  = 5;  // kết nối chân ENA với chân 5 arduino
const int R1      = 6;  // kết nối chân IN1 với chân 3 arduino
const int R2      = 7;  // kết nối chân IN2 với chân 4 arduino
const int L1      = 8; // kết nối chân IN3 với chân 7 arduino
const int L2      = 9; // kết nối chân IN4 với chân 8 arduino
const int motorLspeed  = 10;  // kết nối chân ENB với chân 6 arduino


const int R_s = A0;
const int L_s = A1;

int tocdo = 115;
int dogiat = 100;
int error = 0;

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

}

void loop() {
  // int high1 = 1;
  // int low1  = 0;
  // int high2 = 1;
  // int low2  = 0;
  // put your main code here, to run repeatedly:
  // digitalWrite(R1, HIGH); 
  // digitalWrite(R2, LOW);
  // digitalWrite(L1, HIGH);
  // digitalWrite(L2, LOW);

  int RS = analogRead(R_s);
  int LS = analogRead(L_s);
  Serial.print(RS);
  Serial.print("  |  ");
  Serial.println(LS);
  // dichuyen(110,200);
 

  // if(RS > 300 && RS < 600 && LS < dogiat){
  //   // re phai
  //   Serial.println("re phai1");
  //   int high1 = 0;
  //   int low1  = 1;

  // }
  // if(LS > 200 && LS < 350 && RS < dogiat){
  //   // re trai
  //   Serial.println("re trai1");
  //   int high2 = 0;
  //   int low2  = 1;
  // }
  // if(RS > dogiat && RS < 300 && LS < dogiat){
  //   // re phai
  //   // Serial.println("re phai");
  //   int high1 = 1;
  //   int low1  = 0;
  //   int high2 = 1;
  //   int low2  = 0;
  //   error = 40;
  // }
  // if(LS > dogiat && LS < 200 && RS < dogiat){
  //   // re trai
  //   // Serial.println("re trai");
  //   int high1 = 1;
  //   int low1  = 0;
  //   int high2 = 1;
  //   int low2  = 0;
  //   error = -40;
  // }
  
  
  // if((RS > dogiat && LS > dogiat) || (RS < dogiat && LS < dogiat)) {
  //   error = 0;
  // }
  // int left = tocdo + error;
  // int right =  tocdo - error;
  // if(left > 225){
  //   left = 225;
  // }
  // if(left < 0){
  //   left = 0;
  // }
  // if(right > 225){
  //   right = 225;
  // }
  // if(right < 0){
  //   right = 0;
  // }
  // dichuyen(left, right);
  
  


  if(RS > dogiat && LS < dogiat){
    // re phai
    // analogWrite(motorRspeed, 90);
    digitalWrite(R1, LOW); 
    digitalWrite(R2, HIGH);
    Serial.println("re phai");

  }
  if(LS > dogiat && RS < dogiat){
    // re trai
    // analogWrite(motorLspeed, 90);
    digitalWrite(L1, LOW); 
    digitalWrite(L2, HIGH);
    Serial.println("re trai");

  }
  if((RS > dogiat && LS > dogiat) || (RS < dogiat && LS < dogiat)){
    Serial.println("di");
    analogWrite(motorRspeed, tocdo); 
    analogWrite(motorLspeed, tocdo);
    digitalWrite(R1, HIGH); 
    digitalWrite(R2, LOW);
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
  }
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
