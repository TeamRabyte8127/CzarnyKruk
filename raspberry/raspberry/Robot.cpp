#include <iostream>
#include "DriveTrain.h"
//#include "Elevator.h"
//#include "Intake.h"
#include "Communication.h"
#include "udp_client_server.h"
#include <unistd.h>

#define PORT 8888
#define IP "192.168.0.11"

using namespace udp_client_server;


bool running = true;
char msg[4];
int mot1 = 1, mot2 = 2, mot3 = 3, mot4 = 4, mot5 = 5, mot6 = 6;
double xl = 0, yl = 0, xr = 0, yr = 0, rt = 0, lt = 0;
bool rb = 0, lb = 0, a = 0, b = 0, x = 0, y = 0, re = 0, st = 0, up = 0, left = 0, right = 0, down = 0;


int decode(char *msg)   {
    int i;
    sscanf(msg, "%d", &i);
    return i;
}


int main()
{
    
    Communication com;
    DriveTrain drive_train(mot1, mot2, mot3, mot4);
    //Elevator elevator(mot5);
    //Intake intake(mot6);
    
    /* Creting new server object receiving only with 
     * defined PORT and IP */
    udp_server server(IP, PORT);
    std::cout << "Running at port: " << server.get_port() << std::endl;
    std::cout << "Running at ip: " << server.get_addr() << std::endl;
    
    
	
    if(!com.setup()) return 1;
    
    
    
    for (int i = 0; i < 4; i++)
    {
	for (int i = 0; i < 4; i++)
	{
		server.recv(msg, 4);
		switch(i)
		{
			case 0:
			yl = decode(msg);
			break;
			case 1:
			xr = decode(msg);
			break;
			case 2:
			yr = decode(msg);
			break;
			case 3:
			xl = decode(msg);
			break;
		}
		memset(msg, 0, 4);
	
	}
	
        std::cout << xl << "\n" << yl << "\n"<< xr << "\n" << yr << "\n";

        drive_train.drive(xr, yr, xl);
/*
        com.sendData(com.setData(drive_train.getMotorValue(mot1),mot1));
        com.sendData(com.setData(drive_train.getMotorValue(mot2),mot2));
        com.sendData(com.setData(drive_train.getMotorValue(mot3),mot3));
        com.sendData(com.setData(drive_train.getMotorValue(mot4),mot4));  */
	
    }
    return 0;
}
