#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <string>
#include <map>
#include <iostream>

/// Namespace
using namespace std;
/// Type definition
using uint = unsigned int;


class Graph /// This graph is implmented based on Adjacency List
{
public:
    ~Graph() = default;
    explicit Graph();
    explicit Graph(initializer_list<string> vertexList);
// Setters & Getters
public:
    void addVertex(string vName);
    void printEdges(string vName);
    void printAllVertices();
    void addEdge(string from, string to, int weight);
    void printAllEdges();
    void clearGraph(); // removes all vertecies and edges
    bool isNeighbor( string self, string neighbor);
    bool isEmpty(); // returns true if graph has no vertex / edges
    int  getSize();
    void removeVertex(string vName);
    void removeEdge(string self, string neighbor);

    list< pair<string,list< pair<string,int> > > > :: iterator& getVertex(string vName); // returns the reference of pointer to the position of vertex with given name
    list<reference_wrapper< pair<string,list< pair<string,int> > > >> getNeighbors(string vName); // retuens a list of ref to all neighbors
    list<pair<string,int>>& getEdges( string vName ); // returns the reference to a list of all edges of the given vertex
    list<reference_wrapper< pair<string,list< pair<string,int> > > >> getAllVertecies(); //return a list of ref to each vertex i.e. pair composed of vName and Edges

private:
    list< pair<string,list< pair<string,int> > > > vertecies; // pair<vertex, weight>

};

#endif // GRAPH_H
