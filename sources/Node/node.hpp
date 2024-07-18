#ifndef NODE_H
#define NODE_H

using namespace std;

class Node
{
public:
    explicit Node(); // HINT: a default constructor can have "explicit" specifier but "explicit" is ignored.
    explicit Node(int input);
    ~Node() = default;
    
    //copy c'tor
	Node(const Node&);
	// move c'tor
	Node(Node&& rhs) noexcept;
	
	// Assignment Operator
	Node& operator=(Node& rhs);
	// move assignment operator
	Node& operator=(Node&& rhs) noexcept;
public:
    // Setters
    void setData( int parData);
    void setLeftNode( shared_ptr<Node> parNode);
    void setRightNode( shared_ptr<Node> parNode);
    // Getters
    int getData() const;
    shared_ptr<Node>& getRightNode(); // return a reference 'cause binaryTree has funcs accept node& as input.An alternative is to
    shared_ptr<Node>& getLeftNode();  // remove getter functions and make right and left node public in orther to use them directly in binaryTree funcs


private:
    int m_data;
    shared_ptr<Node> m_rightNode;
    shared_ptr<Node> m_leftNode;
};

#endif // NODE_H
