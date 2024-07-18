#include "Heap.hpp"

Heap::Heap(HEAP_TYPE heap_type)
    : m_container{}
    , m_heap_type{heap_type} {}

int Heap::getParent(int i) const { return (i - 1) / 2; }

int Heap::getLeftChild(int i) const { return 2 * i + 1; }

int Heap::getRightChild(int i) const { return 2 * i + 2; }

bool Heap::isHigherInHeap(int val1, int val2) const {
    /*
    @brief: For MinHeap, it checks if val1 is lower than val2. For MaxHeap, it checks if val1 is
    greater than val2.
    */
    if (m_heap_type == HEAP_TYPE::MIN) {
        return (val1 < val2);
    } else {
        return (val1 > val2);
    }
}

void Heap::insert(int value) {
    // insert back
    m_container.push_back(value);
    int idx = m_container.size() - 1;
    bottom_up_heapify(idx);
}

void Heap::bottom_up_heapify(int idx) {
    /*
    @brief: if the value in the index is smaller than its parent, it is moved up to its right
    position.
    */
    int parent_idx = getParent(idx);
    if (idx == parent_idx) {
        // root reached
        return;
    }
    if (isHigherInHeap(m_container[idx], m_container[parent_idx])) {
        // idx should be placed higher than its parent
        std::swap(m_container[idx], m_container[parent_idx]);
        bottom_up_heapify(parent_idx);
    }
}

int Heap::top() {
    // save the root, put the last element in root, and shrink the heap by one.
    int top = m_container[0];
    m_container[0] = m_container.back();
    m_container.resize(m_container.size() - 1);

    top_down_heapify(0);

    return top;
}

void Heap::top_down_heapify(int idx) {
    /*
    @brief: If the node is smaller than its children, it is moved down till it is largers than its
    children or to a leaf.
    @input: idx is the index of the target node.
    @note: SEE DSA Cormen's book p. 165 max_heapify()
    */
    int largest = idx;
    int left_child_idx = getLeftChild(idx);
    int right_child_idx = getRightChild(idx);
    if ((m_container.size() <= 1) || (left_child_idx > m_container.size() - 1)) {
        // It has no child
        return;
    }

    if ((left_child_idx <= m_container.size() - 1) &&
        isHigherInHeap(m_container[left_child_idx], m_container[idx])) {
        // It has a left child larger than the parent
        largest = left_child_idx;
    }

    if ((right_child_idx <= m_container.size() - 1) &&
        isHigherInHeap(m_container[right_child_idx], m_container[largest])) {
        // It has a right child larger than the parent
        largest = right_child_idx;
    }

    if (idx != largest) {
        // The child w/ index 'largest' is larger than the parent
        std::swap(m_container[idx], m_container[largest]);
        top_down_heapify(largest);
    }
}

uint16_t Heap::getSize() const { return m_container.size(); }

void Heap::print() const {
    std::cout << "The Heap contains: ";
    for (auto& e : m_container) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}