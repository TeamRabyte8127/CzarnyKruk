#pragma once
#include <iostream>
#include "DriveTrain.h"
#include "Elevator.h"
//#include "Intake.h"
#include "Communication.h"
#include "UDP_server.h"

int mot1 = 1, mot2 = 2, mot3 = 3, mot4 = 4, mot5 = 5, mot6 = 6;
int xl = 0, yl = 0, xr = 0, yr = 0, rt = 0, lt = 0;
bool rb = 0, lb = 0, a = 0, b = 0, x = 0, y = 0, re = 0, st = 0, up = 0, left = 0, right = 0, down = 0;

void decode(std::string msg)
{
	msg = msg.substr(3, msg.size() - 6);

	size_t pos = 0;
	std::string delimiter = "},{";
	int i = 0;
	while ((pos = msg.find(delimiter)) != std::string::npos)
	{
		elements[i] = msg.substr(0, pos);
		msg.erase(0, pos + delimiter.length());
		i++;
	}

	delimiter = ":";
	for (int i = 0; i < 18; i++)
	{
		while ((pos = elements[i].find(delimiter)) != std::string::npos)
		{
			elements[i] = elements[i].substr(pos + 1, elements[i].size() - 1);
		}
	}
	xl = std::stof(elements[0]) * 100 + 100;
	yl = std::stof(elements[1]) * 100 + 100;
	xr = std::stof(elements[2]) * 100 + 100;
	yr = std::stof(elements[3]) * 100 + 100;
	rb = std::stoi(elements[4]) * 100 + 100;
	lb = std::stoi(elements[5]) * 100 + 100;
	rt = std::stof(elements[6]) * 100 + 100;
	lt = std::stof(elements[7]) * 100 + 100;
	a = std::stoi(elements[8]);
	b = std::stoi(elements[9]);
	x = std::stoi(elements[10]);
	y = std::stoi(elements[11]);
	re = std::stoi(elements[12]);
	st = std::stoi(elements[13]);
	up = std::stoi(elements[14]);
	left = std::stoi(elements[15]);
	right = std::stoi(elements[16]);
	down = std::stoi(elements[17]);
}

int main()
{
    Communication com;
    DriveTrain drive_train(mot1, mot2, mot3, mot4);
    Elevator elevator(mot5);
    //Intake intake(mot6);
    UDP_Server udp_server;

    if(!com.setup()) return 1;

    while(!r1 && !l1)  {
        //decode(udp_server.udpServer('1'));
        std::cout << udp_server.udpServer('1');
        cout<<xl<<yl<<xr<<yr;
        drive_train.drive(xr, yr, xl);
      //  elevator.setPosition(lt);
        //w tym komentarzu chodzi o to zebyście mi dali dalmierz = com.getData();
      //  elevator.changePosition(dalmierz);
      //  com.sendData(com.setData(elevator.getMotorValue(mot5),mot5));
/*
        com.sendData(com.setData(drive_train.getMotorValue(mot1),mot1));
        com.sendData(com.setData(drive_train.getMotorValue(mot2),mot2));
        com.sendData(com.setData(drive_train.getMotorValue(mot3),mot3));
        com.sendData(com.setData(drive_train.getMotorValue(mot4),mot4));  */
    }
}
