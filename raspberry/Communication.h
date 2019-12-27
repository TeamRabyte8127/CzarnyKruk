#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>
#include <vector>
#include <stdint.h>

using namespace std;

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

	Communication(int s = serialOpen ("/dev/ttyS0", 9600),int n=16)
	{
		serial_port=s;
		readPin=n;
	}

	template <typename T> uint8_t countBits(T a, int n){
	    uint8_t number = 0;
	    for (int i = n-1; i>=0; i--){
	        number += (1&(a>>i));
    	}
    return number;
	}

	uint8_t setBits(uint8_t var, uint8_t value, int second)
	{
    	var = var|(value<<(8-second));
    	return var;
	}

	message setData(uint8_t value, uint8_t motor)
	{
	    message output;
	    output.numberOfPackets=2;
	    output.setPackets();
	    
	    uint8_t direction=0b00000001&(value>>7);
	    value = value&0b01111111;
	    
	    output.packets[0]=setBits(output.packets[0], countBits(value, 8), 4);
	    output.packets[0]=setBits(output.packets[0], motor, 7);
	    output.packets[0]=setBits(output.packets[0], direction, 8);
	    
	    output.packets[1]=setBits(output.packets[1], 1, 1);
	    output.packets[1]=setBits(output.packets[1], value, 8);

    	return output;
    }	

	bool setup()
	{
		if (serial_port< 0)			{
			fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
			return 0;
		}
		if (wiringPiSetup () == -1)	
		{
			fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
			return 0;
		}
		return 1;
	}

	void sendData(message data)
	{
		for(int i = 0; i<2; i++){
			serialPutchar(serial_port, data.packets[i]);
		}
	}

	bool dataAvailable()
	{
		return serialDataAvail(serial_port);
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
