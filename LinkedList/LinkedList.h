#pragma once
#include <iostream>
using namespace std;

class Node;

class DoublyLinkedList
{
private:
	Node* head;
	Node* tail;
	int numberofnodes;

public:
	DoublyLinkedList();
	~DoublyLinkedList();
	bool remove(int pos);
	bool add(Node* data, int pos);
	bool replace(Node* oldnode, Node* newnode);
	bool addtail(Node* data);
	//bool remove(int pos);
	//bool replace(Node* oldnode, Node* newnode);
	//int search(Node* data);
	//Node* nodeAt(int pos);
	void display_forward();
	void display_backward();
	//void display_backward();
	//int size();
};

class Node
{
private:
	
public:
	int data;
	int nodeNumber;
	Node* next;
	Node* prev;
	Node();
	//int getData();
	//void setData(int data);
	//Node* getNext();
	//void setNext(Node* next);
	//Node* getPrev();
	//void setPrev(Node* prev);
};