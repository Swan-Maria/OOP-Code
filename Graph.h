#pragma once
#include <vector>
#include <set>
#include <queue>
#include <assert.h>
#include <algorithm>

class Graph
{
private:
	size_t V;
	std::vector<std::set<size_t>> adj;

public:
	Graph(size_t V);
	size_t getNumVertices() const;
	void addEdge(size_t v, size_t w);
	void addRandomEdges(size_t numEdges);

	void DFSFrom(size_t startV) const;
	void DFSAll() const;
	void BFSFrom(size_t startV) const;
	void BFSAll() const;

	void printGraph() const;
private:

	void DFS(int v, std::vector<bool>& visited) const;
	void BFS(int startV, std::vector<bool>& visited) const;
};