#include "DriveTrain.h"
#include "Elevator.h"
#include "Intake.h"
#include "Communication.h"
#include <iostream>

int main()
{
    int a,b,c,d,e,f,g,h;
    std::cin>>a;
    std::cin>>b;
    std::cin>>c;
    std::cin>>d;
    std::cin>>e;
    std::cin>>f;
    std::cin>>g;
    std::cin>>h;

    DriveTrain drive_train(a, c, e, g);
    drive_train.set_motors(b, d, f, h);
    int recieve;
    Communication com;
    wiringPiISR(com.readPin, INT_EDGE_FALLING, &com.interrupt);
    std::cout<<recieve;
}
