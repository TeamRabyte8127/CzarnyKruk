#include <cstdint>


class Elevator  {

    private:
        uint8_t motor;

    public:
        void set_motors(int16_t motor_value)  {

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
        motor = mot;
    }
};