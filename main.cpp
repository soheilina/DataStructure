#include "node.h"



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


    return 0;
}
