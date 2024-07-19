#include "Vertex.hpp"

Vertex::Vertex()
    : m_id(-1)
    , m_distance_from_source{-1}
    , m_color{Color::WHITE}
    , m_predecessor{nullptr}
    , m_DFS_finish_time{0}
    , m_neighbors({}) {}

void Vertex::setID(int id) { m_id = id; }

void Vertex::setDistanceFromSource(int d) { m_distance_from_source = d; }

void Vertex::setColor(Color c) { m_color = c; }

void Vertex::setPredecessor(Vertex* predecessor) { m_predecessor = predecessor; }

/**
 * @brief: Set the finish time for a Depth First Search algorithm
 */
void Vertex::setFinishTime(u_int16_t time) {
    m_DFS_finish_time = time;
}

void Vertex::addNeighbor(std::shared_ptr<Vertex> neighbor, int weight) {
    m_neighbors.push_back(std::make_pair(neighbor, weight));
}

Color Vertex::getColor() const { return m_color; }

int Vertex::getDistanceFromSource() const { return m_distance_from_source; }

int Vertex::getID() const { return m_id; }

std::list<std::pair<std::weak_ptr<Vertex>, int>>& Vertex::getNeighbors() { return m_neighbors; }

void Vertex::removeNeighbor(std::shared_ptr<Vertex> neighbor) {
    m_neighbors.remove_if([&](const auto& n) {
        return (n.first.expired() ? false : (n.first.lock()->getID() == neighbor->getID()));
    });
}

int Vertex::getNumberOfNeighbors() const { return m_neighbors.size(); }

bool Vertex::isNeighbor(std::shared_ptr<Vertex>& v) const {
    auto idx = std::find_if(m_neighbors.begin(), m_neighbors.end(), [&](const auto n) {
        return (n.first.expired() ? false : (n.first.lock()->getID() == v->getID()));
    });
    return (idx != m_neighbors.end());
}

Vertex* Vertex::getPredecessor() const { return m_predecessor; }