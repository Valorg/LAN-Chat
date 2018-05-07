#pragma once
#include "IPpool.h"


std::vector<std::array<u_char,4>> GetArp() {
	MIB_IPNETTABLE * pIpNetTable = (MIB_IPNETTABLE *)malloc(0xFFFF);
	ULONG        cbIpNetTable = 0xFFFF;
	GetIpNetTable(pIpNetTable, &cbIpNetTable, TRUE);

	std::vector<std::array<u_char, 4>> Res;

	for (DWORD i = 0; i < pIpNetTable->dwNumEntries; i++)
	{
		if (pIpNetTable->table[i].dwType == 3) {
			std::array<u_char, 4> Buf;
			Buf[0] = (pIpNetTable->table[i].dwAddr << 24) >> 24;
			Buf[1] = (pIpNetTable->table[i].dwAddr << 16) >> 24;
			Buf[2] = (pIpNetTable->table[i].dwAddr << 8) >> 24;
			Buf[3] = pIpNetTable->table[i].dwAddr >> 24;
			Res.push_back(Buf);
		}
	}
	free(pIpNetTable);
	return Res;
}