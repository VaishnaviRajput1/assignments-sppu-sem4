#include<iostream>
#include<queue>
using namespace std;

class Graph
{
	private:
		int **adj;
		int ver;
		int *visited;
	public:
		Graph(int n)
		{
			ver=n;
			adj=new int*[n];
			for(int i=0;i<n;i++)
			{
				adj[i]=new int[n];
				for(int j=0;j<ver;j++)
				{
					adj[i][j]=0;
				}
			}
			for(int i=0;i<n;i++)
			{
				visited[i]=false;
			}
		}
		
		void reset()
		{
			for(int i=0;i<ver;i++)
			{
				visited[i]=false;
			}
			return ;
		}
		
		void addEdge(int ver1,int ver2,bool directional)
		{
			adj[ver1][ver2]=1;
			if(!directional)
			{
				adj[ver2][ver1]=1;
			}
		}
		void adj_list()
		{  	cout<<"adj list"<<endl;
			for(int i=0;i<ver;i++)
			{
			
				cout<<i<<": ";
				for(int j=0;j<ver;j++)
				{
					if(adj[i][j]==1)
					{
						cout<<j<<" ";
					}
				}
				cout<<endl;
			}
		}
		
		void BFS(int start)
		{
			queue<int>q;
			q.push(start);
			visited[start]=true;
			while(!q.empty())
			{
				int front=q.front();
				q.pop();
				cout<<front<<" ";
				for(int i=0;i<ver;i++)
				{
					if(adj[front][i]==1 && !visited[i])
					{
						q.push(i);
						visited[i]=true;
					}
				}
				
			}
		}		
		
		void DFS(int start)
		{
			cout<<start<<" ";
			this->visited[start]=true;
			for(int i=0;i<ver;i++)
			{
				if(adj[start][i]==1 && !visited[i])
				{
					DFS(i);
				}
			}
		}
		void degree()
		{   cout<<" degree"<<endl;
			for(int i=0;i<ver;i++)
			{
				cout<<i<<" :";
				int count=0;
				for(int j=0;j<ver;j++)
				{
					if(adj[i][j]==1)
					{
						count++;
					}
				}
				cout<<count<<endl;
				
			}
		}
};

int main()
{
	
	cout<<"Is graph is directed : ";
	bool is;
	cin>>is;
	cout<<"Enter number of verices you want : ";
	int n;
	cin>>n;
	Graph gr(n);
	cout<<"Enter number of edges you want in graph :";
	cin>>n;
	
	while(n--)
	{
		cout<<"Enter edge : ";
		int a,b;
		cin>>a>>b;
		gr.addEdge(a,b,is);
	}
	gr.adj_list();
	
	gr.degree();
	
	cout<<"Enter starting point for BFS : ";
	int start;
	cin>>start;
	gr.BFS(start);
	cout<<"Enter starting point for DFS : ";
	cin>>start;
	gr.reset();
	gr.DFS(start);

 	return 0;
}