#ifndef _HEAP_HPP
#define _HEAP_HPP

#include "../pch.h" //NOTE: Not necessary when CMake is used. It includes pch to all cpp files of the specified target.

class Heap {
  public:
    Heap(HEAP_TYPE heap_type);
    ~Heap() = default;
    Heap(Heap const& other) = delete;
    Heap& operator=(Heap const& other) = delete;
    Heap(Heap&& other) = delete;
    Heap& operator=(Heap&& other) = delete;

  public:
    void insert(int value);
    int top();
    uint16_t getSize() const;
    void print() const;

  private:
    int getParent(int idx) const;
    int getLeftChild(int idx) const;
    int getRightChild(int idx) const;
    void top_down_heapify(int idx);
    void bottom_up_heapify(int idx);
    bool isHigherInHeap(int idx1, int idx2) const;

  private:
    std::vector<int> m_container;
    HEAP_TYPE m_heap_type;
};

#endif