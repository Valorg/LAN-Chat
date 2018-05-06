#pragma once
#include "IPpool.h"
#include <boost/asio.hpp>
#include "icmp_header.hpp"

using boost::asio::ip::icmp;
using namespace std;
#include <string>
#include <string.h>

class Sender
{
public:
	Sender(boost::asio::io_service& io_service) :Socket(io_service, icmp::v4()) {
		Message.type(icmp_header::echo_request);
		Message.code(0);
		Message.identifier(0);
		Message.sequence_number(0);
	}

	void Send(string info, string ip) {
		boost::asio::streambuf MessageBuffer;
		std::ostream os(&MessageBuffer);
		os << Message << info;
		EndPoint.address(boost::asio::ip::address::from_string(ip));
		Socket.send_to(MessageBuffer.data(), EndPoint);
	}

	void SendHiEveryone() {
		boost::asio::streambuf MessageBuffer;
		std::ostream os(&MessageBuffer);
		os << Message << string("Hello!");
		for (int i = 0; i < 256; i++) {
			EndPoint.address(boost::asio::ip::address::from_string("192.168.1." + to_string(i)));
			Socket.send_to(MessageBuffer.data(), EndPoint);
		}
	}

private:
	icmp::socket Socket;
	icmp::endpoint EndPoint;
	icmp_header Message;
};
