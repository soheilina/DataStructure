#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node
{
public:
    explicit Node(); // HINT: a default constructor can have "explicit" specifier but "explicit" is ignored.
    explicit Node(int input);
    ~Node() = default;
public:
    // Setters
    void setData( int parData);
    void setLeftNode( shared_ptr<Node> parNode);
    void setRightNode( shared_ptr<Node> parNode);
    // Getters
    int getData() const;
    shared_ptr<Node>& getRightNode();
    shared_ptr<Node>& getLeftNode();

private:
    int data;
    shared_ptr<Node> right;
    shared_ptr<Node> left;
};

#endif // NODE_H
