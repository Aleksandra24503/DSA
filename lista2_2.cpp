#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element{
    int value;
    Element* next;
};

struct List{
    Element* head;
    Element* tail;
};

void init(List& l){
    l.head = NULL;
    l.tail = NULL;
}

void insertHead(List& l, int x){
    Element* new_element = new Element;

    new_element->next = l.head;
    new_element->value = x;

    l.head = new_element;
    if (l.tail == NULL)
        l.tail = new_element;
}

bool deleteHead(List& l, int &oldHead){
    if (l.head == NULL)
        return false;

    Element* old_element = l.head;
    l.head = l.head->next;

    oldHead = old_element->value;
    delete old_element;

    if (l.head == NULL)
        l.tail = NULL;

    return true;
}

void insertTail(List& l, int x){
    Element* new_element = new Element;

    new_element->value = x;
    new_element->next = NULL;

    if (l.head == NULL)
    {
        l.head = new_element;
        l.tail = new_element;
    }
    else
    {
        l.tail->next = new_element;
        l.tail = new_element;
    }
}

bool deleteTail(List& l, int &oldTail){
	if (l.head == NULL)
        return false;
    if (l.head == l.tail)
    {
        oldTail = l.head->value;

        delete l.head;

        l.head = NULL;
        l.tail = NULL;

        return true;
    }

    Element* new_tail = l.head;

    while (new_tail->next != l.tail)
        new_tail = new_tail->next;

    new_tail->next = NULL;

    oldTail = l.tail->value;

    delete l.tail;

    l.tail = new_tail;

    return true;
}

int findPosOfValue(List& l, int value){
    int answer = 0;
    Element* current = l.head;

    while (current != NULL)
    {
        if (current->value == value)
            return answer;

        current = current->next;
        answer++;
    }

	return -1;
}

bool deleteValue(List& l, int value){
    if (l.head == NULL)
        return false;
    if (l.head->value == value)
    {
        int oldHead;
        deleteHead(l, oldHead);

        return true;
    }

    Element* current = l.head;

    while (current->next != NULL && current->next->value != value)
    {
        current = current->next;
    }

    if (current->next == NULL)
        return false;

    if (current->next->next == NULL)
    {
        int oldTail;
        deleteTail(l, oldTail);

        return true;
    }

    Element* old_element = current->next;

    current->next = current->next->next;

    delete old_element;

    return true;
}

bool atPosition(List& l, int pos, int &value){
    if (l.head == NULL)
        return false;

    Element* current = l.head;

    for (int i = 0; i < pos; i++)
    {
        current = current->next;

        if (current == NULL)
            return false;
    }

    value = current->value;

	return true;
}

void showListFromHead(List& l){
    Element* current = l.head;

    while (current != NULL)
    {
        cout << current->value << ",";
        current = current->next;
    }
    cout << endl;
}

void clearList(List& l){
    while(l.head != NULL)
    {
        int oldHead;
        deleteHead(l, oldHead);
    }
}

bool deletesecond(List& l, int& value)
{
    int v1, v2;
    bool b1, b2;

    b1 = deleteHead(l, v1);
    if (b1 == false) return false;
    b2 = deleteHead(l, v2);
    insertHead(l, v1);

    value = v2;
    return b2;
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
	List *list=NULL;
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
		if(isCommand(command,"DH"))
		{
			int retValue;
			bool retBool=deleteHead(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if(isCommand(command,"DT"))
		{
			int retValue;
			bool retBool=deleteTail(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"SH"))
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL"))
		{
			clearList(list[currentL]);
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"FP"))
		{
			int ret;
			ret=findPosOfValue(list[currentL],value);
			cout << ret << endl;
			continue;
		}

		if(isCommand(command,"DV"))
		{
			showBool(deleteValue(list[currentL],value));
			continue;
		}


		if(isCommand(command,"AT"))
		{
			int retValue;
			bool retBool=atPosition(list[currentL],value,retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IH"))
		{
			insertHead(list[currentL],value);
			continue;
		}

		if(isCommand(command,"IT"))
		{
			insertTail(list[currentL],value);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}
