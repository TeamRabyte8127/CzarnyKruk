#include "UDP_Client.h"


    #include <chrono>
    #include <thread>
     

int main()
{
    UDP_Client udp;
    char pin[5] = "5";
    char power[5] = "50";
    udp.udpSend(pin);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    udp.udpSend(power);
}

// gcc client.c -g -Wall -o client && ./client
