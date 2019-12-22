#include <cstdint>
#include "Communication.h"

class Intake  {

    private:
        uint8_t motor;
        Communication com;
        const int inputCorretion = 110;

    public:
        void set_motors(int16_t motor_value)  {
            if(!com.setup(com.serial_port))  {
                com.sendData(motor); com.sendData(motor_value + inputCorretion);
            }
        }

        void rotate(int8_t direction)  {
            set_motors(50 * direction);
        }
    
    Intake(uint8_t mot, Communication comunication;)  {
        motor = mot;
        com = communication;
    }
};
