// IR Sensors
int sensor1 = 2;      // Trái ngoài cùng sensor
int sensor2 = 3;
int sensor3 = 4;
int sensor4 = 5;      
int sensor5 = 6;      // Phải ngoài cùng sensor

// Initial Values of Sensors
int sensor[5] = {0, 0, 0, 0, 0};

// Motor Variables
int ENA = 9;              //Motor Trái
int motorInput1 = 8;
int motorInput2 = 7;
int motorInput3 = 12;
int motorInput4 = 11;
int ENB = 10;             //Motor Phải

unsigned long previousMillis = 0;
const long interval = 5500;
bool hasRun = false; 

//Initial Speed of Motor
int initial_motor_speed = 255;
int initial_motor_speed_after = 200;
// int valueO = 0;

// PID Constants
float Kp = 105;
float Ki = 0;
float Kd = 20;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);

  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Serial.begin(9600);                    
  // Serial.println("Started !!");
  delay(2000);

}

void loop() {

    unsigned long currentMillis = millis(); // Lấy thời điểm hiện tại

  if (!hasRun && currentMillis - previousMillis >= interval) {
    initial_motor_speed = initial_motor_speed_after;
    hasRun = true;
  }

  read_sensor_values();
  // Serial.print("\t");
  // Serial.println(error);

  calculate_pid();
  motor_control();

  // testmotorr();
  // testmotorl();
}

void read_sensor_values()
{
  sensor[0] = digitalRead(sensor1);
  sensor[1] = digitalRead(sensor2);
  sensor[2] = digitalRead(sensor3);
  sensor[3] = digitalRead(sensor4);
  sensor[4] = digitalRead(sensor5);

  // Serial.print(sensor[4]);
  // Serial.print("\t");
  // Serial.print(sensor[3]);
  // Serial.print("\t");
  // Serial.print(sensor[2]);
  // Serial.print("\t");
  // Serial.print(sensor[1]);
  // Serial.print("\t");
  // Serial.print(sensor[0]);

  if      ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1)){
      error = -5;
      initial_motor_speed = initial_motor_speed_after;
  } // lệch phải nhiều
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    error = -3;  
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    error = -2;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))
    error = -1;                                                    
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))  // ko lệch
    error = 0;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1))
    error = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 1))
    error = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    error = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0)){
    error = 5;
    initial_motor_speed = initial_motor_speed_after;

  }  // lệch trái nhiều

  // else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))  // lệch trái nhiều
  //   error = 100;

  // else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[3] == 1) && (sensor[4] == 1)) // Turn robot right side
  //   error = 101;
  // else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[3] == 0) && (sensor[4] == 0)) // Make U turn
  //   error = 102;
  // else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[3] == 1) && (sensor[4] == 1)) // Turn left side or stop
  //   error = 103;
}

void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D); 

  previous_I = I;
  previous_error = error;

  // if(error == 0){
  //   valueO = 255;
  // }
  // else{
  //   valueO = 0;
  // };

}

void motor_control()
{
  // Calculating the effective motor speed:
  
  int left_motor_speed = initial_motor_speed - PID_value ;   
  int right_motor_speed = initial_motor_speed + PID_value; 

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 255);   
  right_motor_speed = constrain(right_motor_speed, 0, 255); 

  // Serial.print(left_motor_speed);
  // Serial.print("\t");
  // Serial.print(right_motor_speed);
  // Serial.print("\t");


    analogWrite(ENA, left_motor_speed);
    analogWrite(ENB, right_motor_speed);
    forward();
    unsigned long currentMillis = millis();

  // if (currentMillis - previousMillis >= 27000) {
  //   controlleft(left_motor_speed);
  //   controlright(right_motor_speed);
  // }
  // else{
  //   analogWrite(ENA, left_motor_speed);
  //   analogWrite(ENB, right_motor_speed);
  //   forward();

  // }
    //   controlleft(left_motor_speed);
    // controlright(right_motor_speed);

}

void forward()
{
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}


void controlright(int speed){
  if(speed == 0){
    analogWrite(ENB, 10);
    digitalWrite(motorInput3, LOW);
    digitalWrite(motorInput4, HIGH);
  }
  else{
    analogWrite(ENB, speed);
    digitalWrite(motorInput3, HIGH);
    digitalWrite(motorInput4, LOW);
  }
}

void controlleft(int speed){
  if(speed == 0){
    analogWrite(ENA, 10);
    digitalWrite(motorInput1, LOW);
    digitalWrite(motorInput2, HIGH);
  }
  else{
    analogWrite(ENA, speed);
    digitalWrite(motorInput1, HIGH);
    digitalWrite(motorInput2, LOW);
  }

}





void testmotorr(){
  analogWrite(ENB, 110);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}

void testmotorl(){
  analogWrite(ENA, 200);
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);

}