#pragma once
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

struct message{
    vector<uint8_t> packets;
    int numberOfPackets;
    void setPackets(){
        packets.resize(numberOfPackets);
        for(int i = 0; i<numberOfPackets; i++){
            packets[i]=0x0000;
        }
    }
};

class Communication{
	 
	public:
	int serial_port;
	int readPin;
	int recieve;

	uint8_t setBits(uint8_t var, uint8_t value, int second)
	{
    	var = var|(value<<(8-second));
    	return var;
	}

	message setData(uint8_t value, uint8_t motor)
	{
	    message output;
	    output.numberOfPackets=3;
	    output.setPackets();
	    
	    uint8_t transformedValue[2];
	    
	    transformedValue[1]=(uint8_t)(0x0F & value);
	    transformedValue[0]=value>>4;
	    
	    output.packets[0]=setBits(output.packets[0], 7, 3);
	    output.packets[0]=setBits(output.packets[0], motor, 8);
	    
	    output.packets[1]=setBits(output.packets[1], 5, 3);
	    output.packets[1]=setBits(output.packets[1], transformedValue[0], 8);
	    
	    output.packets[2]=setBits(output.packets[2], 3, 3);
	    output.packets[2]=setBits(output.packets[2], transformedValue[1], 8);
    
    	return output;
    }	

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

	void sendData(message data)
	{
		for(int i = 0; i<3; i++){
			serialPutchar(serial_port, data.packets[i]);
		}
	}

	bool dataAvailable()
	{
		return dataAvailable(serial_port);
	}

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
