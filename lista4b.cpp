#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Element{
	int key;
	int value;
};

struct ElementLL{
	Element elem;
	ElementLL *next, *prev;
};

// Two-way ordered cycled list with sentinel
struct List2W{
	ElementLL *sentinel;
};

void init(List2W& l){
	l.sentinel=new ElementLL();
	l.sentinel->next=l.sentinel;
	l.sentinel->prev=l.sentinel;
}

void insertElem(List2W & l, Element el){
    ElementLL* curr = l.sentinel;

    while (curr->next != l.sentinel && curr->next->elem.key <= el.key)
        curr = curr->next;

    ElementLL* newel = new ElementLL;

    newel->next = curr->next;
    newel->prev = curr;
    newel->elem = el;

    curr->next->prev = newel;
    curr->next = newel;
}

bool findKey(List2W & l,int k, Element &el){
    ElementLL* curr = l.sentinel->next;

    while (curr != l.sentinel && curr->elem.key != k)
        curr = curr->next;

    if (curr == l.sentinel)
		return false;

    el = curr->elem;
    return true;
}

void removeAllKeys(List2W& l, int k){
    ElementLL* curr = l.sentinel->next;

    while (curr != l.sentinel && curr->elem.key != k)
        curr = curr->next;

    while (curr != l.sentinel && curr->elem.key == k)
    {
        ElementLL* del = curr;

        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;

        curr = curr->next;

        delete del;
    }
}

void showListFromHead(List2W& l){
    ElementLL* curr = l.sentinel->next;

    while (curr != l.sentinel)
    {
        cout << curr->elem.key << "(" << curr->elem.value << "),";
        curr = curr->next;
    }
    cout << endl;
}

void showListFromTail(List2W& l){
    ElementLL* curr = l.sentinel->prev;

    while (curr != l.sentinel)
    {
        cout << curr->elem.key << "(" << curr->elem.value << "),";
        curr = curr->prev;
    }
    cout << endl;
}

void clearList(List2W& l){
    ElementLL* curr = l.sentinel->next;

    while (curr != l.sentinel)
    {
        ElementLL* del = curr;

        curr = curr->next;

        delete del;
    }

    l.sentinel->next = l.sentinel->prev = l.sentinel;
}

void addList(List2W& l1,List2W& l2){

    if (l1.sentinel == l2.sentinel)
        return;

    ElementLL* c1 = l1.sentinel->next;
    ElementLL* c2 = l2.sentinel->next;

    while (c2 != l2.sentinel)
    {
        if (c1 == l1.sentinel || c1->elem.key > c2->elem.key)
        {
            ElementLL* mov = c2;

            c2 = c2->next;

            mov->next = c1;
            mov->prev = c1->prev;

            c1->prev->next = mov;
            c1->prev = mov;
        }
        else
        {
            c1 = c1->next;
        }
    }

    l2.sentinel->next = l2.sentinel->prev = l2.sentinel;
}

void dupList(List2W& l)
{
    ElementLL* curr = l.sentinel->next;

    while (curr != l.sentinel)
    {
        ElementLL* newel = new ElementLL;

        newel->next = curr->next;
        newel->prev = curr;
        newel->elem = curr->elem;

        curr->next->prev = newel;
        curr->next = newel;

        curr = curr->next->next;
    }
}

void delSecond(List2W& l)
{
    ElementLL* curr = l.sentinel->next->next;

    while (curr != l.sentinel && curr->prev != l.sentinel)
    {
        ElementLL* del = curr;

        curr = curr->next->next;

        del->next->prev = del->prev;
        del->prev->next = del->next;

        delete del;
    }
}

void showBool(bool val){
	if(val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	List2W *list;
	int currentL=0;
	int value;
	cout << "START" << endl;
	while(true){
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		// zero-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if(isCommand(command,"SH")) //*
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"ST")) //*
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL")) //*
		{
			clearList(list[currentL]);
			continue;
		}

		if(isCommand(command,"IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(list[currentL], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			removeAllKeys(list[currentL],value);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			insertElem(list[currentL],elem);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List2W[value];
			continue;
		}

		if(isCommand(command,"AD"))
		{
			addList(list[currentL],list[value]);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
