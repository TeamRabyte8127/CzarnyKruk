#include "DriveTrain.h"
#include "Elevator.h"
#include "Intake.h"
#include "Communication.h"
#include "UDP_server.h"
#include <iostream>

int mot1 = 1, mot2 = 2, mot3 = 3, mot4 = 4, mot5 = 5, mot6 = 6;
int axis_xr = 0, axis_yr = 0, axis_xl = 0, l2 = 0, r2 = 0;
bool l1 = 0, r1 = 0, y = 0, b = 0, x = 0, a = 0;

int input_correction = 100;

void map_values(int values)  {
    a = values % 10; values / 10;
    x = values % 10; values / 10;
    b = values % 10; values / 10;
    y = values % 10; values / 10;
    r1 = values % 10; values / 10;
    l1 = values % 10; values / 10;
    r2 = values % 1000 - input_correction; values / 1000;
    l2 = values % 1000 - input_correction; values / 1000;
    axis_xl = values % 1000 - input_correction; values / 1000;
    axis_yr = values % 1000 - input_correction; values / 1000;
    axis_xr = values % 1000 - input_correction; values / 1000;
}

int main()
{
    Communication com();
    DriveTrain drive_train(mot1, mot2, mot3, mot4, com);
    Elevator elevator(mot5, com);
    Intake intake(mot6, com);
    UDP_Server udp_server();

    if(!com.setup()) return 1;

    while(!r1 && !l1)  {
        map_values(UDP_Server.udpServer('1'));
        drive_train.drive(axis_yl, axis_xl, axis_xr);
    }
}
