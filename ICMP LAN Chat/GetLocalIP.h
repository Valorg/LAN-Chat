#pragma once
#include <winsock2.h>
#include <string>
#include <boost/lexical_cast.hpp>
#pragma comment(lib,"WS2_32.lib")

short GetIP() {
	WSAData wsaData;
	hostent *h;
	char buf[128];
	WSAStartup(WINSOCK_VERSION, &wsaData);
	gethostname(buf, 128);
	h = gethostbyname(buf);
	std::string addr = inet_ntoa(*(reinterpret_cast<in_addr *>(*(h->h_addr_list))));
	WSACleanup();
	addr.erase(0, 10);
	return boost::lexical_cast<short>(addr);
}