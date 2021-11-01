#include "graph.h"

Graph::Graph()
    : vertecies{}
{
}

Graph :: Graph(initializer_list<string> vertexList){

    for(auto&& vertex : vertexList){
        addVertex(vertex);
    }
}

void Graph :: addVertex(string vName){
    auto pos = getVertex(vName);
    if( pos != vertecies.end()){
        // The vertex exists already
        clog << "Graph :: addVertex : The vertex already exists" << endl;
    }
    else{
        // Each vertex has a list of edges containg the neighbors' index and edge weight
        pair<string, list<pair<string,int>>> connection{vName,{}};
        vertecies.push_back(connection);
    }
}


void Graph :: printAllVertices(){
    cout << "The graph contains following vertices:" << endl;
    for(auto&& v : vertecies){
        cout << v.first << endl;
    }
}

void Graph :: addEdge(string from, string to, int weight){
    auto pos = getVertex(from);
    if(pos == vertecies.end()){
        // There is no vertex called 'from'
        clog << "Graph :: addEdge : The vertex doesn't exist" << endl;
    }
    else{
        pair<string,int> edge = {to,weight}; // make an edge
        pos->second.push_back(edge); // add the edge to the list
    }
}

void Graph :: printAllEdges(){
    for( auto&& vertex : vertecies){
        printEdges(vertex.first);
    }
}

void Graph :: printEdges(string vName){
    auto pos = getVertex(vName);
    if( pos == vertecies.end() ){
        // Requested vertex doesn't exist.
        clog << "Graph :: printEdges : The vertex doesn't exist" << endl;
    }
    else{
        for(auto&& edge : pos->second){
            cout << vName << "--->[" << edge.second << "]>---" << edge.first << endl;
        }
    }
}

list<reference_wrapper< pair<string,list< pair<string,int> > > >> Graph :: getNeighbors(string vName){ // returns a pointer to a list containing 'indexes' of all neighbors
    list<reference_wrapper< pair<string,list< pair<string,int> > > >> neighbors{};
    auto pos = getVertex(vName);
    if( pos == vertecies.end()){
        // The requested vertex doesn't exist
    }
    else{
        for( auto& edge : pos->second){
            auto posNeighbor = getVertex(edge.first);
            neighbors.push_back( *posNeighbor ); // TODO: get reference of each neighbor
        }
    }
    return neighbors;
}

list<pair<string,int>>& Graph :: getEdges(string vName){
    // get the vertex pos
    auto pos = getVertex(vName);
    if (pos != vertecies.end()){
        list<pair<string,int>>& edges = pos->second;
        return edges;
    }
    else{
        // TODO:
        clog << "clog!!!" << endl;
//        throw("No such a vertix!");
    }
}

void Graph :: clearGraph(){
    vertecies = {};
}

list<pair<string,list< pair<string,int> > > > :: iterator& Graph :: getVertex(string vName){
    auto pos = std::find_if(vertecies.begin(), vertecies.end(),
                            [&](pair<string,list<pair<string,int>>> item){
                            return (item.first == vName);
                });
//    list<pair<string,list< pair<string,int> > > > :: iterator& pVertex =  pos;
//    return pVertex;
    return pos;
}

list<reference_wrapper< pair<string,list< pair<string,int> > > >> Graph :: getAllVertecies(){
    list<reference_wrapper<pair<string,list< pair<string,int> > > >> ref{};
    auto it = vertecies.begin();
    while( it != vertecies.end()){
        ref.push_back(*it);
        it++;
    }
    return ref;
}

bool Graph :: isNeighbor(string self, string neighbor){
    bool res {false};

    // Does neighbor exist at all?
    auto pos = getVertex( neighbor );
    if( pos == vertecies.end()){
        // No vertex
//        return res;
//        throw "There is no such a vertex called " + neighbor; //TODO
    }

    // Does self exist at all?
    pos = getVertex(self);
    if(pos == vertecies.end()){
       // The vertex doesn't exist
        throw "There is no such a vertex called " + self ;
    }
    else{
        for( auto&& n : pos->second){
            if(n.first == neighbor){
                res = true;
            }
        }
    }
    return res;
}

bool Graph :: isEmpty(){
    return vertecies.empty();
}

int Graph :: getSize(){
    return vertecies.size();
}

void Graph :: removeVertex(string vName){
    // Remove it from neighbor list of others
    for(auto&& vertex : vertecies){ // TODO: why auto&& works but auto not?
        auto& edges = vertex.second;
        auto it = edges.begin();
        for_each(it, edges.end(), [&vName, &edges, &it](auto edge){
            // find the vertex vName in all its neighbors and erase it
            if(edge.first == vName){
                edges.erase(it);
            }
            it++;
        });
    }

    // Remove vertex
    auto pos = getVertex(vName);
    vertecies.erase(pos);
}

void Graph :: removeEdge(string self, string neighbor){
    auto posSelf = getVertex(self);
    if(posSelf == vertecies.end()){
        // No vertex called self
    }
    else{
        auto& edges = posSelf->second;
        edges.erase(find_if(edges.begin(), edges.end(), [&neighbor](auto edge){
            return ( edge.first == neighbor);
        }));
    }
}


