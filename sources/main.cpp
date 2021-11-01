
#include "binaryTree.h"
#include "graph.h"
#include "hashset.h"
#include "node.h"

void testNode( void );
void testBinaryTree( void );
void testGraph();
void testHashSet();

int main(){
    std::cout << "To test any Design Pattern, please enter its corresponding number." << std::endl;
    std::cout << "For Node enter 1\n"
              << "For BinaryTree enter 2\n"
              << "For Graph enter 3\n"
              << "For HashSet enter 4\n"
              << std::endl;
    
    int input{0};
    std::cin >> input;
    switch (input)
    {
    case 1:{
        testNode();
        break;
    }
    case 2:{
        testBinaryTree();
    }
    case 3:{
        testGraph();
    }
    case 4:{
        testHashSet();
    }
    
    default:
        break;
    }

    return 0;
}

void testNode(){

    shared_ptr<Node> ptrParent = make_shared<Node>();
    shared_ptr<Node> ptrLeft = make_shared<Node>();
    shared_ptr<Node> ptrRight = make_shared<Node>();

    ptrParent->setData(0);
    ptrLeft->setData(1);
    ptrRight->setData(2);

    ptrParent->setLeftNode(ptrLeft);
    ptrParent->setRightNode(ptrRight);

    cout << "The node has a value of " << ptrParent->getData() << "." <<\
            " Its left child has a value of " << ptrParent->getLeftNode()->getData() << \
            " and its right child has a value of " << ptrParent->getRightNode()->getData() << endl;

}

void testBinaryTree(){
    cout << "\nA tree is created..." << endl;

    shared_ptr<BinaryTree> BT = make_shared<BinaryTree>( std::initializer_list<int>({0,1,2,7,-2, -5, -1, 7, 5, 8 , 4, 6,-3, -17, -19, -18}) );
    // TODO:
    //BinaryTree BT({0,1,2}); // This works but this one not: shared_ptr<BinaryTree> BT = make_shared<BinaryTree>({0,1,2}); why not?

    shared_ptr<Node>& rootOfTree = BT->getRoot();
    cout << "The tree is printed in pre-order:" << endl;
    BT->printTreePreOrder(rootOfTree);
    cout << "The tree is printed in in-order:" << endl;
    BT->printTreeInOrder(rootOfTree);
    cout << "The tree is printed in post-order:" << endl;
    BT->printTreePostOrder(rootOfTree);
    cout << "The tree is printed in reverse-order:" << endl;
    BT->printTreeReverseOrder(rootOfTree);



    int item = 5;
    BT->removeNode(item);
    cout << "the node containing " << item << " has been removed:" << endl;

    BT->printTreeReverseOrder(BT->getRoot());
}

void testGraph(){

    std::initializer_list<string> vList{"v1","v2", "v3", "v4", "v5", "v6", "v7"};
    std::unique_ptr<Graph> pGraph = std::make_unique<Graph>(vList);

    //pGraph->printAllVertices();
    pGraph->addEdge("v1", "v2", 3);
    pGraph->addEdge("v1", "v4", 5);
    pGraph->addEdge("v1", "v7", 2);
    pGraph->addEdge("v2", "v3", 6);
    pGraph->addEdge("v2", "v5", 1);
    pGraph->addEdge("v3", "v6", 1);
    pGraph->addEdge("v4", "v7", 6);
    pGraph->addEdge("v5", "v2", 1);
    pGraph->addEdge("v5", "v6", 2);
    pGraph->addEdge("v6", "v3", 2);
    pGraph->addEdge("v6", "v7", 4);
    pGraph->addEdge("v7", "v1", 2);
    pGraph->addEdge("v7", "v4", 6);
    pGraph->addEdge("v7", "v5", 3);

//    pGraph->getEdges("v1").begin()->second = -3;

//    for(auto& i : pGraph->getNeighbors("v1") ){
//        cout << "v1 neighbor: " << i.get().first << "!" << endl;
//        i.get().first = "@";
//    }

    //pGraph->printAllEdges();

//    for(auto& v : pGraph->getAllVertecies() ){
//        cout << "v: " << v.get().first << endl;
//    }
    pGraph->removeVertex("v5");
    pGraph->removeEdge("v7","v4");

    pGraph->printAllEdges();

    //TODO: list<pair<string,int>> x = pGraph->getEdges("v11");

    string self{"v2"}, other{"v5"};
    cout << self << " has " << ( (pGraph->isNeighbor(self, other) == true ) ? "" : "NOT ") << "a neighbor called " << other << endl;

    cout << "its size is: " << pGraph->getSize() << endl;


}

void testHashSet(){

    shared_ptr<HashSet> ptrHashSet = make_shared<HashSet>();
    vector<int> inputs = {17, 41, 9, 29, 37, 81, 69, 20, 42, 17};
    for(auto&& i : inputs){
        cout << "add " << i << " (before)" << endl;
        ptrHashSet->printStructure();
        ptrHashSet->add(i);
        cout << "add " << i << " (after)" << endl;
        ptrHashSet->printStructure();
    }

    int val = 59;
    cout << "The HashSet" << ( (ptrHashSet->contains(val) == true ) ? (" contains ") : (" doesn't contain ")) << "a node with data " << val << endl;

    ptrHashSet->remove(29);
    ptrHashSet->printStructure();
}
