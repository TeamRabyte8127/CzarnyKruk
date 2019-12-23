#include <cstdint>
#include "Communication.h"

class Intake  {

    private:
        uint8_t motor;
        Communication com;
        const int inputCorretion = 110;

    public:
        void set_motors(int16_t motor_value)  {
                com.sendData(com.setData(motor_value + inputCorretion, motor));
        }

        void rotate(int8_t direction)  {
            set_motors(50 * direction);
        }
    
    Intake(uint8_t mot, Communication comunication;)  {
        motor = mot;
        com = communication;
    }
};