#include "Graph.hpp"

Graph::Graph()
    : m_vertices({})
    , m_DFS_time{0} {}

void Graph::addVertex(std::shared_ptr<Vertex>& v) {
    // checks that the vertix is not alrealy available and the ID is not taken
    if (!isVertex(v) && !isVertexByID(v->getID())) {
        m_vertices.push_back(v);
    } else {
        std::cerr << "ATTENTION: There is a vertex with id=" << v->getID() << std::endl;
    }
}

void Graph::removeVertex(std::shared_ptr<Vertex>& v) {
    // remove v from the neighbor list of its adjacent vertecies
    for (const auto& vertex : m_vertices) {
        if (vertex->getID() != v->getID()) {
            vertex->removeNeighbor(v);
        }
    }

    // remove v from list of vertecies
    m_vertices.remove(v);
}

void Graph::removeVertexByID(int id) {
    auto vertex = getVertexByID(id);
    if (vertex != nullptr) {
        removeVertex(vertex);
    }
}

std::shared_ptr<Vertex> Graph::getVertexByID(int id) {
    std::shared_ptr<Vertex> result = nullptr;

    for (const auto& v : m_vertices) {
        if (v->getID() == id) {
            result = v;
        }
    }

    if (result == nullptr) {
        std::cerr << "ATTENTION: There is no Vertex with id=" << id << std::endl;
    }
    return result;
}

void Graph::addEdge(std::shared_ptr<Vertex>& v, std::shared_ptr<Vertex>& u, int weight) {
    // ensures there is no edge from v1 to v2
    if (!isEdge(v, u)) {
        // establishes a connection from v1 to v2 (not vice versa!)
        v->addNeighbor(u, weight);
    }
}

void Graph::removeEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2) {
    // remove the connection from v1 to v2 (not vice versa)
    v1->removeNeighbor(v2);
}

void Graph::printVertecies() const {
    std::cout << "List of all vertecies: " << std::endl;
    for (const auto v : m_vertices) {
        std::cout << "V" << v->getID() << "\t";
    }
    std::cout << std::endl;
}

void Graph::printGraph() const {
    std::cout << "Graph representation from a vertex with a wight to the next vertex:" << std::endl;
    for (auto const& v : m_vertices) {
        for (auto const& n : v->getNeighbors()) {
            std::cout << "V" << v->getID() << "---weight=" << n.second << "--->V"
                      << n.first.lock()->getID() << std::endl;
        }
    }
}

bool Graph::isGraphEmpty() const { return (m_vertices.size() == 0); }

int Graph::getNumberOfVertecies() const { return m_vertices.size(); }

void Graph::clearGraph() {
    // m_edges.clear();
    m_vertices.clear();
}

bool Graph::isEdge(std::shared_ptr<Vertex>& v, std::shared_ptr<Vertex>& u) const {
    /*
        @brief: check if u is an adjacent vertex to v.
    */
    auto result =
        std::find_if(v->getNeighbors().begin(), v->getNeighbors().end(), [&](const auto& n) {
            return (n.first.expired() ? false : n.first.lock()->getID() == u->getID());
        });
    return (result != v->getNeighbors().end());
}

bool Graph::isVertex(std::shared_ptr<Vertex>& v) const {
    auto result = std::find(m_vertices.begin(), m_vertices.end(), v);
    return (result != m_vertices.end());
}

bool Graph::isVertexByID(int id) const {
    auto result = std::find_if(m_vertices.begin(), m_vertices.end(),
                               [&](const auto& v) { return (v->getID() == id); });
    return (result != m_vertices.end());
}

void Graph::calculatePathByBreadthFirstSearch(Vertex* v, Vertex* u) {
    /*@brief: Construct BFS-Tree from vertex v and print the path from v to u
     */
    runBreadthFirstSearch(v);
    std::cout << "The path from source with id " << v->getID() << " to the vertex with id "
              << u->getID() << " is:" << std::endl;
    printPath(v, u);
    std::cout << std::endl;
}

void Graph::runBreadthFirstSearch(Vertex* source) {
    // reset all vertecies
    for (auto v : m_vertices) {
        v->setColor(Color::WHITE);
        v->setDistanceFromSource(-1);
        v->setPredecessor(nullptr);
    }
    // Set the source
    source->setColor(Color::GRAY);
    source->setDistanceFromSource(0);
    source->setPredecessor(nullptr);

    std::queue<Vertex*> q;
    q.push(source);
    while (q.size() != 0) {
        // Get the next vertex in the queue
        Vertex* u = q.front();
        q.pop();
        // Search for neighbors of u
        for (auto& neighbor : u->getNeighbors()) {
            if (!neighbor.first.expired()) {
                Vertex* n = neighbor.first.lock().get();
                if (n->getColor() == Color::WHITE) { // Is n being discovered now?
                    n->setColor(Color::GRAY);
                    n->setDistanceFromSource(u->getDistanceFromSource() + 1);
                    n->setPredecessor(u);
                    q.push(n);
                }
            }
        }
        u->setColor(Color::BLACK);
    }
}

void Graph::printPath(Vertex* source, Vertex* v) {
    if (source == v) {
        std::cout << "--> V(" << source->getID() << ") ";
    } else if (v->getPredecessor() == nullptr) {
        std::cout << "There is no path from vertex " << source->getID() << " to vertex "
                  << v->getID() << std::endl;
    } else {
        printPath(source, v->getPredecessor());
        std::cout << "--> V(" << v->getID() << ") ";
    }
}

void Graph::runDepthFirstSearch(Vertex* source) {
    initializeDFS();
    visitDFS(source);
}

void Graph::initializeDFS() {
    for (auto& v : m_vertices) {
        v->setColor(Color::WHITE);
        v->setPredecessor(nullptr);
    }

    m_DFS_time = 0;
    for (auto& v : m_vertices) {
        if (v->getColor() == Color::WHITE) {
            visitDFS(v.get());
        }
    }
}

void Graph::visitDFS(Vertex* u) {
    ++m_DFS_time;
    u->setDistanceFromSource(m_DFS_time);
    u->setColor(Color::GRAY);

    // explore each edge of u
    for (auto& v : u->getNeighbors()) {
        if ((!v.first.expired()) && (v.first.lock()->getColor() == Color::WHITE)) {
            v.first.lock()->setPredecessor(u);
            // NOTE: Unlike BFS, DFS uses Stack instead of Queue which can be
            // implemented by recursion
            visitDFS(v.first.lock().get());
        }
    }

    ++m_DFS_time;
    u->setFinishTime(m_DFS_time);
    u->setColor(Color::BLACK);
}

void Graph::topological_sort() {
    /*@brief: perform topological sort using DFS.
              See Cormen's book p.573
    */
    std::cout << "This is the topological sorted of vertecies" << std::endl;
    // TODO: CHECK THE CORRECTNESS
    std::list<std::shared_ptr<Vertex>> sorted_vertecies;
    for (auto& v : m_vertices) {
        runDepthFirstSearch(v.get());
        sorted_vertecies.push_front(v);
    }
    for (auto& v : sorted_vertecies) {
        std::cout << "-->V" << v->getID();
    }
    std::cout << std::endl;
}