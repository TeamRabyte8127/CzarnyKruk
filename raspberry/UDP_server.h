#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> // memset()
#include <string> // memset()
#include <arpa/inet.h> // inet_pton()
#include <sys/socket.h>

#define SERWER_PORT 8888
#define SERWER_IP "192.168.1.88"


class UDP_Server
{
    public:
        std::string udpServer(char response [4096])  {
            struct sockaddr_in serwer =  {
                .sin_family = AF_INET,
                .sin_port = htons( SERWER_PORT )
            };
            
            if( inet_pton( AF_INET, SERWER_IP, & serwer.sin_addr ) <= 0 )  {
                perror( "inet_pton() ERROR" );
                exit( 1 );
            }
            
            const int socket_ = socket( AF_INET, SOCK_DGRAM, 0 );
            
            if(( socket_ ) < 0 ) {
                perror( "socket() ERROR" );
                exit( 2 );
            }
            
            char buffer[ 4096 ] = { };
            
            socklen_t len = sizeof( serwer );
            if( bind( socket_,( struct sockaddr * ) & serwer, len ) < 0 )  {
                perror( "bind() ERROR" );
                exit( 3 );
            }
            
            while( 1 )  {
                struct sockaddr_in client = { };
                
                memset( buffer, 0, sizeof( buffer ) );
                
                printf( "Waiting for connection...\n" );
                if( recvfrom( socket_, buffer, sizeof( buffer ), 0,( struct sockaddr * ) & client, & len ) < 0 )  {
                    perror( "recvfrom() ERROR" );
                    exit( 4 );
                }
                printf( "|Message from client|: %s \n", buffer );
                
                std::string mes;
                for(int i = 0; i<5; i++)  {
                    mes+=buffer[i];
                }

                
                char buffer_ip[ 128 ] = { };
                printf( "|Client ip: %s port: %d|\n", inet_ntop( AF_INET, & client.sin_addr, buffer_ip, sizeof( buffer_ip ) ), ntohs( client.sin_port ) );
                
                strncpy( buffer,response, sizeof( buffer ) );

                if( sendto( socket_, buffer, strlen( buffer ), 0,( struct sockaddr * ) & client, len ) < 0 )  {
                    perror( "sendto() ERROR" );
                    exit( 5 );
                }
                return (mes);
            }
            
            shutdown( socket_, SHUT_RDWR );
        }
};
// gcc server.c -g -Wall -o server && ./server
