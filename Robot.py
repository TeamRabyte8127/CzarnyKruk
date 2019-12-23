import DriveTrain
import Elevator
import Intake


class Robot:

    def __init__(self, motor1, motor2, motor3, motor4, motor5, motor6):
        self.diveTrain = DriveTrain(motor1, motor2, motor3, motor4)
        self.elevator = Elevator(motor5)
        self.intake = Intake(motor6)

    def start(self):
