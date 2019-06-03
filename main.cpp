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


    return 0;
}
