#pragma once
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

class Communication{
	 
	public:
	int serial_port;
	int readPin;
	int recieve;
	Communication(int s= serialOpen ("/dev/ttyS0", 9600),int n=16)
	{
		serial_port=s;
		readPin=n;
	}
	bool setup(int serial_port)
	{
		if (serial_port< 0)			{
			fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
			return 1;
		}
		if (wiringPiSetup () == -1)	
		{
			fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
			return 1;
		}
		return 0;
	}
	void sendData(char n)
	{
		serialPutchar(serial_port, n);
	}
	
	int getData()
	{
		int value;
		while(!serialDataAvail (serial_port) );
		if(serialDataAvail (serial_port))
			{ 
				value = serialGetchar(serial_port);
					return value;
			}
			return 0;
	}
};
