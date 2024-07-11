#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <list>

enum class Color {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2,
};
class Vertex {
  public:
    Vertex();
    ~Vertex() = default;
    Vertex(const Vertex& other) = delete;
    Vertex(const Vertex&& other) = delete;
    Vertex& operator=(const Vertex& other) = delete;
    Vertex& operator=(Vertex&& other) = delete;

    void setID(int id);
    void setColor(Color c);
    void setDistanceFromSource(int d);
    void setPredecessor(Vertex* p);
    void setFinishTime(u_int16_t time);

    int getID() const;
    Color getColor() const;
    int getDistanceFromSource() const;
    Vertex* getPredecessor() const;
    int getNumberOfNeighbors() const;
    void addNeighbor(std::shared_ptr<Vertex> neighbor, int weight);
    void removeNeighbor(std::shared_ptr<Vertex> neighbor);
    bool isNeighbor(std::shared_ptr<Vertex>& v) const;
    // NOTE: Return by reference is crucial here. E.g. inside Graph::isEdge we get an identical list
    // for begin and end, so we can iterate over the list. Otherwise, begin and end points to two
    // different lists.
    std::list<std::pair<std::weak_ptr<Vertex>, int>>& getNeighbors();

  private:
    int m_id;
    int m_distance_from_source;
    Color m_color;
    Vertex* m_predecessor;
    u_int16_t m_DFS_finish_time;
    // NOTE: To avoid Cyclic Shared_ptr Reference the elements of this list are weak_ptr
    std::list<std::pair<std::weak_ptr<Vertex>, int>> m_neighbors;
};

#endif // VERTEX_H