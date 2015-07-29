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

#include "Socket/ClientSocket.h"
#include "Socket/SocketException.h"

using namespace std;

int main() {
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
			ClientSocket clientSock("192.168.100.103",13579);
			cout << "Open connection" << endl;
			while(true)
			{
				int recv_size = clientSock.recv(recv_buf, 5);
				if(recv_size<=0)
				{
					throw SocketException ( "Could not read from socket." );
				}
				printf("Receiving %d bytes from server:", recv_size);
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
