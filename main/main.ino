// defining the RX abd TX port on Arduino Uno board
#define rx 7
#define tx 8

// defininig Trig and Echo pins for measuring distance device
#define trigPin  10
#define echoPin  9

// defining motors and motors direction pins
#define motor1 3
#define motor1dir 4
#define motor2 5
#define motor2dir 13
#define motor3 6
#define motor3dir 2
#define motor4 11
#define motor4dir 12

// including necesery libraries
#include <SoftwareSerial.h>

SoftwareSerial mySerial(rx, tx);

// variables containing motor's speed and direction
uint8_t motor1_speed, motor2_speed, motor3_speed, motor4_speed;
uint8_t motor1_dir, motor2_dir, motor3_dir, motor4_dir;
long loop_timer = 0;

// seting variables for distancemeter and and motors
long readData;
int motor;
long duration;
int distance;

void setup() {
// Setting motors pins I/O (registers)
  PORTD = B00001000;
  PORTD = B00010000;
  PORTD = B00100000;
  PORTB = B00100000;
  PORTB = B00000010;
  PORTD = B00000100;
  PORTB = B00001000;
  PORTB = B00010000;
  
  analogWrite(motor1, 0);
  analogWrite(motor2, 0);
  analogWrite(motor3, 0);
  analogWrite(motor4, 0);

  
// Setting distancemotor pins I/O
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Starting port monitor
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  
  loop_timer = micros();
  
  
  // defining control bytes
  uint8_t controlByte1, controlByte2, controlByte3, controlByte4;
  
  //to don't couse lag, we clear the buffer when there are more than 6 bytes (2 data packs) available
  if(myserial.available()>6){
    while(myserial.available()){
      myserial.read();
    }
  }
  
  //if we have more than 3 bytes in serial port read buffer, we start to read control bytes and we can receive message for one motor
  else if(myserial.available()>=3){
    uint8_t dataPck1 = myserial.read();
    uint8_t dataPck2 = myserial.read();
    uint8_t dataPck3 = myserial.read();
    controlByte1 = (0b11100000 & dataPck1)>>5;
    controlByte2 = (0b11100000 & dataPck2)>>5;
    controlByte3 = (0b11100000 & dataPck3)>>5;
    motor_id = (0b00001111 & dataPck1)
  
  }
  
  
  
  //if all data packs are correct we can write new values to the motor
  if(controlByte1 == 1 && controlByte2 == 2 && controlByte3 == 3){
    
    switch(motor_id){
      case 1: 
          motor1_speed = (0b00001111 & dataPck2) | (0b00001111 & dataPck3) << 4;
          if(motor1_speed<110)motor1_dir = 1;
          else if(motor_speed>110){
            motor1_dir = 0;
            motor1_speed -= 110;
          }
          else if(motor1_speed == 110) motor1_speed = 0;
          break;
      case 2:
          motor2_speed = (0b00001111 & dataPck2) | (0b00001111 & dataPck3) << 4;
          if(motor2_speed<110)motor2_dir = 1;
          else if(motor_speed>110){
            motor2_dir = 0;
            motor2_speed -= 110;
          }
          else if(motor2_speed == 110) motor2_speed = 0;
          break;
       case 3:
          motor3_speed = (0b00001111 & dataPck2) | (0b00001111 & dataPck3) << 4;
          if(motor3_speed<110)motor3_dir = 1;
          else if(motor_speed>110){
            motor3_dir = 0;
            motor3_speed -= 110;
          }
          else if(motor3_speed == 110) motor3_speed = 0;
          break;
       case 4:
          motor4_speed = (0b00001111 & dataPck2) | (0b00001111 & dataPck3) << 4;
          if(motor4_speed<110)motor1_dir = 1;
          else if(motor_speed>110){
            motor4_dir = 0;
            motor4_speed -= 110;
          }
          else if(motor4_speed == 110) motor4_speed = 0;
          break;
          
      }
  
  
  }
  
  while(micros() - loop_timer < 1000)
  
}
