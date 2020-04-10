#include<iostream>
#include <string>
#include <sstream>

using namespace std;


// Two-way unordered cycled list without sentinel
struct Element{
    int value;
    Element* next;
    Element* prev;
};

struct List2W{
    Element* head;
};

void init(List2W& l){
    l.head = NULL;
}

void insertHead(List2W& l, int x){
    Element* newel = new Element;

    newel->value = x;

    if (l.head == NULL)
    {
        newel->next = newel;
        newel->prev = newel;
    }
    else
    {
        newel->next = l.head;
        newel->prev = l.head->prev;
        l.head->prev->next = newel;
        l.head->prev = newel;
    }

    l.head = newel;
}

bool deleteHead(List2W& l, int &value){
    Element* oldel = l.head;

    if (oldel == NULL)
        return false;

    oldel->next->prev = oldel->prev;
    oldel->prev->next = oldel->next;

    value = oldel->value;

    if (l.head != l.head->next)
        l.head = l.head->next;
    else
        l.head = NULL;

    delete oldel;

    return true;
}

void insertTail(List2W& l, int x){
    Element* newel = new Element;

    newel->value = x;

    if (l.head == NULL)
    {
        newel->next = newel;
        newel->prev = newel;

        l.head = newel;
    }
    else
    {
        newel->next = l.head;
        newel->prev = l.head->prev;
        l.head->prev->next = newel;
        l.head->prev = newel;
    }
}

bool deleteTail(List2W& l, int &value){
    if (l.head == NULL)
        return false;

    Element* oldel = l.head->prev;

    oldel->next->prev = oldel->prev;
    oldel->prev->next = oldel->next;

    value = oldel->value;

    if (l.head == l.head->next)
        l.head = NULL;

    delete oldel;

    return true;
}

int findValue(List2W& l, int value){
    if (l.head == NULL) return 0;

    int answer = 0;
    Element* current = l.head;

    do
    {
        if (current->value == value)
            return answer;

        answer++;
        current = current->next;
    } while (current != l.head);

	return -1;
}

void removeAllValue(List2W& l, int value){
    if (l.head == NULL) return;

    Element* current = l.head->next;

    while (current != l.head)
    {
        if (current->value == value)
        {
            Element* oldel = current;

            current = current->next;

            oldel->next->prev = oldel->prev;
            oldel->prev->next = oldel->next;

            delete oldel;
        }
        else current = current->next;
    }

    if (l.head->value == value)
        deleteHead(l, value);
}

void showListFromHead(List2W& l){
    if (l.head != NULL)
    {
        Element* current = l.head;

        do
        {
            cout << current->value << ",";
            current = current->next;
        } while (current != l.head);
    }

    cout << endl;
}

void showListFromTail(List2W& l){
    if (l.head != NULL)
    {
        Element* current = l.head->prev;

        do
        {
            cout << current->value << ",";
            current = current->prev;
        } while (current != l.head->prev);
    }

    cout << endl;
}

void removeOddPosition(List2W& l){
    if (l.head == NULL) return;

    Element* current = l.head->next;
    int pos = 1;

    while (current != l.head)
    {
        if (pos % 2 == 1)
        {
            Element* oldel = current;

            current = current->next;

            oldel->next->prev = oldel->prev;
            oldel->prev->next = oldel->next;

            delete oldel;
        }
        else current = current->next;
        pos++;
    }
}

void removeOddValues(List2W& l){
    if (l.head == NULL) return;

    Element* current = l.head->next;

    while (current != l.head)
    {
        if (current->value % 2 == 1)
        {
            Element* oldel = current;

            current = current->next;

            oldel->next->prev = oldel->prev;
            oldel->prev->next = oldel->next;

            delete oldel;
        }
        else current = current->next;
    }

    int value;
    if (l.head->value % 2 == 1)
        deleteHead(l, value);
}

void clearList(List2W& l){
    int value;
    while (l.head != NULL)
        deleteHead(l, value);
}

void addList(List2W& l1,List2W& l2){
    if (l1.head == l2.head)
        return;

    int value;

    while (l2.head != NULL)
    {
        deleteHead(l2, value);
        insertTail(l1, value);
    }
}

void duplicate(List2W& l){
    if (l.head == NULL) return;

    Element* current = l.head;

    do
    {
        Element* newel = new Element;

        newel->value = current->value;

        newel->next = current->next;
        newel->prev = current;
        current->next->prev = newel;
        current->next = newel;

        current = current->next->next;

    } while (current != l.head);
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

		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}


		// zero-argument command
		if(isCommand(command,"DH")) //*
		{
			int retValue;
			bool retBool=deleteHead(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if(isCommand(command,"DT")) //*
		{
			int retValue;
			bool retBool=deleteTail(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
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

		if(isCommand(command,"FV")) //*
		{
			int ret;
			ret=findValue(list[currentL],value);
			cout << ret << endl;
			continue;
		}

		if(isCommand(command,"RV")) //*
		{
			removeAllValue(list[currentL],value);
			continue;
		}

        if(isCommand(command,"OP")) //*
		{
			removeOddPosition(list[currentL]);
			continue;
		}
		if(isCommand(command,"OV")) //*
		{
			removeOddValues(list[currentL]);
			continue;
		}


		if(isCommand(command,"AD")) //*
		{
			addList(list[currentL],list[value]);
			continue;
		}

		if(isCommand(command,"CH")) //*
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IH")) //*
		{
			insertHead(list[currentL],value);
			continue;
		}

		if(isCommand(command,"IT")) //*
		{
			insertTail(list[currentL],value);
			continue;
		}

		if(isCommand(command,"DP")) //*
		{
			duplicate(list[currentL]);
			continue;
		}

		if(isCommand(command,"GO")) //*
		{
			list=new List2W[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}
