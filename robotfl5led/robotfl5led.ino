#include <AFMotor.h>

AF_DCMotor motorL(3);        //motor trai
AF_DCMotor motorR(2);        //motor phai
#define MAX_SPEED 235        // cài đặt tốc độ động cơ DC motors
#define MAX_SPEED_OFFSET 20 


const int Ss1 = A5;  
const int Ss2 = A4;     
const int Ss3 = A3; 
const int Ss4 = A2; 
const int Ss5 = A1;       
int S1 ;    
int S2 ;    
int S3 ;
int S4 ;
int S5 ; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  S1 = digitalRead(Ss1);   
  S2 = digitalRead(Ss2);
  S3 = digitalRead(Ss3);
  S4 = digitalRead(Ss4);   
  S5 = digitalRead(Ss5);
  Serial.println(S1);
  

  if(S1 = HIGH){
    Serial.println("s1");
  }
  if(S2 = HIGH){
    Serial.println("s2");
  }
  if(S3 = HIGH){
    Serial.println("s3");
  }
  if(S4 = HIGH){
    Serial.println("s4");
  }
  if(S5 = HIGH){
    Serial.println("s5");
  }


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
