#pragma once

#include <algorithm>
#include <list>
#include <string>
#include <memory>
#include <iostream>

#include "Vertex.hpp"
#include "Edge.hpp"

class Graph {
public:
	Graph();
	~Graph() = default;
	Graph(const Graph& other) = delete;
	Graph(const Graph&& other) = delete;
	Graph& operator=(Graph& other) = delete;
	Graph& operator=(Graph&& other) = delete;

	void addVertex(std::shared_ptr<Vertex>& v);
	void addEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2, int weight);

	void removeVertex(std::shared_ptr<Vertex>& v);
	void removeVertexByID(int id);
	void removeEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2);

	void printAllVertecies() const;
	void printAllEdges() const;

	int getNumberOfVertecies() const;
	std::shared_ptr<Edge> getEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2) const;
	std::shared_ptr<Vertex> getVertexByID(int id);

	bool isEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2) const;
	bool isVertex(std::shared_ptr<Vertex>& v) const;
	bool isVertexByID(int id) const;
	
	bool isGraphEmpty() const;
	void clearGraph();

private:
	std::list<std::shared_ptr<Vertex>> m_vertices;
	std::list<std::shared_ptr<Edge>> m_edges;
};