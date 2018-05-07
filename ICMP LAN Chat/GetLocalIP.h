#pragma once
#include "IPpool.h"

std::array<u_char, 4> splitAndToUint(const std::string& source)
{
	using boost::lexical_cast;

	char delim = '.';
	std::array<u_char, 4> result;

	std::istringstream stream(source);
	std::string str;

	for (int i = 0; std::getline(stream, str, delim); i++)
	{
		result.at(i) = lexical_cast<int>(str);
	}

	return result;
}

std::vector<std::array<u_char, 4>> GetIP() {
	using boost::asio::ip::tcp;
	using boost::lexical_cast;

	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(boost::asio::ip::host_name(), "");
	tcp::resolver::iterator iter = resolver.resolve(query);
	tcp::resolver::iterator end;
	std::vector<std::array<u_char, 4>> LocalIP;
	while (iter != end)
	{
		tcp::endpoint ep = *iter++;
		std::string ip = lexical_cast<std::string>(ep);
		if (ip.length() < 16) {
			ip.erase(ip.end() - 2, ip.end());
			LocalIP.push_back(splitAndToUint(ip));
		}

	}

	return LocalIP;
}