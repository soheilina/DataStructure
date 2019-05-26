#include "node.h"
#include "binaryTree.h"



int main(){
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

    cout << "\nA tree is created..." << endl;

    shared_ptr<BinaryTree> BT = make_shared<BinaryTree>( std::initializer_list<int>({0,1,2,3,-2, -5, -3, 7, 4, 5}) );
    // TODO:
    //BinaryTree BT({0,1,2}); // This works but this one not: shared_ptr<BinaryTree> BT = make_shared<BinaryTree>({0,1,2}); why not?

    cout << "The tree is printed:" << endl;
    shared_ptr<Node> rootOfTree = BT->getRoot();
    BT->printTree(rootOfTree);

    /*cout << "rootL: " << BT->getRoot()->getLeftNode()->getData() << endl;
    cout << "root: " << BT->getRoot()->getData() << endl;
    cout << "rootR: " << BT->getRoot()->getRightNode()->getData() << endl;
    cout << "rootRR: " << BT->getRoot()->getRightNode()->getRightNode()->getData() << endl;
    cout << "rootRRR: " << BT->getRoot()->getRightNode()->getRightNode()->getRightNode()->getData() << endl;*/





    return 0;
}
