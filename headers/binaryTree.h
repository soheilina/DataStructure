#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <initializer_list>
#include <string> // to_string

#include "node.h"

/// Defines
#define ptrNode     shared_ptr<Node> // HINT: You can use them! No need to repeat shared_ptr<Node>&!
#define ptrRefNode  shared_ptr<Node>&

using namespace std;

class BinaryTree
{
public:
    explicit BinaryTree(); // HINT: a default constructor can have "explicit" specifier but "explicit" is ignored.
    explicit BinaryTree( std::initializer_list<int> initList ); // HINT: initializer-list-constructor
    ~BinaryTree() = default;

public:
    shared_ptr<Node>& getRoot();
    shared_ptr<Node>& getMin( shared_ptr<Node>& startNode ) const;
    shared_ptr<Node>& findNode( shared_ptr<Node>& startNode, int nodeValue ) const; //NOTE: '&' for startNode is necessary 'cause output is its reference, although nothing is modified in function.
    void addNode( shared_ptr<Node>& parent, const shared_ptr<Node>& node ); // NOTE: const is not necessary as the node is not modified.
    void removeNode( shared_ptr<Node>& startNode ); // HINT: watch "CS 106B Lecture: Binary Search Trees: removing" by Morty
    void removeNode( int nodeValue );// Helper
public:
    void printTreePreOrder( const shared_ptr<Node> startNode ); // the input is the node where you wanna start printing
    void printTreeInOrder( const shared_ptr<Node> startNode, int nodeDepth = 0 ); //NOTE: Nothing is gonna get modified in funtion, so no need for '&' for startNode
    void printTreePostOrder( const shared_ptr<Node> startNode );
    void printTreeReverseOrder( const shared_ptr<Node> startNode, int nodeDepth = 0 );
    void printDepth( int nodeDepth );

private:
    shared_ptr<Node> root;
    //int nodeDepth; // stores the depth of current node and is used for printDepth()
};

#endif // BINARYTREE_H
