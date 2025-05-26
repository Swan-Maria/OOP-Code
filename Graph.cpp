#include "Graph.h"
#include <iostream>

Graph::Graph(size_t V) : V(V), adj(V){}

size_t Graph::getNumVertices() const {return V;}

void Graph::addEdge(size_t v, size_t w)
{
	assert(v < V && w < V);
	adj[v].insert(w);
	adj[w].insert(v); 
}

void Graph::addRandomEdges(size_t numEdges) 
{
	std::srand(std::time(nullptr));
	std::set<std::pair<size_t, size_t>> edges; 

	while (edges.size() < numEdges) 
	{
		size_t v = std::rand() % V;
		size_t w = std::rand() % V;

		if (v != w) 
		{
			auto edge = std::minmax(v, w);
			auto res = edges.insert(edge);
			if (res.second) 
			{
				addEdge(v, w);
			}
		}
	}
}

void Graph::DFSFrom(size_t startVertex) const
{
	assert(startVertex < V);
	std::vector<bool> visited(V, false);
	DFS(startVertex, visited);
	std::cout << std::endl;
}

void Graph::DFSAll() const
{
	std::vector<bool> visited(V, false);
	for (size_t i = 0; i < V; i++) 
	{
		if (!visited[i]) 
		{
			DFS(i, visited);
			std::cout << std::endl;
		}
	}
}

void Graph::BFSFrom(size_t startVertex) const
{
	assert(startVertex < V);
	std::vector<bool> visited(V, false);

	BFS(startVertex, visited);
}

void Graph::BFSAll() const
{
	std::vector<bool> visited(V, false);

	for (size_t i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			BFS(i, visited);
		}
	}
}

void Graph::printGraph() const 
{
	for (size_t i = 0; i < V; i++) 
	{
		std::cout << "Vertex " << i << ":";
		for (size_t neighbor : adj[i]) 
		{
			std::cout << "\t" << neighbor << " ";
		}
		std::cout << "\n-------------------------------------------------------------------------------------------------------------------\n";
	}
}

void Graph::DFS(int v, std::vector<bool>& visited) const
{
	visited[v] = true;
	std::cout << v ;

	for (size_t neighbor : adj[v]) 
	{
		if (!visited[neighbor]) 
		{
			std::cout << "  ";
			DFS(neighbor, visited);
		}
	}
}

void Graph::BFS(int startVertex, std::vector<bool>& visited) const
{
	std::queue<size_t> queue;

	visited[startVertex] = true;
	queue.push(startVertex);
	while (!queue.empty())
	{
		size_t v = queue.front();
		queue.pop();
		std::cout << v <<"  ";

		for (size_t neighbor : adj[v])
		{
			if (!visited[neighbor])
			{
				visited[neighbor] = true;
				queue.push(neighbor);
			}
		}
	}
	std::cout << std::endl;
}

int main()
{
	const size_t numVertices = 20;
	Graph graph(numVertices);

	graph.addRandomEdges(50);
	graph.printGraph();

	std::cout << "DFS All:\t";
	graph.DFSAll();
	std::cout << "-------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "BFS All:\t";
	graph.BFSAll();
	
	return 0;
}
