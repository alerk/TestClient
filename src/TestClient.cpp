//============================================================================
// Name        : TestClient.cpp
// Author      : QuyenNX
// Version     :
// Copyright   : ITT Solution
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>

#include "Socket/ClientSocket.h"
#include "Socket/SocketException.h"

using namespace std;

int main() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];
	char* recv_buf;


	recv_buf = (char*)malloc(15);
	//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	int counter = 0;
	while(true)
	{
		try
		{

			//			system("clear");
			cout << "\r" << std::flush;
			cout << "Trying to connect " << counter++ << endl;
			counter %= 10;
			ClientSocket clientSock("localhost",13579);
			cout << "Open connection" << endl;
			while(true)
			{
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				strftime (buffer,80,"[%D - %H:%M:%S]",timeinfo);
				int recv_size = clientSock.recv(recv_buf, 5);
				if(recv_size<=0)
				{
					throw SocketException ( "Could not read from socket." );
				}
				printf("%sReceiving %d bytes from server:", buffer, recv_size);
				for(int i=0;i<5;i++)
				{
					printf("%2.2x",(unsigned char)recv_buf[i]);
				}
				if((recv_buf[4]&0x0F))
				{
					printf("\t ====> Fired @ %d!", (recv_buf[4]&0x0F));
				}

				if((recv_buf[4]&0x20))
				{
					printf("\t ====> Intruder!");
				}
				printf("\n");
			}
		}
		catch(SocketException &e)
		{
			sleep(1);
//			cout << "Error " << e.description() << endl;
			//break;
		}
	}
	return 0;
}
