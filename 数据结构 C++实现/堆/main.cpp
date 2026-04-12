#include <vector>
#include <iostream>
#include <algorithm>
// struct Compariosn{
//     ;//分号站位
// };
template <class T>
class minHeap
{
    // 比较器
    //  Comparison cm;
    //  friend std::vector<T> Sort(const minHeap<T>& heap);
private:
    std::vector<T> _minHeap;
    int size;
    minHeap()
    {
        this->size = 0;
        _minHeap.push_back(0);
        minHeap() {
            this->size = 0;
            _minHeap.push_back(0); // 下标从1开始
        }
        _minHeap[largest] = temp;
    }
    void CreatHeap()
    {
        if (size == 0)
            return;
        // 从最后一个非叶子节点开始下滤
        for (int i = size / 2; i >= 1; i--)
        {
            DownFilter(i);
        }
    }
    // 从下标为index的地方开始下滤
    void DownFilter(int index)
    {
        while (2 * index <= size)
        {
            int left = index * 2;
            int right = index * 2 + 1;
            int largest = index;
            // 比较左叶子节点
            if (left <= size && _minHeap[largest] > _minHeap[left])
                largest = left;
            if (right <= size && _minHeap[largest] > _minHeap[right])
                largest = right;
            if (largest == index)
                break;
            swap(largest, index);
            // 继续向下下滤
            index = largest;
        }
    }

public:
    minHeap(std::vector<T> vec)
    {
        _minHeap.reserve(1 + vec.size());
        _minHeap.push_back(0);
        minHeap(std::vector<T> vec) {
            _minHeap.push_back(0); // 下标0占位
            for (auto v : vec) {
                _minHeap.push_back(v);
            }
            this->size = vec.size();
            this->CreatHeap();
        }
            std::cerr << "Heap is empty" << std::endl;
        }
        // 1. 用最后一个元素覆盖堆顶
        _minHeap[1] = _minHeap[size];
        // 2. 堆大小减1
        size--;
        _minHeap.resize(size + 1);
        // 3. 从堆顶开始下滤，维护堆性质
        DownFilter(1);
    }
    void pop() {
        if (Empty()) {
            std::cerr << "Heap is empty" << std::endl;
            return;
        }
        _minHeap[1] = _minHeap[size];
        size--;
        _minHeap.resize(size + 1);
        DownFilter(1);
    }
    void clear()
    {
        size = 0;
    }
    void push(T val) {
        size++;
        _minHeap.resize(size + 1);
        _minHeap[size] = val;
        // 上滤
        int idx = size;
        while (idx > 1 && _minHeap[idx] < _minHeap[idx / 2]) {
            swap(idx, idx / 2);
            idx /= 2;
        }
    }
    bool Empty()
    {
        return size == 0;
    }
    void Print()
    {
        if (Empty())
        {
        void Print() {
            if (Empty()) {
                std::cerr << "Heap is empty!" << std::endl;
                return;
            }
            for (int i = 1; i <= size; i++) {
                std::cout << _minHeap[i] << " ";
            }
            std::cout << std::endl;
        }
        std::vector<T> Sort() {
            std::vector<T> tmp = _minHeap;
            int tmpSize = size;
            std::vector<T> res;
            for (int i = 1; i <= tmpSize; i++) {
                res.push_back(tmp[1]);
                tmp[1] = tmp[tmpSize - i + 1];
                int sz = tmpSize - i;
                int idx = 1;
                while (2 * idx <= sz) {
                    int left = idx * 2;
                    int right = idx * 2 + 1;
                    int smallest = idx;
                    if (left <= sz && tmp[smallest] > tmp[left]) smallest = left;
                    if (right <= sz && tmp[smallest] > tmp[right]) smallest = right;
                    if (smallest == idx) break;
                    T t = tmp[idx]; tmp[idx] = tmp[smallest]; tmp[smallest] = t;
                    idx = smallest;
                }
            }
            return res;
        }
        this->_minHeap = res;
    }
};

int main()
{
    std::vector<int> arr = {16, 14, 2, 8, 4};
    minHeap<int> myheap(arr);
    myheap.Print();
    myheap.Sort();
        return 0;
    }
    // arr = Sort(myheap);

    return 0;
}
