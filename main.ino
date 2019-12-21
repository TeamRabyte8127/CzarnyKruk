#define rx 7
#define tx 8

#define trigPin  10
#define echoPin  9

#define motor1 3
#define motor1dir 4
#define motor2 5
#define motor2dir 13
#define motor3 6
#define motor3dir 2
#define motor4 11
#define motor4dir 12

#include <SoftwareSerial.h>

SoftwareSerial mySerial(rx, tx);

int readData;
int motor;
long duration;
int distance;
void setup() {
// silniki
  PORTD = B00001000;
  PORTD = B00010000;
  PORTD = B00100000;
  PORTB = B00100000;
  PORTB = B00000010;
  PORTD = B00000100;
  PORTB = B00001000;
  PORTB = B00010000;
// Dalmierz
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //DDRB = B00000010;
  //PORTB = B00000100;
  
  Serial.begin(9600);

  mySerial.begin(9600);
}
void loop() {

  while (mySerial.available())
  {
    readData = mySerial.read();
    Serial.println(readData);
    
    if(readData==-1)break;
    
    else if (readData < 10)
    {
      switch (readData) {
        case 1:
          motor = 1;
          break;
    
        case 2:
          motor = 2;
          break;
  
        case 3:
          motor = 3;
          break;
  
        case 4:
          motor = 4;
          break;
      }
    }
    else {
      if ((readData < 110) && (readData > 10))
   
      {
        switch(motor)
        {
          case 1:
          //digitalWrite(motor1dir,LOW);
          PORTD = B00000000;
          break;
          
          case 2:
          //digitalWrite(motor2dir,LOW);
          PORTB = B00000000;
          break;
          
          case 3:
          //digitalWrite(motor3dir,LOW);
          PORTD = B00000000;
          break;
          
          case 
          //digitalWrite(motor4dir,LOW);
          PORTB = 00000000;
          break;
        }
     int value=map(readData,10,110,0,255);
       analogWrite(motor, value);
    }
    else if(readData>110&&readData<210)
    {
      switch(motor)
      {
        case 1:
        //digitalWrite(motor1dir, HIGH);
        PORTD = B00010000;
        break;
        
        case 2:
        //digitalWrite(motor2dir, HIGH);
        PORTB = B00100000;
        break;
        
        case 3:
        //digitalWrite(motor3dir, HIGH);
        PORTD = B00000100;
        break;
        
        case 4:
        //digitalWrite(motor4dir, HIGH);
        PORTB = B00010000;
        break;
      }
       int value=map(readData,10,110,0,255);
       analogWrite(motor, value);
    }
  }

  } 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  if (distance > 200) {
    distance = 200;
  }
  Serial.println(distance);
  mySerial.write(distance);

 
}