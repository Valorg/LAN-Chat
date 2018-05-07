#pragma once
#include "IPpool.h"
#include "Global.h"
//using boost::asio::ip::icmp;

class Sender
{
public:
	Sender(boost::asio::io_service& io_service) :Socket(io_service, boost::asio::ip::icmp::v4()) {
		Message.type(icmp_header::echo_request);
		Message.code(0);
		Message.identifier(0);
		Message.sequence_number(0);
	}

	void Scan() {
		boost::asio::streambuf MessageBuffer;
		std::ostream os(&MessageBuffer);
		os << Message << std::string("Hello!");
		for (int ip = 0; ip < 256; ip++) {
			EndPoint.address(boost::asio::ip::address::from_string("192.168.1." + std::to_string(ip)));
			Socket.send_to(MessageBuffer.data(), EndPoint);
		}
	}

	void SendEveryone(std::string info) {
		boost::asio::streambuf MessageBuffer;
		std::ostream os(&MessageBuffer);
		os << Message << info;

		for (auto iter: g_IPpool) {
			u_long IPL = (static_cast<u_long>(iter.at(0)) << 24)+
						(static_cast<u_long>(iter.at(1)) << 16)+
						(static_cast<u_long>(iter.at(2)) << 8)+
						(static_cast<u_long>(iter.at(3)));
			boost::asio::ip::address_v4 IP(IPL);
			EndPoint.address(IP);
			Socket.send_to(MessageBuffer.data(), EndPoint);
		}
	}

private:
	boost::asio::ip::icmp::socket Socket;
	boost::asio::ip::icmp::endpoint EndPoint;
	icmp_header Message;
};
