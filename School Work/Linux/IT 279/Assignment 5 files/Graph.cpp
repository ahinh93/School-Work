#include "Graph.h"
#include "math.h"

Graph::Graph(int no_of_vertices)
{
	numVertices = no_of_vertices;
	for(int i = 0; i < no_of_vertices; i++)
	{
		for(int k = 0; k < no_of_vertices; k++)
		{
			adj[i][k].weight = INT_MAX;
		}
	}
	//no of vertices goes from 0 to no of edges to declare map.
}

Graph::~Graph()
{
}

void Graph::setEdge(int v1,int v2,double weight)
{
	adj[v1][v2].weight = weight;
}

void Graph::blockVertex(int v)
{
	for(int i = 0; i < numVertices; i++)
	{
		adj[v][i].weight=INT_MAX;
	}
}

int Graph::getEdgeWeight(int v1,int v2)
{

	//returns weight of edge from int a to b. If edge exists, return 1. If edge does not 	exist, return large positive number.	
	
	if(adj[v1][v2].weight != INT_MAX)
		return 1;
	else
		return INT_MAX;
}

int Graph::getEdgeWeightWithTurns(int v1,int v2,int current_direction)
{
}

vector<int> Graph::getShortestPathWithoutTurns(int start,int end)
{
	vector<int> path;
	

	//begin dijkstra's algorithm 
	for(int i = 0; i < numVertices; i++) //for each vertex in G
	{
		node v;
		v.traversed = false;
		v.distance = INT_MAX;
		v.last = -1;
		//this line causes a crash, trying to insert node into PriorityQueue<node>
		//q.insert(v,v.distance);		
	}
	/*
	//start.dist=0;
	q.changePriority(start,0);
	while(!q.empty())
	{
		node u = q.front();
		q.pop();
		if(u.distance==end)
			break;
		u.traversed = true;
		for(map<int,map<int,node>::iterator it=adj.begin(); it!=adj.end(); ++i)
		{
			if(it->first.traversed == false)
			{
				if((it->second.distance + adj[it->first][it->second].weight)< (it->first.distance))
				{
					it->first.distance = (it->second.distance+adj[it->first][it->second].weight);
					it->first.last = it->second;
					q.changePriority(v,v.distance);
				}
			}
		}
	}
*/

	

	return path;  
	
}

vector<int> Graph::getShortestPathWithTurns(int start,int end,int start_direction)
{
    vector<int> path;
	
	return path;     
}
