#include <stdint.h>
#include <math.h>
#define low 10;
#define medium 20;
#define high 30
#define speedControl 20;
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
            }
        }
        void changePosition(uint8_t distance)  {
            if (std::abs(distance-target_position>speedControl)
            {
                ElevatorMotor_value = 50*(distance-target_position/(std::abs(distance-target_position)*(-1);
            }
            else if (std::abs(distance-target_position<speedControl && std::abs(distance-target_position>marginError) 
            {
                ElevatorMotor_value = 2,5*(std::abs(distance-target_position))*(distance-target_position/(std::abs(distance-target_position)*(-1);
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
};
