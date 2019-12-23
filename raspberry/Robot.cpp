#include "DriveTrain.h"
#include "Elevator.h"
#include "Intake.h"
#include "Communication.h"
#include <iostream>

int main()
{
    int mot1 = 1, mot2 = 2, mot3 = 3, mot4 = 4, mot5 = 5, mot6 = 6;
    int axis_xl = 0, axis_yl = 0, axis_xr = 0;

    Communication com();
    DriveTrain drive_train(mot1, mot2, mot3, mot4, com);
    Elevator elevator(mot5, com);
    Intake intake(mot6, com);

    int i = 0;

    while(i<100)  {

        std::cin>>axis_xl;
        std::cin>>axis_yl;
        std::cin>>axis_xr;

        drive_train.drive(axis_yl, axis_xl, axis_xr);

        i++;
    }
}
