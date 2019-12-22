/*
  This is sample code for distancemeter
  Model: HC-SR04
*/

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;

void setup() {

// Sets the trigPin as an Output and echoPin as an Input using registers
DDRB = B00000010;
PORTB = B00000000;

Serial.begin(9600); // Starts the serial communication
}

void loop() {
  
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
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}
