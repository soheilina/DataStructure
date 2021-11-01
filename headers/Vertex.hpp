#pragma once

#include <list>
#include <memory>

class Vertex
{
public:
	Vertex();
	~Vertex() = default;
	Vertex(const Vertex& other) = delete;
	Vertex(const Vertex&& other) = delete;
	Vertex& operator=(const Vertex& other) = delete;
	Vertex& operator=(Vertex&& other) = delete;

	void setID(int id);
	int getID() const;
	void addNeighbor(std::shared_ptr<Vertex>& neighbor);
	void removeNeighbor(std::shared_ptr<Vertex>& neighbor);
	std::list<std::weak_ptr<Vertex>>& getAllNeighbors(); // HINT: Return by reference is crucial here. E.g. inside Graph::isEdge we get an identical list for begin and end, so we can iterate over the list. Otherwise, begin and end points to two different lists.
	int getNumberOfNeighbors() const;
	bool isNeighbor(std::shared_ptr<Vertex>& v) const;

private:
	int m_id;
	std::list<std::weak_ptr<Vertex>> m_neighbors; //HINT: To avoid Cyclic Shared_ptr Reference the elements of this list are weak_ptr
};