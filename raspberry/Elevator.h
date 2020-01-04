#include <stdint.h>
#include <math.h>
#define linear_speed 50
#define scale 2.5
#define low 10
#define medium 20
#define high 30
#define speedControl 20
#define marginError 5

class Elevator  {

    private:
        uint8_t ElevatorMotor;
        uint8_t motor;
        int8_t ElevatorMotor_value;
        int8_t motor_value;
        uint8_t target_position.; 

    public:

        Elevator(uint8_t mot, uint8_t mot2)  {
            ElevatorMotor = mot;
            motor = mot2;
        }

        int8_t getElevatorMotorValue()  {
            return ElevatorMotor_value;
        }
        int8_t getMotorValue()
        {
            return motor_value;
        }

        void setPosition(int8_t trigger_state)
        {
            switch(trigger_state)
            {
                case -1:
                target_position=low;
                break;
                case 0:
                target_position = medium;
                break;
                case 1:
                target_position = high;
                break;
            }#include <stdint.h>
2
#include <math.h>
3
#define low 10;
4
#define medium 20;
5
#define high 30
6
#define speedControl 20;
7
#define marginError 5
8
​
9
class Elevator  {
10
​
11
    private:
12
        uint8_t ElevatorMotor;
13
        uint8_t motor;
14
        int8_t ElevatorMotor_value;
15
        int8_t motor_value;
16
        uint8_t target_position.; 
17
​
18
    public:
19
​
20
        Elevator(uint8_t mot, uint8_t mot2)  {
21
            ElevatorMotor = mot;
22
            motor = mot2;
23
        }
24
​
25
        int8_t getElevatorMotorValue()  {
26
            return ElevatorMotor_value;
27
        }
28
        int8_t getMotorValue()
29
        {
30
            return motor_value;
31
        }
32
​
33
        void setPosition(int8_t trigger_state)
34
        {
35
            switch(trigger_state)
36
            {
37
                case -1:
38
                target_position=low;
39
                break;
40
                case 0:
41
                target_position = medium;
42
                break;
43
                case 1:
44
                target_position = high;
45
                break;
46
            }
47
        }
48
        void changePosition(uint8_t distance)  {
49
            if (std::abs(distance-target_position>speedControl)
        }
        void changePosition(uint8_t distance)  {
            if (std::abs(distance-target_position>speedControl)
            {
                ElevatorMotor_value = linear_speed*(distance-target_position/(std::abs(distance-target_position)*(-1);
            }
            else if (std::abs(distance-target_position<speedControl && std::abs(distance-target_position>marginError) 
            {
                ElevatorMotor_value = scale*(std::abs(distance-target_position))*(distance-target_position/(std::abs(distance-target_position)*(-1);
            }
        }
        void getBall ()
        {
            motor_value = -100;
        }
        void shootBall()
        {
            motor_value = 100;
        }
        void normalPosition()
        {
            motor_value = 0;
        }
};
