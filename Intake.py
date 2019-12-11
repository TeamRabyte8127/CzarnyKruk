class Intake:

    def __init__(self, motor):
        self.motor = motor

    def start(self, direction):
        set_motors(direction*50)

    def set_motors(self, motor_value):
        # Arduino set set_motors
        pass