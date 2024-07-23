#ifndef _SORT_HPP
#define _SORT_HPP

#include "../pch.h" //NOTE: Not necessary when CMake is used. It includes pch to all cpp files of the specified target.

class Sort{
  public:
    Sort(SORT_TYPE sort_type);
    ~Sort() = default;
    Sort(Sort const& other) = delete;
    Sort(Sort&& other) = delete;
    Sort& operator=(Sort const& other) = delete;
    Sort& operator=(Sort&& other) = delete;

  public:
    void merge_sort(std::vector<int>& arr, int p, int r) const;
    void quick_sort(std::vector<int>& arr, int p, int r) const;
    void counting_sort_outplace(std::vector<int> arr, uint8_t max_val, std::vector<int>& res);
    void counting_sort_inplace(std::vector<int>& arr, uint8_t max_val);
    template<typename T>
    void insertion_sort(std::vector<T>& arr);
    void bucket_sort(std::vector<float>& arr);
    void heap_sort(std::vector<int>& arr);
    //TODO: write the following functions
    // std::pair<int, int> find_min_max();
    // int find_2nd_min();
    // int get_max_recursive(int* arr, int n);
    // int quickselect(int* arr, int b, int e, int i);
    // float find_median(int* arr, int n);
    // int randomized_select(int* arr, int p, int r, int i);

  private:
    bool is_sorted_ascending(int a, int b) const;
    void merge(std::vector<int>& arr, int p, int q, int r) const;
    int partition(std::vector<int>& arr, int p, int r) const;
    int get_random_pivot(int p, int r) const;
    void build_heap(std::vector<int>& vec);
    void max_heapify(std::vector<int>& vec, int idx, int last_idx);
    void min_heapify(std::vector<int>& vec, int idx, int last_idx);


  private:
    SORT_TYPE m_sort_type;
};

#endif // _SORT_HPP