#include "pch.h" //NOTE: Not necessary when CMake is used. It includes pch to each cpp file.

#include "Graph/Graph.hpp"
#include "HASH/hashset.hpp"
#include "Heap/Heap.hpp"
#include "Node/node.hpp"
#include "Stack/Stack.hpp"
#include "Tree/binaryTree.hpp"
#include "Vertex/Vertex.hpp"
#include "Sort/Sort.hpp"

void testNode();
void testBinaryTree();
void testHashSet();
void testVertecies();
void testGraph();
void testCylicSharedPtr();
void testStack();
void testHeap();

using namespace std;

int main() {
    // set current time as seed for the random generator function
    std::srand(std::time(nullptr));
    
    std::cout << "To test any Design Pattern, please enter its corresponding number." << std::endl;
    std::cout << "1 to test Node\n"
              << "2 to test BinaryTree\n"
              << "3 to test HashSet\n"
              << "4 to test Vertex\n"
              << "5 to test Cylic Shared Pointer\n"
              << "6 to test Graph\n"
              << "7 to test Heap\n"
              << std::endl;

    int input{0};
    std::cin >> input;
    switch (input) {
    case 1: {
        testNode();
        break;
    }
    case 2: {
        testBinaryTree();
        break;
    }
    case 3: {
        testHashSet();
        break;
    }
    case 4: {
        testVertecies();
        break;
    }
    case 5: {
        testCylicSharedPtr();
        break;
    }
    case 6: {
        testGraph();
        break;
    }
    case 7: {
        testHeap();
        break;
    }

    default:
        break;
    }

    return 0;
}

void testNode() {

    shared_ptr<Node> ptrParent = make_shared<Node>();
    shared_ptr<Node> ptrLeft = make_shared<Node>();
    shared_ptr<Node> ptrRight = make_shared<Node>();

    ptrParent->setData(0);
    ptrLeft->setData(1);
    ptrRight->setData(2);

    ptrParent->setLeftNode(ptrLeft);
    ptrParent->setRightNode(ptrRight);

    cout << "The node has a value of " << ptrParent->getData() << "."
         << " Its left child has a value of " << ptrParent->getLeftNode()->getData()
         << " and its right child has a value of " << ptrParent->getRightNode()->getData() << endl;
}

