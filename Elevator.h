#include <stdint.h>
#include <math.h>
#define low 10;
#define medium 20;
#define high 30
#define speedControl 20;
#define marginError 3

class Elevator  {

    private:
        uint8_t motor;
        int8_t motor_value;
        uint8_t target_position; 
        int8_t speed;

    public:

        Elevator(uint8_t mot)  {
            motor = mot;
        }

        uint8_t getMotorValue()  {
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
        int8_t change_pos(uint8_t distance)  {
            if (std::abs(distance-target_position>speedControl)
            {
                motor_value = 50*(distance-target_position/(std::abs(distance-target_position)*(-1);
            }
            else if (std::abs(distance-target_position<speedControl && std::abs(distance-target_position>marginError) 
            {
                motor_value = 2,5*(std::abs(distance-target_position))*(distance-target_position/(std::abs(distance-target_position)*(-1);
            }
        }
    }
};