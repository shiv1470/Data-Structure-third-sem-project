#include<bits/stdc++.h>
using namespace std;
/*
Thing left to do:
1. Find Fare Function in network
2. A Function to do String Matching and return a score
score = length(Largest common substring) * (max(len(s1),len(s2)) - min of index of two first mathching strings)
3. Add Comments
4.(Optional) While printing path, Print "Interchange" on change of color.
-Format of storing:
 first line contains number of station:
 then each line contain name of Station Id , station , color of station , traffic
 Then a line contains number of trains between Stations:
 then each line contains SID of U , SID of V , Time , Distance
-Fare is based on distance.
-Remember to save and use all name without space or figure out a way using puts/gets
*/

int k=0;
struct edge
{
    int v2;
    int time;
    int distance;
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
    station(ifstream &fname)
    {
        fname>>sid>>name>>color>>traffic;
    }
    void settraffic(int x)
    {
        traffic=x;
    }
    int gettraffic()
    {
        return this->traffic;
    }
};
class network
{
    public:
    int numofstation; //nodes
    int numoftrains; //edges
    vector <station> node;
    vector < vector <struct edge> >  graph;
    network(int n=1)
    {
        int x,y,t;
        numofstation=n;
        numoftrains=0;
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
            numoftrains+=2;
        }
        while(x>0 or y>0 );
    }
    network(ifstream &fname)
    {
        int n,m;
        fname>>n;
        numofstation=n;
        k=n;
        for(int x=1;x<=n;x++)
        {
            station temp(fname);
            node.push_back(temp);
        }
        fname>>m;
        numoftrains=m;
        graph.resize(n+1);
        for(int x=1;x<=m;x++)
        {
            int u,v,t,d;
            fname>>u>>v>>t>>d;
            struct edge e1,e2;
            e1.v2=v;e1.time=t;e1.distance=d;
            graph[u].push_back(e1);
        }
      //  cout<<"divyanshu"<<node.size()<<endl;
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
        numoftrains+=2;
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
        numoftrains+=2;
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
    int printPath(int parent[], int j,int time[],int cnt)
    {
    //Time below is supposed to be added in system time to get approx arrival time
    if (parent[j] == - 1)
    {
        cout<<"Station Id     Station Name      Station Color    Time\n";
        cout<<j+1<<"             "<<node[j].name<<"    "<<node[j].color<<"      "<<time[j]<<"\n";
        return cnt;
    }
    printPath(parent, parent[j],time,cnt+1);
    cout<<j+1<<"             "<<node[j].name<<"    "<<node[j].color<<"      "<<time[j]<<"\n";
    }

int LCSubStr(string X, string Y, int m, int n)
{
    // Create a table to store lengths of longest common suffixes of
    // substrings.   Notethat LCSuff[i][j] contains length of longest
    // common suffix of X[0..i-1] and Y[0..j-1]. The first row and
    // first column entries have no logical meaning, they are used only
    // for simplicity of program
    int LCSuff[m+1][n+1];
    int idx=0;
    int result = 0;  // To store length of the longest common substring
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                LCSuff[i][j] = 0;

            else if (X[i-1] == Y[j-1])
            {
                idx+=max(i,j);
                LCSuff[i][j] = LCSuff[i-1][j-1] + 1;
                result = max(result, LCSuff[i][j]);
            }
            else LCSuff[i][j] = 0;
        }
    }
    return result*idx;
}
    string findmatchingstation(string nme)
    {
        int mxscore=-1,i,j;
        string ans;
        for(i=0;i<numofstation;i++)
        {
            j=LCSubStr(nme,node[i].name,nme.length(),node[i].name.length());
            if(j > mxscore)
            {
                mxscore=j;
                ans=node[i].name;
            }
        }
        return ans;
    }
    public:
    void findroute()
    {
        int i,j,k=0;
        char ch='N';
        string source,destination,temp;int sourceid,destid;
        while(ch!='Y')
        {
            cout<<"\nEnter Name of starting station:";
            cin>>source;
            temp=findmatchingstation(source);
            if(temp==source)
            {
                ch='Y';
            }
            else
            {
                cout<<"\nDid You mean: '"<<temp<<"'. (Y/N) ";
                cin>>ch;
                if(ch!='Y')
                {
                    ch='N';
                }
                else
                {
                    source=temp;
                }
            }
        }
        ch='N';
        while(ch!='Y')
        {
            cout<<"Enter Name of destination: ";
            cin>>destination;
            temp=findmatchingstation(destination);
            if(temp==destination)
            {
                ch='Y';
            }
            else
            {
                cout<<"\nDid You mean: '"<<temp<<"'. (Y/N) ";
                cin>>ch;
                if(ch!='Y')
                {
                    ch='N';
                }
                else
                {
                    destination=temp;
                }
            }
        }
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
            int u = minDistance(time, sptset);
             // Mark the picked vertex
            // as processed
            sptset[u] = true;
            // Update dist value of the
            // adjacent vertices of the
            // picked vertex.
            for (int v = 0; v < numofstation; v++)
            {
            if (!sptset[v] && findweight(u+1,v+1) && time[u] + findweight(u+1,v+1) < time[v])
            {
                parent[v] = u;
                time[v] = time[u] + findweight(u+1,v+1);
            }
            }

    }
    cout<<"Minimum Time ="<<time[destid-1]<<endl;
    cout<<"Path to follow:\n";
    int xtra = printPath(parent,destid-1,time,0);
    }
    int FindFare(string src , string dest)
    {
        int fare=0;

        return fare;
    }

};
network *dmrc;
void loaddata()
{
    ifstream in;
    in.open("dmrcorp.txt");
    dmrc = new network(in);
    in.close();
}
void savefile()
{
    ofstream out;
    out.open("dmrcorp.txt");
    out<<dmrc->numofstation<<endl;
    for(int x=0;x<dmrc->numofstation;x++)
    {
        out<<dmrc->node[x].sid<<" "<<dmrc->node[x].name<<" "<<dmrc->node[x].color<<" "<<dmrc->node[x].gettraffic()<<endl;
    }
    out<<dmrc->numoftrains<<endl;
    int i,j,k,n=dmrc->numofstation;
    for(i=0;i<=n;i++)
    {
        for(j=0;j<dmrc->graph[i].size();j++)
        {
            out<<i<<" "<<dmrc->graph[i][j].v2<<" "<<(dmrc->graph[i][j]).time<<" "<<(dmrc->graph[i][j]).distance<<endl;
        }
    }
    out.close();
}
void newdata()
{
    int n;
    cout<<"Enter Number of stations:";
    cin>>n;
    dmrc=new network(n);
}
void adminview()
{
    int ch1,ch2;
    do
    {
        cout<<"Press 1 for Loading the last saved data\nPress 2 for Opening new File\nPress 0 for exit";
        cin>>ch1;
        switch(ch1)
        {
        case 1:
            loaddata();
            do
            {
                cout<<"Press 1 for seeing the network\nPress 2 for Adding a new Station\nPress 3 for Adding a new Train\nPress 4 for Saving(This will overwrite existing data)\nPress 0 for Exit";
                cin>>ch2;
                switch(ch2)
                {
                case 1:
                    dmrc->shownetwork();
                    break;
                case 2:
                    dmrc->addnode();
                    break;
                case 3:
                    dmrc->addedge();
                    break;
                case 4:
                    savefile();
                    break;
                case 0:
                    return;
                default:
                    cout<<"Choose Correct Option\n";
                }
            }while(ch2>0);
            break;
        case 2:
            newdata();
            cout<<"Created New Network";
            do
            {
                cout<<"Press 1 for seeing the network\nPress 2 for Adding a new Station\nPress 3 for Adding a new Train\nPress 4 for Saving\nPress 0 for Exit";
                cin>>ch2;
                switch(ch2)
                {
                case 1:
                    dmrc->shownetwork();
                    break;
                case 2:
                    dmrc->addnode();
                    break;
                case 3:
                    dmrc->addedge();
                    break;
                case 4:
                    savefile();
                    break;
                case 0:
                    break;
                default:
                    cout<<"Choose Correct Option\n";
                }
            }while(ch2>0);
            break;

                case 0:
                    break;
                default:
                    cout<<"Choose correct option";
        }
    }while(ch1>0);
}
void userview()
{
    loaddata();
    int ch;
    do
    {
    cout<<"Press 1 to view Route between 2 Station\nPress 2 to Know Fare between 2 station\nPress 3 to View Network\nPress 0 to Exit\n";
    cin>>ch;
        switch(ch)
        {
            case 1:
                dmrc->findroute();
                break;
            case 2:
                {
                 string src,des;
                cout<<"\nEnter Source Station:";
                cin>>src;
                cout<<"\nEnter Destination:";
                cin>>des;
                cout<<"Total Fare = "<<dmrc->FindFare(src,des)<<endl;
                }
                break;
            case 3:
                dmrc->shownetwork();
                break;
            case 0:
                break;
            default:
                cout<<"Enter Correct Option and try again!\n";
        }
    }
    while(ch>0);
}
int main()
{
    int ch=0;
    do
    {
    cout<<"Welcome!\n Press 1 For Admin View\n Press 2 For User View\n Press 0 For Exit\n";
    cin>>ch;
    switch(ch)
    {
    case 1:
        adminview();
        break;
    case 2:
        userview();
        break;
    case 0:
        return 0;
    default:
        cout<<"Choose Correct Option and try again!\n";
    }
    }while(ch>0);
    return 0;
}
