#include<bits/stdc++.h>
using namespace std;
int k=0;
struct edge
{
	int v2;
	int time;
};

class station
{
	int traffic;
	public:
	string name;
	int sid;
	string color;
	station()
	{
		++k;
		sid=k;
		traffic=1000;
		cout<<"Enter Name of Station "<<sid<<": ";
		cin>>name;
		cout<<"Enter Color: ";
		cin>>color;
	}
};
class network
{
	public:
	int numofstation;
	vector <station> node;
	vector < vector <struct edge> >  graph;
	network(int n=1)
	{
		int x,y,t;
		numofstation=n;
		for(x=1;x<=n;x++)
        {
            station temp;
            node.push_back(temp);
        }
		graph.resize(n+1);
		do
		{
			cout<<"Enter station Id of two station and time between which edge exist. Enter 0 0 0 to exit";
			cin>>x>>y>>t;
			struct edge e1,e2;
			e1.v2=x;
			e1.time=t;
			e2.v2=y;
			e2.time=t;
			graph[x].push_back(e2);
			graph[y].push_back(e1);
		}
		while(x>0 or y>0 );
	}
	void addnode()
	{
	    ++numofstation;
	    int x,t;
        station temp;
        node.push_back(temp);
        cout<<"Write the station id it connects with time(Ex: 1 5):";
        cin>>x>>t;
        struct edge t1,t2;
        t2.v2=x;
        t2.time=t;
        t1.v2=numofstation;
        t1.time=t;
        vector <struct edge> newnode;
        newnode.push_back(t2);
        graph[x].push_back(t1);
        graph.push_back(newnode);
	}
	void addedge()
	{
	    int x,y,t;
	    cout<<"Enter the Station Id it connects with time(Ex: 1 2 10):";
	    cin>>x>>y>>t;
	    struct edge e1,e2;
	    e1.v2=x;e1.time=t;
	    e2.v2=y;e2.time=t;
	    graph[y].push_back(e1);
	    graph[x].push_back(e2);
	}
	void shownetwork()
	{
		int i,j;
		for(i=0;i<numofstation;i++)
		{
			cout<<node[i].name<<"->";
			for(j=0;j<graph[i+1].size();j++)
			{
				cout<<node[graph[i+1][j].v2 -1].name<<"->";
			}
			cout<<endl;
		}
	}
	private:
	int minDistance(int dist[], bool sptSet[])
	{
    // Initialize min value
    int min = 100000, min_index;

    for (int v = 0; v < numofstation; v++)
        if (sptSet[v] == false &&  dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
	}
	int findweight(int u,int v)
	{
		int i,j;
		for(i=0;i<graph[u].size();i++)
		{
			if(graph[u][i].v2==v)
			{
				return graph[u][i].time;
			}
		}
		return 0;
	}
	void printPath(int parent[], int j,int time[])
	{
    //Time below is supposed to be added in system time to get approx arrival time
    if (parent[j] == - 1)
    {
        cout<<"Station Id     Station Name      Station Color    Time\n";
        cout<<j+1<<"             "<<node[j].name<<"    "<<node[j].color<<"      "<<time[j]<<"\n";
        return;
    }
    printPath(parent, parent[j],time);
    cout<<j+1<<"             "<<node[j].name<<"    "<<node[j].color<<"      "<<time[j]<<"\n";
    }
	public:
	void findroute()
	{
		int i,j,k;
		string source,destination;int sourceid,destid;
		cout<<"Enter Name of starting station:";
		cin>>source;
		cout<<"Enter Name of destination: ";
		cin>>destination;
		for(i=0;i<numofstation;i++)
		{
			if(node[i].name==source)
			{
				sourceid=i+1;
			}
			if(node[i].name==destination)
			{
				destid=i+1;
			}
		}
		int time[numofstation];
		bool sptset[numofstation];
		int parent[numofstation];
		parent[sourceid-1]=-1;
		for(i=0;i<numofstation;i++)
		{
			time[i]=100000;
			sptset[i]=false;
		}
		time[sourceid-1]=0;
		for (int count = 0; count < numofstation - 1; count++)
    	{
        	// Pick the minimum distance
        	// vertex from the set of
        	// vertices not yet processed.
        	// u is always equal to src
        	// in first iteration.
        	int u = minDistance(time, sptset);
  		//	cout<<u<<" ";
 	        // Mark the picked vertex
        	// as processed
        	sptset[u] = true;

        	// Update dist value of the
        	// adjacent vertices of the
        	// picked vertex.
        	for (int v = 0; v < numofstation; v++)
            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            {
		//	cout<<endl<<"Findweight("<<u<<","<<v<<") = "<<findweight(u,v)<<endl;
            if (!sptset[v] && findweight(u+1,v+1) && time[u] + findweight(u+1,v+1) < time[v])
            {
                parent[v] = u;
                time[v] = time[u] + findweight(u+1,v+1);
        	}
			}

    }
	cout<<"Minimum Time ="<<time[destid-1]<<endl;
	cout<<"Path to follow:\n";
	printPath(parent,destid-1,time);
	}
};


int main()
{
	network dmrc(2);
	dmrc.shownetwork();
	dmrc.addnode();
	dmrc.addedge();
	dmrc.shownetwork();
	dmrc.findroute();
	return 0;
}



