#include "Sort.hpp"

Sort::Sort(SORT_TYPE sort_type)
: m_sort_type{sort_type}
{}

/**
 * @brief comapre two inputs. If you want to sort in asceding order, it checks if first input is SE than the second one.
 *        Otherwise, it check if the first value is LE than the second one.
 */
bool Sort::is_sorted_ascending(int a, int b) const {
    return (m_sort_type==SORT_TYPE::ASCENDING) ? (a<=b) : (a>=b);
}

/**
 * @brief sort in ascending order
 * @param arr is the input array
 * @param p is the begining index of the subarray 
 * @param r is the last index of the subarray 
 * @note  T(n)= O(nlg(n)). SEE Cormen's book p. 39
 */
void Sort::merge_sort(std::vector<int>& arr, int p, int r) const {
    if(p==r){ //base
        return;
    }
    // divid & conqure
    int q = (r+p)/2;
    merge_sort(arr, p, q);
    merge_sort(arr, q+1, r);
    // combine
    merge(arr, p, q, r);
}


/**
 * @brief merge two subarrays so that they are in ascending/descenging order. Used in merge_sort()
 * @param arr is the input array
 * @param p is the begining of the subarray
 * @param q is the mid-point of the subarray
 * @param r is the end of the subarray
 * @note  T(n)= O(n). SEE Cormen's book p. 36
 */
void Sort::merge(std::vector<int>& arr, int p, int q, int r) const {
    // copy arr elements to two subarrays
    std::vector<int> left_subarray{};
    std::vector<int> right_subarray{};
    for(int idx=p; idx<=q; ++idx){
        left_subarray.push_back(arr[idx]);
    }
    for(int idx=q+1; idx<=r; ++idx){
        right_subarray.push_back(arr[idx]);
    }

    // merge
    uint8_t idxl{0}, idxr{0};
    while(idxl<left_subarray.size() && idxr<right_subarray.size()){
        // merge the smallest element first for ascending sort; otherwise merge the largest element first.
        if(is_sorted_ascending(left_subarray[idxl], right_subarray[idxr])){
            arr[p] = left_subarray[idxl++];
        } else {
            arr[p] = right_subarray[idxr++];
        }
            ++p;
    }

    // add remaining elements of the left subarray to the arr
    while(idxl<left_subarray.size()){
        arr[p++] = left_subarray[idxl++];
    }
    // add remaining elements of the right subarray to the arr
    while(idxr<right_subarray.size()){
        arr[p++] = right_subarray[idxr++];
    }
}

/** @brief used in quick_sort. Return a pivot in arr where all elements on its right side are larger
        and all elements on its left side are smaller, if ascending sort has been chosen;
        otherwise, left side of the pivot are larger and its right side smaller.
    @param arr is input array
    @param p is the begining of the subarray
    @param r is the end of the subarray
    @note  T(n)= O(n). SEE Cormen's book p. 
*/
int Sort::partition(std::vector<int>& arr, int p, int r) const {
    // To avoid worst-case, get a random pivot and move it to the end of the array. SEE Cormen's book p. 189
    int random_pivot = get_random_pivot(p,r);
    std::swap(arr[random_pivot], arr[r]);

    // put all smaller elements than the last element (i.e.pivot) to one side and all larger ones to the other side
    int i=p-1, j=p;
    while(j<r){
        if(is_sorted_ascending(arr[j], arr[r])){
            std::swap(arr[j], arr[i+1]);
            ++i;
        }
        ++j;
    }
    // move the pivot form the end between lower and larger values
    std::swap(arr[i+1], arr[r]);
    return i+1;
}

/** @brief divide the array into two subarrays and sort them around a pivot in each call.
    @param arr is input array
    @param p is the begining of the subarray
    @param r is the end of the subarray
    @note  T(n)= O(nlg(n)). SEE Cormen's book p. 183
 */
void Sort::quick_sort(std::vector<int>& arr, int p, int r) const {
    if(p<r){
        int q = partition(arr, p, r);
        quick_sort(arr, p, q-1);
        quick_sort(arr, q+1, r);
    }
}

