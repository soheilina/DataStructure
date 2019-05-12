#include "node.h"

Node::Node():
    data(0),
    right(nullptr),
    left(nullptr)
{
    cout << "default constructor called" << endl;
}

Node :: Node(int input){
    data = input;
    left = nullptr;
    right = nullptr;
    cout << "parameterized constructor called" << endl;
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

shared_ptr<Node> Node :: getLeftNode() const {
    return left;
}

shared_ptr<Node> Node :: getRightNode() const {
    return right;
}

