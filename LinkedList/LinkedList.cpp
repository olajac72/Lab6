// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "LinkedList.h"

int main()
{
    DoublyLinkedList dll;

    Node* newnode;

    newnode = new Node();
    newnode->data = 10;
    //dll.addtail(newnode);
    dll.add(newnode, 1);
    
    newnode = new Node();
    newnode->data = 20;
    //dll.addtail(newnode);
    dll.add(newnode, 2);

    newnode = new Node();
    newnode->data = 30;
    //dll.addtail(newnode);
    dll.add(newnode, 1);


    dll.display_forward();

}

DoublyLinkedList::~DoublyLinkedList()
{
    Node* current, * currentDel;

    current = head->next;


    while (current != tail)
    {
        currentDel = current;
        current = current->next;

        delete currentDel;
    }


    delete head;
    delete tail;
}

DoublyLinkedList::DoublyLinkedList()
{
    head = new Node();
    tail = new Node();

    head->nodeNumber = 0;

    head->prev = nullptr;
    head->next = tail;

    tail->nodeNumber = -1;

    tail->next = nullptr;
    tail->prev = head;

    numberofnodes = 0;

}

bool DoublyLinkedList::addtail(Node* data)
{
    data->nodeNumber = tail->prev->nodeNumber + 1;

    data->prev = tail->prev;
    data->next = tail;

    data->prev->next = data;
    tail->prev = data;

    cout << "Data : " << data->data << endl;
    
    numberofnodes++;
    
    return true;
}

bool DoublyLinkedList::add(Node* data, int pos)
{
    Node* current;
    int currentindex;

    currentindex = 1;
    current = head->next;

    if (pos > numberofnodes + 1)
        return false;
    else if (pos == numberofnodes + 1)
    {
        data->nodeNumber = tail->prev->nodeNumber + 1;

        data->prev = tail->prev;
        data->next = tail;

        data->prev->next = data;
        tail->prev = data;
    }
    else
    {

        while (currentindex != pos)
        {
            current = current->next;
            currentindex++;
        }

        data->prev = current->prev;
        data->next = current;
        data->prev->next = data;
        current->prev = data;

    }

    numberofnodes++;
    cout << "Data : " << data->data << endl;
    return true;
}

void DoublyLinkedList::display_forward()
{
    Node* current;
    current = head->next;

    while (current != tail)
    {
        cout << "Data for node nr: " << current->nodeNumber << " is: "  << current->data << endl;
        current = current->next;
     }
 }

Node::Node()
{

}