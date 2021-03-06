#include "IPpool.h"

void ListenerTreadFunction(pcap_t *fp, short inum) {
	Listener lis;
	lis.Listen(fp, inum);
}

void SenderTreadFunction() {
	boost::asio::io_service io_service;
	Sender sen(io_service);
	std::string Msg;
	for (;;) {
		std::cin >> Msg;
		sen.SendEveryone(Msg);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Listener lis;
	short inum;
	int InterfaceCount = lis.FindAndPrint();
	do {
		std::cout << "Enter the interface number:" << std::endl;
		std::cin >> inum;
	} while (inum < 1 || inum > InterfaceCount);

	pcap_t *fp = lis.GetInterfaceByNumber(inum);


	boost::asio::io_service io_service;
	Sender sen(io_service);
	sen.Scan();

	std::thread ListenerThread(ListenerTreadFunction, fp, inum);

	std::vector<std::array<u_char,4>> IPFromArp = GetArp();
	for (int i = 0; i < IPFromArp.size(); i++)
		g_IPpool.insert(IPFromArp.at(i));

	std::cout << "Say:" << std::endl;

	std::thread SenderThread(SenderTreadFunction);
	ListenerThread.join();
	SenderThread.detach();

	system("pause");
	return 0;
}

