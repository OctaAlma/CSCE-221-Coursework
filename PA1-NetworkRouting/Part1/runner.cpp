#include <iostream>
#include "NetworkRouter.h"

using std::cout, std::endl, std::string;

void EXPECT_EQ(string str1, string str2){
	cout << str1;
	cout << "\n should be equal to:\n\n";
	cout << str2;
	cout << "\n";
}

int main() {
	DoublyLinkedList dll;
	NetworkPacket n1("0","0","A","Hello!");
	NetworkPacket n2("0","0","B","Howdy!");
	NetworkPacket n3("10","5","C","");
	NetworkPacket n4("5","10","D","TAMU");
	NetworkPacket n5("50","10","E","TAMU");
	NetworkPacket n6("20","5","F","");
	NetworkPacket n7("5","50","G","Hello!");
	NetworkPacket n8("5","20","H","Goodbye");
	dll.insert(n1,0);
	dll.insert(n2,1);
	dll.insert(n3,0);
	dll.insert(n8,3);
	dll.insert(n4,1);
	dll.insert(n5,5);
	EXPECT_EQ(dll.toString(),"SRC: 10, DST: 5, CKS: C, Data: \n SRC: 5, DST: 10, CKS: D, Data: TAMU\n SRC: 0, DST: 0, CKS: A, Data: Hello!\n SRC: 0, DST: 0, CKS: B, Data: Howdy!\n SRC: 5, DST: 20, CKS: H, Data: Goodbye\n SRC: 50, DST: 10, CKS: E, Data: TAMU\n ");
	dll.remove(0);
	dll.remove(3);
	dll.remove(2);
	EXPECT_EQ(dll.toString(),"SRC: 5, DST: 10, CKS: D, Data: TAMU\n SRC: 0, DST: 0, CKS: A, Data: Hello!\n SRC: 50, DST: 10, CKS: E, Data: TAMU\n ");
	dll.insert(n4,1);
	dll.insert(n5,4);
	dll.insert(n6,2);
	dll.insert(n7,3);
	dll.remove(6);
	dll.remove(1);
	dll.remove(4);
	EXPECT_EQ(dll.toString(),"SRC: 5, DST: 10, CKS: D, Data: TAMU\n SRC: 20, DST: 5, CKS: F, Data: \n SRC: 5, DST: 50, CKS: G, Data: Hello!\n SRC: 0, DST: 0, CKS: A, Data: Hello!\n ");
	NetworkRouter net;

	net.receiveRequests(std::cin);
	net.processRequests();
	net.sendRequests(std::cout);

	return 0;
}