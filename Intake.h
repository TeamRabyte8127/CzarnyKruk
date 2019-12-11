#include <cstdint>


class Intake  {

    private:
        uint8_t motor;

    public:
        void set_motors(int16_t motor_value)  {

        }

        void rotate(int8_t direction)  {
            set_motors(50 * direction);
        }
};