#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int get_local_ip(int *ip) {
	char hostname[128];
	int ret = gethostname(hostname, sizeof(hostname));
	if (ret == -1) {
		return -1;
	}
	struct hostent *hent;
	hent = gethostbyname(hostname);
	if (NULL == hent) {
		return -1;
	}
	*ip = ntohl(((struct in_addr *)hent->h_addr)->s_addr);
	return 0;
}

int main() {
	int ip = 0;
	int ret = get_local_ip(&ip);
	if (ret == 0) {
		cout << ip << endl;
        cout << (ip / 256 / 256 / 256) << '.';
        cout << (ip / 256 / 256 & 255) << '.';
        cout << (ip / 256 & 255) << '.';
        cout << (ip & 255) << endl;
	} else {
		cerr << "wrong" << endl;
	}
	return 0;
}