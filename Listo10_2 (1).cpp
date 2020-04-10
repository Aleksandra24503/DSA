#include<iostream>
#include<string.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define INFINITY 10000000

struct Graph{
    int n;
    vector<pair<int, double> > *v;
};

void loadGraph(Graph &g, int n, int m){
    g.n = n;
    g.v = new vector<pair<int, double> >[n];

    for (int i = 0; i < m; i++)
    {
        int u, v;
        double w;

        cin >> u >> v >> w;
        g.v[u].push_back(make_pair(v, w));
    }

    for (int i = 0; i < n; i++)
        sort(g.v[i].begin(), g.v[i].end());
}

void insertEdge(Graph &g, int u, int v, double weight){
    int a = 0;
    int b = g.v[u].size() - 1;

    while (a <= b)
    {
        int s = (a + b) / 2;

        if (g.v[u][s].first == v)
        {
            g.v[u][s].second = weight;
            return;
        }
        else if (g.v[u][s].first > v)
            b = s - 1;
        else
            a = s + 1;
    }

    g.v[u].push_back(make_pair(v, weight));

    int i = g.v[u].size() - 1;

    while (i > 0 && g.v[i] < g.v[i-1])
    {
        swap(g.v[i], g.v[i-1]);
        i--;
    }
}

bool findEdge(Graph &g, int u, int v, double &weight){
    int a = 0;
    int b = g.v[u].size() - 1;

    while (a <= b)
    {
        int s = (a + b) / 2;

        if (g.v[u][s].first == v)
        {
            weight = g.v[u][s].second;
            return true;
        }
        else if (g.v[u][s].first > v)
            b = s -1 ;
        else
            a = s + 1;
    }
    return false;
}

void showAsMatrix(Graph &g){
    for (int i = 0; i < g.n; i++)
    {
        int indx = 0;

        for (int j = 0; j < g.n; j++)
            if (i == j)
                cout << "0,";
            else if (indx < g.v[i].size() && g.v[i][indx].first == j)
            {
                cout << g.v[i][indx].second << ",";
                indx++;
            }
            else
                cout << "-,";

        cout << endl;
    }
}

void showAsArrayOfLists(Graph &g){
    for (int i = 0; i < g.n; i++)
    {
        cout << i << ":";

        for (int j = 0; j < g.v[i].size(); j++)
            cout << g.v[i][j].first << "(" << g.v[i][j].second << "),";

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

