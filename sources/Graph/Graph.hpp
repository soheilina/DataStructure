#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include "../pch.h" //NOTE: Not necessary when CMake is used. It includes pch to all cpp files of the specified target.

#include "../Vertex/Vertex.hpp"

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

    void printVertecies() const;
    void printGraph() const;

    int getNumberOfVertecies() const;
    std::shared_ptr<Vertex> getVertexByID(int id);

    bool isEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2) const;
    bool isVertex(std::shared_ptr<Vertex>& v) const;
    bool isVertexByID(int id) const;

    bool isGraphEmpty() const;
    void clearGraph();

    // Functions for BFS algorithm
    void runBreadthFirstSearch(Vertex* source);
    void calculatePathByBreadthFirstSearch(Vertex* v, Vertex* u);
    void printPath(Vertex* source, Vertex* v);

    // Functions for DFS algorithms
    void runDepthFirstSearch(Vertex* source);
    void visitDFS(Vertex* source);
    void initializeDFS();
    void topological_sort();

  private:
    std::list<std::shared_ptr<Vertex>> m_vertices;
    u_int16_t m_DFS_time;
};

#endif // _GRAPH_HPP