#include "binaryTree.hpp"

BinaryTree::BinaryTree()
    : root(nullptr) {
    // TODO: Is it needed?
}

BinaryTree ::BinaryTree(std::initializer_list<int> initList)
    : root(nullptr) {

    // fill it out
    for (auto n : initList) {
        shared_ptr<Node> node = std::make_shared<Node>(n);
        addNode(root, node);
        cout << "Tree has a node containing value: " << node->getData() << endl;
    }
}

void BinaryTree ::addNode(shared_ptr<Node>& parent,
                          const shared_ptr<Node>& node) { // Inserts a new node asccending form

    if (parent == nullptr) {
        // Set root
        parent = node;
    } else if (node->getData() < parent->getData()) { // if smaller
        // traverse to left
        addNode(
            parent->getLeftNode(),
            node); // a temp variable can be used too: shared_ptr<Node>& n{ parent->getLeftNode() };
    } else if (node->getData() > parent->getData()) { // if bigger
        // traverse to right
        addNode(parent->getRightNode(), node); // a temp variable can be used too: shared_ptr<Node>&
                                               // n{ parent->getRightNode() };
    } else {                                   // if equal: the node already exists. Do nothing.
        cout << "The node already exists." << endl;
    }
}

void BinaryTree ::printTreePreOrder(
    const shared_ptr<Node> node) { // print first the root node, then left, then right (up-to-down)
    if (node == nullptr) {
        // Base case: Do nothing
    } else {
        // Print (parent) node
        cout << node->getData() << endl;

        // Traverse to left
        printTreePreOrder(node->getLeftNode());

        // Traverse to right
        printTreePreOrder(node->getRightNode());
    }
}

void BinaryTree ::printTreeInOrder(
    const shared_ptr<Node> node,
    int nodeDepth) { // print left subtree, then root, then right subtree ( ACENDING )
    if (node == nullptr) {
        // Base case: Do nothing
    } else {
        // Traverse to left
        nodeDepth++;
        printTreeInOrder(node->getLeftNode(), nodeDepth);
        nodeDepth--;

        // Print (parent) node
        printDepth(nodeDepth);
        cout << node->getData() << endl;

        // Traverse to right
        nodeDepth++;
        printTreeInOrder(node->getRightNode(), nodeDepth);
        nodeDepth--;
    }
}

void BinaryTree ::printTreePostOrder(
    const shared_ptr<Node>
        node) { // print left subtree, then right subtree, then root (down-to-top)
    if (node == nullptr) {
        // Base case: Do nothing
    } else {
        // Traverse to left
        printTreePostOrder(node->getLeftNode());

        // Traverse to right
        printTreePostOrder(node->getRightNode());

        // Print (parent) node
        cout << node->getData() << endl;
    }
}

void BinaryTree ::printTreeReverseOrder(
    const shared_ptr<Node> node,
    int nodeDepth) { // print right subtree, then root, then left subtree ( DECENDING )
    if (node == nullptr) {
        // Base case
    } else {
        // Traverse to right
        nodeDepth++; // Move the tree down
        printTreeReverseOrder(node->getRightNode(), nodeDepth);
        nodeDepth--; // Move the tree up

        // Print (parent) node
        printDepth(nodeDepth);
        cout << node->getData() << endl;

        // Traverse to left
        nodeDepth++; // Move the tree down
        printTreeReverseOrder(node->getLeftNode(), nodeDepth);
        nodeDepth--; // Move the tree up
    }
}

shared_ptr<Node>& BinaryTree ::getRoot() { return root; }

void BinaryTree ::printDepth(int nodeDepth) {
    int count = nodeDepth;
    while (count--) {
        cout << "    ";
    }
}

shared_ptr<Node>& BinaryTree ::findNode(shared_ptr<Node>& startNode, int nodeValue)
    const { // NOTE: It has O(log2). An inefficient solution would be search all branches for
            // equality regardless of bigger or smaller
    if (startNode == nullptr || startNode->getData() == nodeValue) {
        // Base case: not found OR found
        return startNode;
    } else if (startNode->getData() < nodeValue) { // bigger
        // traverse right
        return findNode(startNode->getRightNode(), nodeValue);
    } else { // smaller
        // traverse left
        return findNode(startNode->getLeftNode(), nodeValue);
    }
}

void BinaryTree ::removeNode(int nodeValue) {
    shared_ptr<Node>& n = findNode(root, nodeValue); // start from the root and look for nodeValue
    if (n != nullptr) {                              // node found
        removeNode(n);
    }
}

void BinaryTree ::removeNode(shared_ptr<Node>& startNode) {
    if (startNode->getLeftNode() == nullptr &&
        startNode->getRightNode() == nullptr) { // has no child
        // Base case: remove it.
        startNode = nullptr;
    } else if (startNode->getLeftNode() != nullptr &&
               startNode->getRightNode() == nullptr) { // has only left children
        // substitute the node by its left subtree
        startNode = startNode->getLeftNode();
    } else if (startNode->getLeftNode() == nullptr &&
               startNode->getRightNode() != nullptr) { // has only right children:
        // substitute the node by its right subtree
        startNode = startNode->getRightNode();
    } else { // has both left and right subtrees
        // Find the min value in the right subtree
        shared_ptr<Node>& n =
            getMin(startNode->getRightNode()); // returns the min child which is in right subtree
        startNode->setData(n->getData());
        removeNode(n);
    }
}

shared_ptr<Node>& BinaryTree ::getMin(shared_ptr<Node>& startNode) const {
    if (startNode == nullptr) {
        // Do nothing. The first input node is null.
    } else if (startNode->getLeftNode() == nullptr) { // left node is null
        // Base case:
        return startNode; // NOTE: this returns the result of very inner function (last left node)
                          // to its own 'one' upper function
    } else {
        // traverse to left
        return getMin(
            startNode->getLeftNode()); // NOTE: Each inner function returns the result to its upper
                                       // function untill it gets to the 1st one and then out.
    }
}