/** @brief return a random pivon in the interval [p, r].
    @note Worst case scenario happens in quick_sort when one subarray is empty.
          Choosing a random pivot helps as remedy. SEE Cormen's book p. 189
 */
int Sort::get_random_pivot(int p, int r) const {
    return (p + (std::rand()%(r-p+1)));
}

/** @brief sort an array using another array stores the counting of each element of arr.
    @param arr is input array
    @param max_val maximum value in arr
    @note T(n)=THETA(n+max_value)=O(n). Stability is irrelevant here because we have no satellite data.
          //NOTE: In case of using satellite data, counter needs to have a FIFO collection to ensure stability.
          SEE excercise 8.2-5 at Cormen's book p.211
*/
void Sort::counting_sort_inplace(std::vector<int>& arr, uint8_t max_val){
    std::vector<int> counter(max_val+1, 0);
    for(uint8_t i=0; i<arr.size(); ++i){
        ++counter[arr[i]];
    }

    uint8_t i{0};
    for(int j=0; j<counter.size(); ++j){
        while(counter[j]>0){
            if(m_sort_type == SORT_TYPE::ASCENDING){
                arr[i] = j;
            } else {
                arr[arr.size()-1-i] = j;
            }
            --counter[j]; // track duplicates
            ++i;
        }
    }
}

/** @brief sort an array using another array stores the counting of each element of arr into res.
    @param arr is input array
    @param max_val maximum value in arr
    @param res stores the output. By this cost, the algorithm becomes linear.
    @note T(n)=THETA(n+max_value)=O(n). Stability is irrelevant here because we have no satellite data.
          //NOTE: In case of using satellite, data counter needs to have a FIFO collection to ensure stability.
          SEE Cormen's book p. 209 & excercise 8.2-5 at p.211
*/
void Sort::counting_sort_outplace(std::vector<int> arr, uint8_t max_val, std::vector<int>& res) {
    // counter has no collection inside, so stability is irrelevant here.
    std::vector<int> counter(max_val + 1, 0);

    // store number of element arr[i], where the index corresponds to number of arr[i] in arr
    for (int i = 0; i < arr.size(); ++i) {
        counter[arr[i]]++;
    }

    // counter[i] contains number of elements LE to i. This determindes the max pos of i.
    for (int i = 1; i <= max_val; ++i) {
        counter[i] += counter[i - 1];
    }

    // NOTE: If the loop start from 0 upward or from top downwards impacts the stability.
    //       If you use a FIFO collection insid counter, you have to strat from i=0.
    //       For LIFO, you have to start from i=n.
    for (int i = arr.size() - 1; i >= 0;--i) {
        if(m_sort_type == SORT_TYPE::ASCENDING){
            res[counter[arr[i]] - 1] = arr[i];
        } else{
            res[arr.size() - counter[arr[i]]] = arr[i];
        }

        // handles duplicates: decrement the max position of value arr[i] in counter by 1;
        // so the second duplicate can be places in the adjecent left pos.
        counter[arr[i]]--;
    }
}

/** @brief sort a vector of type T in ascending order.
    @note T(n) = O(n * (n-1)) = O(n^2)
 */
