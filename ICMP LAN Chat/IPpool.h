#pragma once
#include <iostream>
#include <locale.h>
#include <mutex> 
#include <set>
#include <thread>
#include <iostream>
#include <string.h>

#include "Sender.h"
#include "Listener.h"

using namespace std;

mutex g_mt;
set<short> g_IPpool;