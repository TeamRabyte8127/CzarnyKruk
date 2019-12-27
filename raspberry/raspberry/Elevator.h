#include <stdint.h>


class Elevator  {

    private:
        uint8_t motor1;
        const int inputCorretion = 110;

    public:
        uint8_t getMotorValue(uint8_t motor)  {
                switch(motor){
                    case motor1:
                        return 
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

    Elevator(uint8_t mot)  {
        motor1 = mot;
    }
};