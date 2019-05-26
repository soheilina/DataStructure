#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <initializer_list>
#include <string> // to_string

#include "node.h"

using namespace std;

class BinaryTree
{
public:
    explicit BinaryTree(); // HINT: a default constructor can have "explicit" specifier but "explicit" is ignored.
    explicit BinaryTree( std::initializer_list<int> initList ); // HINT: initializer-list-constructor
    ~BinaryTree() = default;

public:
    void addNode( shared_ptr<Node>& parent, const shared_ptr<Node>& node ); // NOTE: cons is not necessary as the node is not modified.
    void printTree( const shared_ptr<Node>& startNode ); // the input is the node where you wanna start printing
    void printDepth( void );
    shared_ptr<Node> getRoot();

private:
    shared_ptr<Node> root;
    int nodeDepth; // stores the depth of current node and is used for printDepth()
};

#endif // BINARYTREE_H
