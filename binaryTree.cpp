#include "binaryTree.h"


BinaryTree::BinaryTree():
    root(nullptr),
    nodeDepth(0)
{
// TODO: Is it needed?
}

BinaryTree :: BinaryTree( std::initializer_list<int> initList ):
    root(nullptr),
    nodeDepth(0)
{

    // fill it out
    for( auto n : initList){
        shared_ptr<Node> node = std::make_shared<Node>(n);
        addNode( root, node );
        cout << "Tree has a node containing value: " << node->getData() << endl;
    }

}

void BinaryTree :: addNode( shared_ptr<Node>& parent, const shared_ptr<Node>& node ){ // Inserts a new node asccending form

    if( parent == nullptr ){
        // Set root
        parent = node;
    }
    else if( node->getData() < parent->getData() ){ // if smaller
        // traverse to left
        shared_ptr<Node>& n{ parent->getLeftNode() }; // NOTE: A refernce is required; otherwise it doesn't work.
        addNode( n, node);
    }
    else if( node->getData() > parent->getData() ){ // if bigger
        // traverse to right
        shared_ptr<Node>& n{ parent->getRightNode() };
        addNode( n, node);
    }else { // if equal: the node already exists. Do nothing.
        cout << "The node already exists." << endl;
    }
}

void BinaryTree :: printTree( const shared_ptr<Node>& node ){
    if(node == nullptr){
        // Base case: Do nothing
    }
    else{
        // Traverse to left
        nodeDepth++;
        shared_ptr<Node>& n1{ node->getLeftNode() };
        printTree(n1);

        // Print (parent) node
        printDepth();
        cout << node->getData() << endl;

        // Traverse to right
        nodeDepth++;
        shared_ptr<Node>& n2{ node->getRightNode() };
        printTree(n2);
    }
}

shared_ptr<Node> BinaryTree :: getRoot(){
    return root;
}

void BinaryTree :: printDepth(){
    int count = nodeDepth;
    while(count--){
        cout << " ";
    }
    nodeDepth--;
}
