#pragma once

#include "../Vertex/Vertex.hpp"

// BUG: Depricated! An edge is represened using list of neighbors in each Vertex.
class Edge {
  public:
    Edge();
    ~Edge() noexcept = default;
    Edge(const Edge&) = delete;
    Edge(const Edge&&) = delete;
    Edge& operator=(Edge& other) = delete;
    Edge& operator=(Edge&& other) = delete;

    void setVertecies(std::shared_ptr<Vertex>& vRight, std::shared_ptr<Vertex>& vLeft);
    void setWeight(int weight);

    std::shared_ptr<std::pair<std::shared_ptr<Vertex>&, std::shared_ptr<Vertex>&>> getVertecies();
    int getWeight();

  private:
    int m_weight;
    std::shared_ptr<Vertex> m_rightVertex;
    std::shared_ptr<Vertex> m_leftVertex;
};