void testBinaryTree() {
    cout << "\nA tree is created..." << endl;

    shared_ptr<BinaryTree> BT = make_shared<BinaryTree>(
        std::initializer_list<int>({0, 1, 2, 7, -2, -5, -1, 7, 5, 8, 4, 6, -3, -17, -19, -18}));
    // TODO:
    // BinaryTree BT({0,1,2}); // This works but this one not: shared_ptr<BinaryTree> BT =
    // make_shared<BinaryTree>({0,1,2}); why not?

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

void testHashSet() {

    shared_ptr<HashSet> ptrHashSet = make_shared<HashSet>();
    vector<int> inputs{17, 41, 9, 29, 37, 81, 69, 20, 42, 17};
    for (auto&& i : inputs) {
        cout << "add " << i << " (before)" << endl;
        ptrHashSet->printStructure();
        ptrHashSet->add(i);
        cout << "add " << i << " (after)" << endl;
        ptrHashSet->printStructure();
    }

    int val = 59;
    cout << "The HashSet"
         << ((ptrHashSet->contains(val) == true) ? (" contains ") : (" doesn't contain "))
         << "a node with data " << val << endl;

    ptrHashSet->remove(29);
    ptrHashSet->printStructure();
}

void testVertecies() {
    std::shared_ptr<Vertex> v1 = std::make_shared<Vertex>();
    std::shared_ptr<Vertex> v2 = std::make_shared<Vertex>();
    std::shared_ptr<Vertex> v3 = std::make_shared<Vertex>();
    std::shared_ptr<Vertex> v4 = std::make_shared<Vertex>();
    v1->setID(1);
    v2->setID(2);
    v3->setID(3);
    v4->setID(4);

    v1->addNeighbor(v2, 12);
    v1->addNeighbor(v3, 13);
    v1->addNeighbor(v4, 14);
    std::cout << "v1 has " << v1->getNumberOfNeighbors() << " neighbors:" << std::endl;
    for (const auto& i : v1->getNeighbors()) {
        if (!i.first.expired())
            std::cout << "vertex " << i.first.lock()->getID() << " is a neighbor of v1"
                      << std::endl;
    }

    v1->removeNeighbor(v3);

    std::cout << std::endl;

    std::cout << "v1 has " << v1->getNumberOfNeighbors() << " neighbors:" << std::endl;
    for (const auto& i : v1->getNeighbors()) {
        if (!i.first.expired())
            std::cout << "vertex " << i.first.lock()->getID() << " is a neighbor of v1"
                      << std::endl;
    }

    v1->removeNeighbor(v2);

    if (v1->isNeighbor(v2)) {
        std::cout << "V2 is a neighbor of v1" << std::endl;
    } else {
        std::cout << "V2 is NOT a neighbor of v1" << std::endl;
    }
}

void testGraph() {
    std::shared_ptr<Vertex> v1 = std::make_shared<Vertex>();
    std::shared_ptr<Vertex> v2 = std::make_shared<Vertex>();
    std::shared_ptr<Vertex> v3 = std::make_shared<Vertex>();
    std::shared_ptr<Vertex> v4 = std::make_shared<Vertex>();
    v1->setID(1);
    v2->setID(2);
    v3->setID(3);
    v4->setID(4);

    std::unique_ptr<Graph> G = std::make_unique<Graph>();
    G->addVertex(v1);
    G->addVertex(v2);
    G->addVertex(v3);
    G->addVertex(v4);

    std::shared_ptr<Vertex> v5 = std::make_shared<Vertex>();
    v5->setID(4);
    G->addVertex(v4);
    G->addVertex(v5);

    // G->removeVertex(v4);
    // G->removeVertexByID(3);

    G->addEdge(v1, v2, 12);
    G->addEdge(v1, v3, 13);
    G->addEdge(v2, v2, 22);
    G->addEdge(v2, v3, 23);
    G->addEdge(v2, v4, 24);
    G->addEdge(v3, v1, 31);
    G->addEdge(v3, v4, 34);
    G->addEdge(v4, v1, 41);
    G->addEdge(v4, v2, 42);

    G->printVertecies();
    G->printGraph();

    // G->removeVertex(v3);

    // G->printAllVertecies();
    // G->printAllEdges();

    // G->removeEdge(v1, v2);
    // std::cout << "\nThe edge from v1 to v2 is removed." << std::endl;
    // G->printAllEdges();

    // G->removeEdge(v2, v2);
    // std::cout << "\nThe edge from v2 to v2 is removed." << std::endl;
    // G->printAllEdges();

    // G->removeEdge(v2, v3);
    // std::cout << "\nThe edge from v2 to v3 is removed." << std::endl;
    // G->printAllEdges();

    // G->removeEdge(v4, v2);
    // std::cout << "\nThe edge from v4 to v2 is removed." << std::endl;
    // G->printAllEdges();

    // std::cout << "Is there any edge from V" <<  std::to_string(v1->getID()) << " to V" <<
    // std::to_string(v2->getID()) << "? "
    //           << (G->isEdge(v1, v2) ? ("Yes! with weight " + std::to_string(G->getEdge(v1,
    //           v2)->getWeight())) : "No!") << std::endl;

    // std::cout << "Is there any edge from V" << std::to_string(v2->getID()) << " to V" <<
    // std::to_string(v4->getID()) << "? "
    //           << (G->isEdge(v2, v4) ? ("Yes! with weight " + std::to_string(G->getEdge(v2,
    //           v4)->getWeight())) : "No!") << std::endl;

    // std::cout << std::endl;
    // auto v = G->getVertexByID(2);
    // G->removeVertexByID(2);
    // G->printVertecies();
    // G->printGraph();

    std::cout << "-------------------------" << std::endl;
    // G->calculatePathByBreadthFirstSearch(v1.get(), v4.get());
    // G->printPath(v1.get(), v4.get());
    G->topological_sort();
}

void testCylicSharedPtr() {
    std::shared_ptr<Vertex> v1 = std::make_shared<Vertex>();
    std::shared_ptr<Vertex> v2 = std::make_shared<Vertex>();
    v1->setID(100);
    v2->setID(200);

    v1->addNeighbor(v2, 12);
    v2->addNeighbor(v1, 21);

    // By reseting v1, it's expected that v2 has no neighbor anymore because v1 is destroyed and the
    // memory is released.
    v1.reset();

    std::weak_ptr<Vertex> neighbor_of_v2 = v2->getNeighbors().front().first;

    if (!neighbor_of_v2.expired()) {
        std::cout << "Cyclic Shared_Ptr Reference! See Vertex.hpp the member variable m_neighbors"
                  << std::endl;
    } else {
        std::cout
            << "No Cyclic Shared_Ptr Reference. Because m_neighbors in Vertex.hpp is weak_ptr."
            << std::endl;
    }
}

void testStack() {
    Stack<std::string> stringStack;
    Stack<int> intStack;
    Stack<Node*> nodeStack;

    stringStack.push("Hi!");
    stringStack.push("--");
    stringStack.push("World!");
    stringStack.push("*!");
    while (!stringStack.isEmpty()) {
        std::cout << stringStack.pop() << "\t";
    }
    std::cout << std::endl;

    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    intStack.push(4);
    while (!intStack.isEmpty()) {
        std::cout << intStack.pop() << "\t";
    }
    std::cout << std::endl;

    nodeStack.push(new Node(1));
}

void testHeap() {
    Heap h(HEAP_TYPE::MAX);
    h.insert(5);
    h.print();
    h.insert(50);
    h.print();
    h.insert(150);
    h.print();
    h.insert(0);
    h.print();
    h.insert(7);
    h.print();
    h.insert(60);
    h.print();
    while (h.getSize()) {
        std::cout << "top: " << h.top() << std::endl;
        h.print();
    }
}