template<typename T>
void Sort::insertion_sort(std::vector<T>& arr){
    for (int i = 1; i < arr.size(); i++) {
        T key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key, 
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/** @brief sort float numberes distributed in [0, 1) in ascending order
    @note T(n)=O(n) bucket sort assumes that the input is generated by a random process that 
            distributes elements uniformly and independently over the interval [0, 1).
            SEE Cormen's book p. 215
 */
void Sort::bucket_sort(std::vector<float>& arr){
    uint8_t n{static_cast<uint8_t>(arr.size())};
    // 2D vector is a vector of buckets
    std::vector<std::vector<float>> buckets(n, std::vector<float>{});

    // put each value into a buckt
    for (int i = 0; i < n; ++i) {
        int idx = static_cast<int>(n * arr[i]);
        buckets[idx].push_back(arr[i]);
    }
    // sort each bucket
    for (int i = 0; i < n; ++i) {
        insertion_sort(buckets[i]);
    }

    // concatinate buckets
    arr.clear();
    int i{0};
    while (i < n) {
        arr.insert(arr.end(), buckets[i].begin(), buckets[i].end());
        ++i;
    }
}

/** @brief sort inplace in ascending order using a max_heap. To sort it descending use min_heapfiy().
    @note T(n)=O(n.lg(n)). SEE Cormen's book p.170
 */
void Sort::heap_sort(std::vector<int>& vec){
    build_heap(vec);
    for(int i=0; i<vec.size(); ++i){
        int last_idx = vec.size() -1 - i;
        // insert the largest element (i.e. root) to the end of max_heap
        std::swap(vec[0], vec[last_idx]);
        // heapify from the root 
        if(m_sort_type == SORT_TYPE::ASCENDING){
            max_heapify(vec, 0, last_idx-1);
        } else {
            min_heapify(vec, 0, last_idx-1);
        }
    }
}

/** @brief check if the node with given idx is larger than its children, if not move it down on the tree to where it's larger than its children.
    @note it assumes subtrees under idx are max_heap. T(n)=O(n). SEE Cormen's book p.
    @param idx is the index of node which is max_heapified
    @param last_idx the index of last node in the heap. Is used later in heap_sort to sort inplace by moving the root to the end.
 */
void Sort::max_heapify(std::vector<int>& vec, int idx, int last_idx){
    int left_child_idx = 2*idx+1;
    int right_child_idx = left_child_idx + 1;
    // assume idx has the largest value than its children
    int largest = idx;

    // check there is a left child and its value is larger than the parent's
    if(left_child_idx<=last_idx && vec[left_child_idx]>vec[largest]){
        largest = left_child_idx;
    }

    // check there is a right child and its value is larger than the parent's
    if(right_child_idx<=last_idx && vec[right_child_idx]>vec[largest]){
        largest = right_child_idx;
    }

    // if vec[idx] isn't the largest, swap it with the largest child & continue with that child
    if(largest != idx){
        std::swap(vec[largest], vec[idx]);
        max_heapify(vec, largest, last_idx);
    }
}

/** @brief check if the node with given idx is smaller than its children, if not move it down on the tree to where it's smaller than its children.
    @note it assumes subtrees under idx are min_heap. T(n)=O(n). SEE Cormen's book p.
    @param idx is the index of node which is max_heapified
    @param last_idx the index of last node in the heap. Is used later in heap_sort to sort inplace by moving the root to the end.
 */
void Sort::min_heapify(std::vector<int>& vec, int idx, int last_idx){
    int left_child_idx = 2*idx+1;
    int right_child_idx = left_child_idx + 1;
    // assume idx has the smallest value than its children
    int smallest = idx;

    // check there is a left child and its value is larger than the parent's
    if(left_child_idx<=last_idx && vec[left_child_idx]<vec[smallest]){
        smallest = left_child_idx;
    }

    // check there is a right child and its value is larger than the parent's
    if(right_child_idx<=last_idx && vec[right_child_idx]<vec[smallest]){
        smallest = right_child_idx;
    }

    // if vec[idx] isn't the smallest, swap it with the smallest child & continue with that child
    if(smallest != idx){
        std::swap(vec[smallest], vec[idx]);
        max_heapify(vec, smallest, last_idx);
    }
}

/** @brief convert a vector to min or max heap in-place in a bottom-up manner. It starts from the last parent traverses up to the root.
    @note although there's a for-loop of size n/2 and each call on max_heapify() runs in O(lg(n),
          the running time is even tighter T(n)=O(n). SEE Cormen's book p.167
*/
void Sort::build_heap(std::vector<int>& vec){
    // index of last inner node (i.e. non-leaf node)
    int n = (vec.size()-1)/2;

    for(int i=n; i>=0; --i){
        if(m_sort_type == SORT_TYPE::ASCENDING){
            max_heapify(vec, i, vec.size()-1);
        } else {
            min_heapify(vec, i, vec.size()-1);
        }
    }
}