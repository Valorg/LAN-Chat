#include "Listener.h"

#include "Sender.h"

void ListenerTreadFunction(pcap_t *fp) {
	Listener lis;
	lis.Listen(fp);
}

void SenderTreadFunction() {
	boost::asio::io_service io_service;
	Sender sen(io_service);
	string Msg;
	for (;;) {
		cin >> Msg;
		for (auto iter = g_IPpool.begin(); iter != g_IPpool.end(); iter++) {
			sen.Send(Msg, string("192.168.1." + to_string(*iter)));
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Listener lis;
	u_int inum;
	int InterfaceCount = lis.FindAndPrint();
	do {
		cout << "Enter the interface number:" << endl;
		cin >> inum;
	} while (inum < 1 || inum > InterfaceCount);

	pcap_t *fp = lis.GetInterfaceByNumber(inum);
	thread ListenerThread(ListenerTreadFunction, fp);
	
	boost::asio::io_service io_service;
	Sender sen(io_service);
	sen.SendHiEveryone();
	
	cout << "Say:" << endl;

	thread SenderThread(SenderTreadFunction);
	ListenerThread.join();
	SenderThread.detach();

	system("pause");
	return 0;
}

