#include "Vertex.hpp"

Vertex::Vertex()
	: m_id(-1)
	, m_neighbors({})
{
}

void Vertex::setID(int id) {
	m_id = id;
}

void Vertex::addNeighbor(std::shared_ptr<Vertex>& neighbor)
{
	m_neighbors.push_back(neighbor);
}

int Vertex::getID() const
{
	return m_id;
}

std::list<std::weak_ptr<Vertex>>& Vertex::getAllNeighbors()
{
	return m_neighbors;
}

void Vertex::removeNeighbor(std::shared_ptr<Vertex>& neighbor) {
	m_neighbors.remove_if([&](const auto& n) {
		return(n.expired()
				? false
				: (n.lock()->getID() == neighbor->getID())
				);
		});
}

int Vertex::getNumberOfNeighbors() const
{
	return m_neighbors.size();
}

bool Vertex::isNeighbor(std::shared_ptr<Vertex>& v) const
{
	auto idx = std::find_if(m_neighbors.begin(), m_neighbors.end(), [&](const auto n) {
		return(n.expired()
			   ? false
			   : (n.lock()->getID()==v->getID())
			   );
		});
	return(idx != m_neighbors.end());
}