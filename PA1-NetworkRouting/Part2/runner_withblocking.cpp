#include <iostream>
#include "NetworkRouter.h"

/*int main() {
	NetworkRouter net;
	//OPTIONAL:
	net.loadBlockedAddresses("blocked.txt");
	net.receiveRequests(std::cin);
	net.processRequests();
	net.sendRequests(std::cout);

	return 0;
}*/

Node<int>* reverseList(Node<int>* head){
	if (head == nullptr){
		return nullptr;
	}
	if (head->getNext() == nullptr){
		return head;
	}
	Node<int>* a = reverseList(head->getNext());
	a->setNext(head);
	head->setNext(nullptr);
	return head;
}

int main(){
	Node<int>* head;
	DoublyLinkedList<int> list;
	for (int i = 0; i < 5; i++){
		list.insert(i+1, list.getLength());
		std::cout << i << " ";
	}
	std::cout << std::endl;
	head = list.getFront();
	reverseList(head);
	for (int i = 0; i < 5; i++){
		head->getData();
		std::cout << i << " ";
		head = head->getNext();
	}

}