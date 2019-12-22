#include <cstdint>
#include "Communication.h"

class Elevator  {

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

        void move(int8_t direction)  {
            set_motors(50 * direction);
        }

        void change_pos(int8_t position)  {
            
        }

        void set_base()  {
            change_pos(1);
            change_pos(0);
        }

    Elevator(uint8_t mot, Communication comunication;)  {
        motor = mot;
        com = communication;
    }
};
