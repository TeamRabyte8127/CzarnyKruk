#include <cstdint.h>
#include <math.h>
#include <algorithm>
#include "Communication.h"

class DriveTrain  {

    private:
        uint8_t motor1, motor2, motor3, motor4;
        Communication com;
        const int inputCorretion = 110;
    
    public:
        void set_motors(int16_t motor1_value, int16_t motor2_value, int16_t motor3_value, int16_t motor4_value)  {
            if(!com.setup(com.serial_port))  {
                com.sendData(com.setData(motor1_value + inputCorretion, motor1));
                com.sendData(com.setData(motor2_value + inputCorretion, motor2));
                com.sendData(com.setData(motor3_value + inputCorretion, motor3));
                com.sendData(com.setData(motor4_value + inputCorretion, motor4));
            }
        }

        void drive(int8_t foward, int8_t side, int8_t rotate)  {
            const uint8_t max_value = 100;
        
            int8_t scale = std::max(std::max(std::abs(foward), std::abs(side)), std::abs(rotate));

            int16_t motor1_value = (foward + side + rotate) * scale;
            int16_t motor2_value = (foward - side - rotate) * scale;
            int16_t motor3_value = (foward - side + rotate) * scale;
            int16_t motor4_value = (foward + side - rotate) * scale;

            if (motor1_value < -max_value) motor1_value = -max_value;
            if (motor1_value > max_value) motor1_value = max_value;

            if (motor2_value < -max_value) motor2_value = -max_value;
            if (motor2_value > max_value) motor2_value = max_value;

            if (motor3_value < -max_value) motor3_value = -max_value;
            if (motor3_value > max_value) motor3_value = max_value;

            if (motor4_value < -max_value) motor4_value = -max_value;
            if (motor4_value > max_value) motor4_value = max_value;

            set_motors(motor1_value, motor2_value, motor3_value, motor4_value);

        }

    DriveTrain(uint8_t mot1, uint8_t mot2, uint8_t mot3, uint8_t mot4, Communication comunication;)  {
        motor1 = mot1;
        motor2 = mot2;
        motor3 = mot3;
        motor4 = mot4;
        com = communication;
    }
};
