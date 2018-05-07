# LAN Chat
local network chat using ICMP Protocol

# How it works
At startup, prompts you to select a network. Then tries to ping all addresses from 192.168.1.0 to 192.168.1.255 and write the last byte of all addresses to set<short> g_IPpool.

# List of libraries used
* boost::asio (sending ICMP messages)
* winPcap (message interception, ICMP messages of type Request do not arrive at the socket, they can be intercepted by a packet sniffer)

[Download](https://github.com/Valorg/LAN-Chat/tree/master/Debug)
