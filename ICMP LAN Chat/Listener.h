#pragma once
#include "IPpool.h"
#include "Global.h"

class Listener
{
private:
	pcap_if_t * alldevs, *d;
	u_int i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	int res;
public:
	int FindAndPrint() {
		/* The user didn't provide a packet source: Retrieve the local device list */
		if (pcap_findalldevs_ex(const_cast<char*>(PCAP_SRC_IF_STRING), NULL, &alldevs, errbuf) == -1)
		{
			fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
			return 0;
		}

		/* Print the list */
		for (d = alldevs; d; d = d->next)
		{
			printf("%d. %s\n    ", ++i, d->name);

			if (d->description)
				printf(" (%s)\n", d->description);
			else
				printf(" (No description available)\n");
		}

		if (i == 0)
		{
			fprintf(stderr, "No interfaces found! Exiting.\n");
			return 0;
		}

		return i;
	}

	pcap_t *GetInterfaceByNumber(u_int inum) {
		pcap_t *fp;
		if (inum < 1 || inum > i)
		{
			printf("\nInterface number out of range.\n");

			/* Free the device list */
			pcap_freealldevs(alldevs);
			
		}

		/* Jump to the selected adapter */
		for (d = alldevs, i = 0; i< inum - 1; d = d->next, i++);

		/* Open the device */
		if ((fp = pcap_open(d->name,
			100 /*snaplen*/,
			PCAP_OPENFLAG_PROMISCUOUS /*flags*/,
			20 /*read timeout*/,
			NULL /* remote authentication */,
			errbuf)
			) == NULL)
		{
			fprintf(stderr, "\nError opening adapter\n");
		}

		return fp;
	}

	void Listen(pcap_t *fp, short inum) {
		struct pcap_pkthdr *header;
		std::array<u_char, 4> IpBuf;
		std::array<u_char, 4> ILocalIP = GetIP().at(inum-1);
		const u_char *pkt_data;
		while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0){
			if (res == 0)
				continue;
			/* Timeout elapsed */


			if (pkt_data[23] == 0x01 /*ICMP*/ &&
				pkt_data[34] == 0x08 /*request*/) {

				g_mt.lock();
				IpBuf[0] = pkt_data[26];
				IpBuf[1] = pkt_data[27];
				IpBuf[2] = pkt_data[28];
				IpBuf[3] = pkt_data[29];
				g_IPpool.insert(IpBuf);
				g_mt.unlock();
				if (IpBuf != ILocalIP){

					for (int i = 26; i < 30; i++) {
						std::cout << (int)pkt_data[i];
						if (i != 29)
							std::cout << ".";
					}

					std::cout << " : ";

					for (int i = 42; i < header->len; i++) {
						std::cout << pkt_data[i];
					}
					std::cout << std::endl;
				}
		
			}
		}
	}
};

