#include<iostream>
#include<climits>  
#include <bits/stdc++.h>    
using namespace std;
#define V 5
int minimumDist(int dist[], bool Tset[]) 
{
	int min=INT_MAX,index;         
	for(int i=0;i<6;i++) 
	{
		if(Tset[i]==false && dist[i]<=min)      
		{
			min=dist[i];
			index=i;
		}
	}
	return index;
}

void Dijkstra(int graph[6][6],int src)
{
	int dist[6];                            
	bool Tset[6];  
	for(int i = 0; i<6; i++)
	{
		dist[i] = INT_MAX;
		Tset[i] = false;	
	}
	dist[src] = 0;            
	for(int i = 0; i<6; i++)                           
	{
		int m=minimumDist(dist,Tset);
		Tset[m]=true;
		for(int i = 0; i<6; i++)                  
		{
			if(!Tset[i] && graph[m][i] && dist[m]!=INT_MAX && dist[m]+graph[m][i]<dist[i])
				dist[i]=dist[m]+graph[m][i];
		}
	}
	cout<<"Vertex\t\tDistance from source"<<endl;
	for(int i = 0; i<6; i++)                      
	{ 
		char str=65+i;
		cout<<str<<"\t\t\t"<<dist[i]<<endl;
	}
}

class DSU { 
	int* parent; 
	int* rank; 
public: 
	DSU(int n) 
	{ 
		parent = new int[n]; 
		rank = new int[n]; 
		for (int i = 0; i < n; i++) { 
			parent[i] = -1; 
			rank[i] = 1; 
		} 
	} 
	int find(int i) 
	{ 
		if (parent[i] == -1) 
			return i; 

		return parent[i] = find(parent[i]); 
	} 
	void unite(int x, int y) 
	{ 
		int s1 = find(x); 
		int s2 = find(y); 
		if (s1 != s2) { 
			if (rank[s1] < rank[s2]) { 
				parent[s1] = s2; 
			} 
			else if (rank[s1] > rank[s2]) { 
				parent[s2] = s1; 
			} 
			else { 
				parent[s2] = s1; 
				rank[s1] += 1; 
			} 
		} 
	} 
}; 
class Graph { 
	vector<vector<int> > edgelist; 
	int V1; 
public: 
	Graph(int V1) { this->V1 = V1; } 
	void addEdge(int x, int y, int w) 
	{ 
		edgelist.push_back({ w, x, y }); 
	} 
	void kruskals_mst() 
	{ 
		sort(edgelist.begin(), edgelist.end()); 
		DSU s(V1); 
		int ans = 0; 
		cout << "Following are the edges in the constructed MST"<< endl; 
		for (auto edge : edgelist) { 
			int w = edge[0]; 
			int x = edge[1]; 
			int y = edge[2]; 
			if (s.find(x) != s.find(y)) { 
				s.unite(x, y); 
				ans += w; 
				cout << x << " -- " << y << " == " << w 
					<< endl; 
			} 
		} 
		cout << "Minimum Cost Spanning Tree: " << ans<<endl; 
	} 
}; 

int minKey(int key[], bool mstSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}
void printMST(int parent[], int graph[V][V])
{
	cout << "Edge \tWeight\n";
	for (int i = 1; i < V; i++)
		cout << parent[i] << " - " << i << " \t"
			<< graph[i][parent[i]] << " \n";
}
void primMST(int graph[V][V])
{
	int parent[V];
	int key[V];
	bool mstSet[V];
	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;
	key[0] = 0;
	parent[0] = -1;
	for (int count = 0; count < V - 1; count++) {
		int u = minKey(key, mstSet);
		mstSet[u] = true;
		for (int v = 0; v < V; v++)
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}
	printMST(parent, graph);
}

int main()
{
    int ch;
    int graph[6][6]={
                {0, 10, 20, 0, 0, 0},
                {10, 0, 0, 50, 10, 0},
                {20, 0, 0, 20, 33, 0},
                {0, 50, 20, 0, 20, 2},
                {0, 10, 33, 20, 0, 1},
                {0, 0, 0, 2, 1, 0}
            };
    int graph1[V][V] = { { 0, 2, 0, 6, 0 },
						{ 2, 0, 3, 8, 5 },
						{ 0, 3, 0, 0, 7 },
						{ 6, 8, 0, 0, 9 },
						{ 0, 5, 7, 9, 0 } };
    Graph g(4);
    while(1){
        cout<<"1) Dijikstra's Algorithm\n2) Krushkal's Algorithm\n3) Prim's Algorithm\n4) Exit\n";
        cout<<"Enter your choice: ";
        cin>>ch;
        switch (ch)
        {
            case 1:
                Dijkstra(graph,0);
                break;
            case 2: 
                g.addEdge(0, 1, 10); 
                g.addEdge(1, 3, 15); 
                g.addEdge(2, 3, 4); 
                g.addEdge(2, 0, 6); 
                g.addEdge(0, 3, 5); 
                // Function call 
                g.kruskals_mst(); 
                break;
                case 3:
                    primMST(graph1);
                    break;
                case 4:
                    exit(0);
            default:
                cout<<"Enter the valid choice !!"<<endl;
                break;
            }
        }
	return 0;	                        
}