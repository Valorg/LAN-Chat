#pragma once

#include <iostream>
#include <locale.h>
#include <mutex> 
#include <set>
#include <thread>
#include <iostream>
#include <vector>
#include <array>

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <pcap.h>

#include <iphlpapi.h>
#pragma comment (lib, "iphlpapi.lib")
#include "GetLocalIP.h"
#include "GetArp.h"
#include "icmp_header.hpp"
#include "Sender.h"
#include "Listener.h"