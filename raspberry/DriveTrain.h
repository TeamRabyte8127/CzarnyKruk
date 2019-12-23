#include <stdint.h>
#include <math.h>
#include <algorithm>
#include "Communication.h"

class DriveTrain  {

    private:
        const int inputCorretion = 110;
        uint8_t motor1, motor2, motor3, motor4;
        
        int8_t motor1_value, motor2_value, motor3_value, motor4_value;
    
    public:

        uint8_t getMotorValue(uint8_t motor)  {
            switch (motor){
                case motor1:
                    return uint8_t(motor1_value+inputCorretion);
                case motor2:
                    return uint8_t(motor2_value+inputCorretion);
                case motor3:
                    return uint8_t(motor3_value+inputCorretion);
                case motor4:
                    return uint8_t(motor4_value+inputCorretion);
            }
        }

        void drive(int8_t foward, int8_t side, int8_t rotate)  {
            const uint8_t max_value = 100;
        
            int8_t scale = max(max(abs(foward), abs(side)), abs(rotate));

            motor1_value = (foward + side + rotate) * scale;
            motor2_value = (foward - side - rotate) * scale;
            motor3_value = (foward - side + rotate) * scale;
            motor4_value = (foward + side - rotate) * scale;

            if (motor1_value < -max_value) motor1_value = -max_value;
            if (motor1_value > max_value) motor1_value = max_value;

            if (motor2_value < -max_value) motor2_value = -max_value;
            if (motor2_value > max_value) motor2_value = max_value;

            if (motor3_value < -max_value) motor3_value = -max_value;
            if (motor3_value > max_value) motor3_value = max_value;

            if (motor4_value < -max_value) motor4_value = -max_value;
            if (motor4_value > max_value) motor4_value = max_value;

        }

    DriveTrain(uint8_t mot1, uint8_t mot2, uint8_t mot3, uint8_t mot4)  {
        motor1 = mot1;
        motor2 = mot2;
        motor3 = mot3;
        motor4 = mot4;
    }
};
