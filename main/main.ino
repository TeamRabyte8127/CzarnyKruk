/*
  Team RaByte #8127
  Project: CzarnyKruk
  Arduino code
  Motors, distancemeter and Raspberry Pi
  communication.
  
  12-2019
*/


// defining data pins for distancemter
#define trigPin A3
#define echoPin A2

// defining motors and motors direction pins
#define motor1 3
#define motor1dir 4
#define motor1_enca 
#define motor1_encb 

#define motor2 5
#define motor2dir 13
#define motor2_enca 
#define motor2_encb 

#define motor3 6
#define motor3dir 7
#define motor3_enca PINC0
#define motor3_encb PINC1

#define motor4 11
#define motor4dir 12
#define motor4_enca 
#define motor4_encb

// LIFT
#define motor5 9
#define motor5dir 8
#define motor5_enca 
#define motor5_encb

#define motor6 10
#define motor6dir 2
#define motor6_enca 
#define motor6_encb

// defines variables for distancemeter
long duration;
int distance;

// variables containing motor's speed and direction
uint8_t motor1_speed_raw, motor2_speed_raw, motor3_speed_raw, motor4_speed_raw;
uint8_t motor1_speed, motor2_speed, motor3_speed, motor4_speed;
uint8_t pid_p = 0.5;
uint8_t motor_id, motor_speed, motor_dir;
uint8_t dataPck;

long loop_timer = 0;
long enc_timer;
long motor_speed_read;

// seting variables for distancemeter and and motors
int encCount = 0;

void setup() {
//setup external interrupts to read motors speed and direction
SREG |= 0b1 << 7;
PCICR |= 0b111;
PCMSK2 |= 0b00000000;
PCMSK1 |= 0b00000011;
PCMSK0 |= 0b00000000;

// Sets the trigPin as an Output and echoPin as an Input using registers
DDRB = B00000010;
PORTB = B00000000;

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
  
  // Starting serial port with bound 115200 bits per second, parity bit set to even, with two stop bits. This ensure us reaible connection
  Serial.begin(9600);
}

void loop() {

  loop_timer = micros();
  
  // Clears the trigPin
  PORTD = B00000000;
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  PORTB = (1 << 1) | PORTD;
  delayMicroseconds(10);
  PORTB = ~(1 << 1) & PORTD;
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration*0.034/2;
  
  // Prints the distance on the Serial Monitor

  //simple PID algorithm (only P algorithm in fact)
  motor1_speed += (motor1_speed_raw - motor1_speed)*pid_p;
  motor2_speed += (motor2_speed_raw - motor2_speed)*pid_p;
  motor3_speed += (motor3_speed_raw - motor3_speed)*pid_p;
  motor4_speed += (motor4_speed_raw - motor4_speed)*pid_p;

  // setMotorSpeed(motor1, motor1_speed);
  // setMotorSpeed(motor2, motor2_speed);
  // setMotorSpeed(motor3, motor3_speed);
  analogWrite(motor4, motor4_speed_raw);


  while(micros()-loop_timer<1000){
    
  }


}

// Our datapacks look like this:

// 11100111             11110111                                                            11110111
// motor id + pckId     motor speed and motor direction (>110, left; <110, right) + pckId   motor speed and motor direction (>110, left; <110, right) + pckId

//Thus, we receive three Bytes of data per motor

void serialEvent(){                                                                               //SerialEvent triggers every time we receive UART data

  if(Serial.available()){
    digitalWrite(11, !digitalRead(11));

    uint8_t read = Serial.read();                                                                 //we read incoming data
    uint8_t packId = read & 0b111;                                                           //we read packId
    if(dataPck == packId){                                                                        //we validate if we have read correct pack
      if(dataPck == 7){                                                                           //if it's first pack we get motor id                                                                                                      //we read incoming Byte
        motor_id = 0b11100000 & read;                                                              
        dataPck = 5;                                                                             //now we wait for next pack with motor's speed
      }
      else if(dataPck == 5){                                                                      //if it's second pack we get first 4 bits of motor speed
        motor_speed = (0b11110000 & read)>>4;                                                                   
        dataPck = 3;                                                                             //now we wait for next pack with more motor's speed
      }
      else if(dataPck == 3){                                                                      //if it's third pack we get last 4 bits of motor speed
        motor_speed = motor_speed | (read & 0b11110000);                                                  //we combine bits to form 8 bits of motor speed (max value is 255)
        if(motor_speed<110)motor_dir = 1;                                                         //we obtain motor's direction
        else if(motor_speed>110){
          motor_dir = 0;
          motor_speed -= 110;
        }
        else if(motor_speed=110)motor_speed = 0;

        switch(motor_id){                                                                         //we see which motor we should apply those setting to (by knowing motor_id)
          case 1:
            PORTD |= motor_dir << 4;
            motor1_speed_raw = motor_speed;
            break;
          case 2:
            PORTB |= motor_dir << 5;
            motor2_speed_raw = motor_speed;
            break;
          case 3:
            PORTD |= motor_dir << 2;
            motor3_speed_raw = motor_speed;
            break;
          case 4:
            PORTB |= motor_dir << 4;
            motor4_speed_raw = motor_speed;
            break;
        }
        dataPck = 7;
      }
      else{
        dataPck = 7;
      }
    }
    else{
      dataPck = 7;
    }
  }

}

void setMotorSpeed(uint8_t motorID, uint8_t motorSpeed){

  //we can come up with something more brilliant
  analogWrite(motorID, map(motorSpeed, 0, 110, 0, 255));

}

//do stuff on interrupt on PCINT8...15
ISR(PCINT1_vect){
  motor_speed_read = micros() - enc_timer;
  enc_timer = micros();
  if(PINB & (0b1 << motor3_enca)) {
    if(!(PINB & (0b1 << motor3_encb))) {
      encCount++;
    } else {
      encCount--;
    }
  } else {
    if (!(PINB & (0b1 << motor3_encb))) {
      encCount--;
    } else {
      encCount++;
    }
  }
}
