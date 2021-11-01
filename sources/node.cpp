#include "node.h"

Node :: Node():
    data(0),
    right(nullptr),
    left(nullptr)
{
    cout << "Node: default constructor called. It's pointing to no other nodes and it's value is zero." << endl;
}

Node :: Node(int input){
    data = input;
    left = nullptr;
    right = nullptr;
    cout << "Node: parameterized constructor called with value: " << data << endl;
}

void Node :: setData(int parData){
    data = parData;
}

void Node :: setLeftNode(shared_ptr<Node> parNode){
    left = parNode;
}

void Node :: setRightNode(shared_ptr<Node> parNode){
    right = parNode;
}

int Node :: getData() const{
    return data;
}

shared_ptr<Node>& Node :: getLeftNode() {
    return left;
}

shared_ptr<Node>& Node :: getRightNode() {
    return right;
}

