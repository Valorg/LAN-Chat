#pragma once
#include "IPpool.h"

std::mutex g_mt;
std::set<std::array<u_char, 4>> g_IPpool;