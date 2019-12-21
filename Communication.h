#pragma once
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

struct message{
    uint8_t first_packet;
    uint8_t second_packet;
};

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

	message transform_data(uint16_t data, bool sign)
	{
    	message output;
    
    	output.first_packet = (uint8_t)((data & 0xFF00) >> 8);
    	output.second_packet = (uint8_t)((data & 0xFF));
    
    	output.first_packet = output.first_packet|(sign<<7);
    
    	return output;
	}

	void sendData(message data)
	{
		serialPutchar(serial_port, data.first_packet)
		serialPutchar(serial_port, data.second_packet);
	}
	bool dataAvailable()
	{
		return dataAvailable(serial_port);
	uint8_t getData()
	{
		uint8_t value;
		while(!serialDataAvail (serial_port) );
		if(serialDataAvail (serial_port))
			{ 
				value = serialGetchar(serial_port);
					return value;
			}
			return 0;
	}
};
