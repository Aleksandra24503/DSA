#include<iostream>
#include<string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

struct Graph{
    int n;
    double** edges;
};

void loadGraph(Graph &g, int n, int m){
    g.n = n;
    g.edges = new double*[n];
    for (int i = 0; i < n; i++)
    {
        g.edges[i] = new double[n];
        for (int j = 0; j < n; j++)
            g.edges[i][j] = INFINITY;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        double w;

        cin >> u >> v >> w;
        g.edges[u][v] = w;
    }
}

void insertEdge(Graph &g, int u, int v, double weight){
    g.edges[u][v] = weight;
}

bool findEdge(Graph &g, int u, int v, double &weight){
    weight = g.edges[u][v];
    return weight != INFINITY;
}

void showAsMatrix(Graph &g){
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g.n; j++)
            if (i == j)
                cout << "0,";
            else if (g.edges[i][j] == INFINITY)
                cout << "-,";
            else
                cout << g.edges[i][j] << ",";
        cout << endl;
    }
}

void showAsArrayOfLists(Graph &g){
    for (int i = 0; i < g.n; i++)
    {
        cout << i << ":";
        for (int j = 0; j < g.n; j++)
        {
            if (g.edges[i][j] != INFINITY)
                cout << j << "(" << g.edges[i][j] << "),";
        }
        cout << endl;
    }
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}


int main(){
	string line;
	string command;
	Graph *graph;
	int currentT=0;
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
		// zero-argument command
		if(isCommand(command,"SM"))
		{
			showAsMatrix(graph[currentT]);
			continue;
		}

		if(isCommand(command,"SA"))
		{
			showAsArrayOfLists(graph[currentT]);
			continue;
		}


		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"LG"))
		{
			int m;
			stream >> m;
			loadGraph(graph[currentT],value,m);
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int v;
			double w;
			stream >> v >> w;
			insertEdge(graph[currentT],value,v,w);
			continue;
		}

		if(isCommand(command,"FE"))
		{
			int v;
			stream >> v;
			double w;
			bool ret=findEdge(graph[currentT],value,v,w);

			if(ret)
				cout << w << endl;
			else
				cout << "false" << endl;
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentT=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			graph=new Graph[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}

