#include "Graph.hpp"

Graph::Graph()
	: m_vertices({})
	, m_edges({})
{
}

void Graph::addVertex(std::shared_ptr<Vertex>& v)
{
	// checks that the vertix is not alrealy available and the ID is not taken
	if (!isVertex(v) && !isVertexByID(v->getID()))
	{
		m_vertices.push_back(v);
	}
	else
	{
		std::cerr << "ATTENTION: There is a vertex with id=" << v->getID() << std::endl;
	}
}

void Graph::removeVertex(std::shared_ptr<Vertex>& v)
{
	// remove v from the neighbor list of its adjacent vertecies
	for (const auto& vertex : m_vertices)
	{
		if (vertex->getID() != v->getID())
		{
			vertex->removeNeighbor(v);
		}
	}

	// remove all edges connected to v
	m_edges.remove_if([&](const auto& e) {
		const auto vDeparture = e->getVertecies()->first;
		const auto vDestination = e->getVertecies()->second;

		return((vDeparture->getID() == v->getID()) || (vDestination->getID() == v->getID()));
		});

	//remove v from list of vertecies
	m_vertices.remove(v);
}

void Graph::removeVertexByID(int id)
{
	auto vertex = getVertexByID(id);
	if ( vertex != nullptr)
	{
		removeVertex(vertex);
	}
}

std::shared_ptr<Vertex> Graph::getVertexByID(int id)
{
	std::shared_ptr<Vertex> result= nullptr;

	for (const auto& v : m_vertices)
	{
		if (v->getID() == id)
		{
			result = v;
		}
	}
	
	if (result != nullptr)
	{
		return result;
	}
	else
	{
		std::cerr << "ATTENTION: There is no Vertex with id=" << id << std::endl;
	}
}

void Graph::addEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2, int weight)
{
	//ensures there is no edge from v1 to v2
	if (!isEdge(v1, v2))
	{
		//establishes a connection from v1 to v2 (not vice versa!)
		v1->addNeighbor(v2);

		// sets an edge
		std::shared_ptr<Edge> edge = std::make_shared<Edge>();
		edge->setVertecies(v1, v2);
		edge->setWeight(weight);

		m_edges.push_back(edge);
	}
}


void Graph::removeEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2)
{
	// remove the connection from v1 to v2 (not vice versa)
	v1->removeNeighbor(v2);

	// remove the edge
	m_edges.remove_if([&](auto const& e) {return((e->getVertecies()->first == v1) && (e->getVertecies()->second == v2)); });
}

void Graph::printAllVertecies() const
{
	std::cout << "List of all vertecies: " << std::endl;
	for (const auto v : m_vertices)
	{
		std::cout << "V" << v->getID() << "\t";
	}
	std::cout << std::endl;
}

void Graph::printAllEdges() const
{
	std::cout << "List of all edges in the Graph:" << std::endl;
	for (const auto& e : m_edges)
	{
		std::cout << "An edge from the vertex V" << e->getVertecies()->first->getID()
					<< " to the vertex V" << e->getVertecies()->second->getID()
					<< " with the weight " << e->getWeight() << std::endl;
	}
}

bool Graph::isGraphEmpty() const
{
	return (m_vertices.size() == 0);
}

int Graph::getNumberOfVertecies() const
{
	return m_vertices.size();
}

void Graph::clearGraph()
{
	m_edges.clear();
	m_vertices.clear();
}

bool Graph::isEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2) const
{
	auto result = std::find_if(v1->getAllNeighbors().begin(), v1->getAllNeighbors().end(), [&](const auto& n) {
		return( n.expired()
			    ? false
			    : n.lock()->getID() == v2->getID());
		});
	return( result != v1->getAllNeighbors().end());
}

std::shared_ptr<Edge> Graph::getEdge(std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2) const
{
	if (isEdge(v1, v2))
	{
		for (const auto& e : m_edges) {
			if (e->getVertecies()->first == v1 && e->getVertecies()->second == v2)
				return e;
		}
	}
	else
	{
		return nullptr;
	}
}

bool Graph::isVertex(std::shared_ptr<Vertex>& v) const
{
	auto result = std::find(m_vertices.begin(), m_vertices.end(), v);
	return (result != m_vertices.end());
}

bool Graph::isVertexByID(int id) const
{
	auto result = std::find_if(m_vertices.begin(), m_vertices.end(), [&](const auto& v) {
		return(v->getID()==id);
		});
	return (result != m_vertices.end());
}