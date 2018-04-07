#include"heaphop.h"
#include<vector>
#include<iostream>
using namespace std;
template<class T>
BinaryHeap<T>::BinaryHeap(const vector<T>&items):array(items.size()+10),currentsize(items.size()){
    for(int i=0;i<items.size();i++){
        array[i+1] = items[i];
    }
    buildheap();
}
template<class T>
int BinaryHeap<T>::getsize()const{
    return currentsize;
}
template<class T>
bool BinaryHeap<T>::isEmpty()const{
    if(!currentsize)    return true;
    else    return false;
}
template<class T>
const T& BinaryHeap<T>::findMin()const{
    return array[1];
}

template<class T>
void BinaryHeap<T>::insert(const T&x){
    if(currentsize==array.size()-1){        //if the array can't hold all these elements 
        array.resize(array.size()*2);
    }
    //Percolate up
    int hole = currentsize +1;
    for(;hole>1&&x<array[hole/2];hole/=2){
        array[hole] = array[hole/2];
    }
    array[hole] = x;
    currentsize++;
}

template<class T>
void BinaryHeap<T>::deleteMin(){
    if(isEmpty()){
        cout<<"empty heap";
        abort();
    }
    array[1] = array[currentsize--];        //replace the root with the last element and percolateDown the root
    percolateDown(1);
}
template<class T>
void BinaryHeap<T>::deleteMin(T&minItem){
    if(isEmpty()){
        cout<<"empty heap";
        abort();
    }
    minItem = array[1];                     //a reference to get the minItem
    array[1] = array[currentsize--];        //replace the root with the last element and percolateDown the root
    percolateDown(1);                       //adapt the heap
}
template<class T>
void BinaryHeap<T>::makeEmpty(){
    array.clear();
    currentsize=0;
}
template<class T>
void BinaryHeap<T>::buildheap(){            //undone
    for(int i =currentsize/2;i>0;i--)
        percolateDown(i);
}

template<class T>
void BinaryHeap<T>::percolateDown(int hole){
    int child;
    T temp = array[hole];
    while(hole*2<=currentsize){
        child =hole*2;
        if(child!=currentsize&&array[child]>array[child+1]){    //decide take the left or the right
            child++;
        }
        if(array[child]<temp){      
            array[hole] = array[child];
        }
        else break;
        hole = child;
    }
    array[hole] = temp;

}
template<class T>
void BinaryHeap<T>::showheap()const{
    for(int i=0;i<array.size();i++)
        cout<<array[i]<<" ";
}
