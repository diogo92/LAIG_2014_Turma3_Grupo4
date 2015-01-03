#ifndef _GAMESOCKET_H_
#define _GAMESOCKET_H_

#include <winsock2.h>
#include <iostream>

#define IPADDRESS "127.0.0.1"
#define PORT 60001

bool socketConnect();
void envia(char *s, int len);
void recebe(char *ans);
void quit();

#endif