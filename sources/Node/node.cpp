#include "node.hpp"

Node ::Node()
    : m_data(0)
    , m_rightNode(nullptr)
    , m_leftNode(nullptr) {
    cout << "Node: default constructor called. It's pointing to no other nodes and it's value is "
            "zero."
         << endl;
}

Node ::Node(int input) {
    m_data = input;
    m_leftNode = nullptr;
    m_rightNode = nullptr;
    cout << "Node: parameterized constructor called with value: " << m_data << endl;
}

Node::Node(const Node& rhs) {
    m_data = rhs.m_data;
    m_rightNode = rhs.m_rightNode;
    m_leftNode = rhs.m_leftNode;
}

Node::Node(Node&& rhs) noexcept {
    if (&rhs != this) {
        m_data = rhs.m_data;
        m_rightNode = rhs.m_rightNode;
        m_leftNode = rhs.m_leftNode;

        // resets rhs
        rhs.m_data = 0;
        rhs.m_rightNode = nullptr;
        rhs.m_leftNode = nullptr;
    }
}

Node& Node::operator=(Node& rhs) { return rhs; }

Node& Node::operator=(Node&& rhs) noexcept {
    if (&rhs != this) {
        this->setData(rhs.m_data);
        this->setRightNode(rhs.m_rightNode);
        this->setLeftNode(rhs.m_leftNode);

        // resets rhs
        rhs.setData(0);
        rhs.setRightNode(nullptr);
        rhs.setLeftNode(nullptr);
    }

    return *this;
}

void Node ::setData(int parData) { m_data = parData; }

void Node ::setLeftNode(shared_ptr<Node> parNode) { m_leftNode = parNode; }

void Node ::setRightNode(shared_ptr<Node> parNode) { m_rightNode = parNode; }

int Node ::getData() const { return m_data; }

shared_ptr<Node>& Node ::getLeftNode() { return m_leftNode; }

shared_ptr<Node>& Node ::getRightNode() { return m_rightNode; }
