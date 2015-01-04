#ifndef _GAMESOCKET_H
#define _GAMESOCKET_H

#include <winsock2.h>
#include <iostream>

#define IPADDRESS "127.0.0.1"
#define PORT 60001

class gameSocket
{
	SOCKET m_socket;
public:
	bool socketConnect();
	void envia(char *s, int len);
	void recebe(char *ans);
	void quit();
	gameSocket();
	~gameSocket();
};

#endif