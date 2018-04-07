#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include<vector>
#include<stdexcept>
template<class T>
class BinaryHeap{
    public:
        explicit BinaryHeap(int capacity=100):array(capacity){  //resize the size of the array
            currentsize = 0;            //a new heap hold zero item
        }
        explicit BinaryHeap(const std::vector<T>&items);  //receive a list of obj and insert them successively to heap
        bool isEmpty()const;            //judge by currentsize
        const T& findMin()const;        // return array[1] which means the root item

        void insert(const T&x);         
        void deleteMin();
        void deleteMin(T&minItem);
        void makeEmpty();           //clear the array and zero currentsize
        int getsize()const;
        void showheap()const;
    //private:
        int currentsize;            //show the size of the heap ++or--when insert or delete
        std::vector<T>array;             //an array to store the data of the heap
        void buildheap();           //
        void percolateDown(int);       //
};
#endif
