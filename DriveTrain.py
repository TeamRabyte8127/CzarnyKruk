class  DriveTrain:

    def __init__(self, motor1, motor2, motor3, motor4):
        self.motor1 = motor1
        self.motor2 = motor2
        self.motor3 = motor3
        self.motor4 = motor4

    def set_motors(self, motor1_value, motor2_value, motor3_value, motor4_value):
        # Arduino set set_motors
        pass

    def move(self, foward, side, rotate):
        max_value = 100
        
        scale = max(abs(foward), abs(side), abs(rotate))

        motor1_value = (foward + side + rotate) * scale
        motor2_value = (foward - side - rotate) * scale
        motor3_value = (foward - side + rotate) * scale
        motor4_value = (foward + side - rotate) * scale

        if (motor1_value < -max_value) motor1_value = -max_value
        if (motor1_value > max_value) motor1_value = max_value

        if (motor2_value < -max_value) motor2_value = -max_value
        if (motor2_value > max_value) motor2_value = max_value

        if (motor3_value < -max_value) motor3_value = -max_value
        if (motor3_value > max_value) motor3_value = max_value

        if (motor4_value < -max_value) motor4_value = -max_value
        if (motor4_value > max_value) motor4_value = max_value

        set_motors(motor1_value, motor2_value, motor3_value, motor4_value)