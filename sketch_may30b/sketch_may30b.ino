#include <AFMotor.h>
#include <IRremote.h>
#include <NewPing.h>
#include <Servo.h>



//motor
AF_DCMotor motorL(3);        //motor trai
AF_DCMotor motorR(2);        //motor phai

#define MAX_DISTANCE 200 
#define MAX_SPEED 235        // cài đặt tốc độ động cơ DC motors
#define MAX_SPEED_OFFSET 20  


//doline
const int SensorLeft   = A5;      //Left sensor input (A1)
const int SensorMiddle = A4;       //Midd sensor input (A2)
const int SensorRight  = A3;       //Right sensor input(A3)
int SL ;    //Status of Left line track sensor
int SM ;    //Status of Midd line track sensor
int SR ;    //Status of Righ line track sensor
int sll;
int srr;
int luustatustruoc;

//tranhvatcan
#define ECHO_PIN A0          //noi chan A0 (Uno)
#define TRIG_PIN A1          //Noi chan A1 (Uno)

Servo myservo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
boolean goesForward=false;
int distance = 100;
int speedSet = 0;
char command; 


//hongngoai
// const int Recv_Pin = 2;

void setup() {
  // put your setup code here, to run once:
    // IrReceiver.begin(Recv_Pin, true,3);
    Serial.begin(9600);
    

    //tranhvatcan
    myservo.attach(9);         //tương ứng SERVO2; NẾU CẮM SERVO1 - KHAI  myservo.attach(10);
    myservo.write(105);         //Chỉnh lại góc quay SG90: 85,95,105,... sao cho cảm biến siêu âm thẳng với xe
    delay(1000);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
}

void loop() {
      
      SL = digitalRead(SensorLeft);   
      SM = digitalRead(SensorMiddle);
      SR = digitalRead(SensorRight);

      // sll = analogRead(SensorLeft);
      // srr = analogRead(SensorRight);

      // Serial.print(sll);
      // Serial.print("   |    ");
      // Serial.print(srr);
      // Serial.print("   |    ");
      // Serial.println();

      
      // SL == HIGH
      if(SL == HIGH){
        Serial.println("trai");
        back(235,235);delay(75);
        Stop();
        forward(20,200);delay(280);
        Stop();delay(100);
      }
      // SR == HIGH
      if(SR == HIGH){
        Serial.println("phai");
        back(235,235);delay(75);
        Stop();
        forward(200,20);delay(280);
        Stop();delay(100);
      }
      // SL == LOW &&  SR == LOW
      if(SL == LOW &&  SR == LOW){
        Serial.println("chay");
        
        forward(160, 160);
      }
      else{
        back(235,235);
        Stop();
      }
      
      // if (SL == HIGH && SM == LOW && SR == LOW) {
        
      //   Serial.println("re trai");
      //   // distance = lookLeft();
      //   // Serial.println(distance);
      //   // delay(200);
      //   forward(20,200);delay(100);
      //   Stop();delay(100);
      // }
      // if (SR == HIGH && SM == LOW && SL == LOW) {
        
      //   Serial.println("re phai");
      //   // distance = lookRight();
      //   // Serial.println(distance);
      //   // delay(200);
      //   forward(200,20);delay(100);
      //   Stop();delay(100);
      // }
      
      // if(SM == HIGH && SL == HIGH && SR == LOW){
        
      //   Serial.println("re trai");
      //   forward(20,160);delay(50);
      //   Stop();delay(50);
      // }
      // if(SM == HIGH && SL == LOW && SR == HIGH){
        
      //   Serial.println("re phai");
      //   forward(160,20);delay(50);
      //   Stop();delay(50);
      // }
      // if (SM == HIGH && SL == LOW && SR == LOW) {
      // Serial.println("mid");
      //   forward(160,160);delay(200);
      //   Stop();delay(200);
      // }
      // if(SM == LOW && SL == LOW && SR == LOW){
      //     Serial.println("lui");
      //     back(160,160);delay(100);
      //     Stop();delay(100);
      // }
      // if(SM == HIGH && SL == HIGH && SR == HIGH){
      //     Serial.println("lui");
      //     back(160,160);delay(100);
      //     Stop();delay(100);
      // }
      // else{
            
      //   Stop();
      // }
      // hongngoai
      // if(IrReceiver.decode()){
      //   uint32_t dataRemote = IrReceiver.decodedIRData.decodedRawData;
      //   if(dataRemote > 0){
      //     Serial.println(dataRemote);
      //   }
      // }
}

void forward(int a, int b)
{
  motorL.setSpeed(a); //Define maximum velocity
  motorL.run(FORWARD); //rotate the motor clockwise
  motorR.setSpeed(b); //Define maximum velocity
  motorR.run(FORWARD); //rotate the motor clockwise
}
void back(int a, int b)
{
  motorL.setSpeed(a); 
  motorL.run(BACKWARD); 
  motorR.setSpeed(b); 
  motorR.run(BACKWARD); 
}
void Stop()
{
  motorL.setSpeed(0);
  motorL.run(RELEASE); 
  motorR.setSpeed(0);
  motorR.run(RELEASE); 
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(105); 
    return distance;
}
int lookLeft()
{
    myservo.write(160); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(105); 
    return distance;
    delay(100);
}
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
