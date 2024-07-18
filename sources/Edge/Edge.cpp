#include "Edge.hpp"

Edge::Edge()
    : m_weight(0xFFFF)
    , m_leftVertex(nullptr)
    , m_rightVertex(nullptr) {}

void Edge::setWeight(int weight) { m_weight = weight; }

void Edge::setVertecies(std::shared_ptr<Vertex>& vRight, std::shared_ptr<Vertex>& vLeft) {
    m_rightVertex = vRight;
    m_leftVertex = vLeft;
}

int Edge::getWeight() { return m_weight; }

std::shared_ptr<std::pair<std::shared_ptr<Vertex>&, std::shared_ptr<Vertex>&>>
Edge::getVertecies() {
    // TODO: Can an Edge use an unique_ptr? There is no need for more than one pointer to an edge
    // TODO: Can you make it better? Why such a long ptr?!
    std::shared_ptr<std::pair<std::shared_ptr<Vertex>&, std::shared_ptr<Vertex>&>> vPtr{
        std::make_shared<std::pair<std::shared_ptr<Vertex>&, std::shared_ptr<Vertex>&>>(
            m_rightVertex, m_leftVertex)};
    return vPtr;
}