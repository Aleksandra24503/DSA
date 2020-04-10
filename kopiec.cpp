#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Heap{
	int *arr;
	int size;
	int pos;
};

void init(Heap& h, int size){
    h.size = size;
    h.pos = 0;
    h.arr = new int[size];
}

inline int parent(int p)
{
    return (p-1)/2;
}

inline int left(int p)
{
    return 2*p + 1;
}

inline int right(int p)
{
    return 2*p + 2;
}

void heap_up(Heap& h, int pos)
{
    while (pos != 0 && h.arr[parent(pos)] < h.arr[pos])
    {
        int t = h.arr[parent(pos)];
        h.arr[parent(pos)] = h.arr[pos];
        h.arr[pos] = t;

        pos = parent(pos);
    }
}

void heap_down(Heap &h, int pos)
{
    int largest = pos;

    if (left(pos) < h.pos && h.arr[left(pos)] > h.arr[pos])
        largest = left(pos);
    if (right(pos) < h.pos && h.arr[right(pos)] > h.arr[largest])
        largest = right(pos);

    if (pos != largest)
    {
        int tmp = h.arr[largest];
        h.arr[largest] = h.arr[pos];
        h.arr[pos] = tmp;

        heap_down(h, largest);
    }
}

void heapAdjustment(Heap &h){
    for (int i = (h.pos-1)/2; i >= 0; i--)
        heap_down(h, i);
}

void loadAndMakeHeap(Heap &h, int howMany){
    h.pos = howMany;
    for (int i = 0; i < howMany; i++)
        cin >> h.arr[i];
    heapAdjustment(h);
}


void add(Heap &h, int value){
    h.arr[h.pos] = value;
    h.pos++;

    heap_up(h, h.pos-1);
}


void makeSorted(Heap& h){
    int real_pos = h.pos;

    for (int i = h.pos-1; i > 0; i--)
    {
        int tmp = h.arr[i];
        h.arr[i] = h.arr[0];
        h.arr[0] = tmp;

        h.pos--;

        heap_down(h, 0);
    }

    h.pos = real_pos;
}

void show(Heap& h){
  for(int i=0;i<h.pos;i++)
  {
	  cout << h.arr[i] << ",";
  }
  cout << endl;
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
	Heap *heap;
	int currentH=0;
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
			show(heap[currentH]);
			continue;
		}

		if(isCommand(command,"MS")) //*
		{
			makeSorted(heap[currentH]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"IN")) //*
		{
			init(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"LD"))
		{
			loadAndMakeHeap(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"AD"))
		{
			add(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentH=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			heap=new Heap[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
