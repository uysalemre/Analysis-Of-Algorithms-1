//
//  HeapSort.cpp
//  AoA2Class
//
//  Created by Emre Uysal on 17.11.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.
//

#include <iostream>
#include "HeapSort.h"

using namespace std;

//returns parent index
int HeapSort::parent(int index)
{
    return index/2;
}

//returns right node index
int HeapSort::right(int index)
{
    return 2*index+1;
}

//returns left node index
int HeapSort::left(int index)
{
    return 2*index;
}

//max Heapify function for performance score
void HeapSort::maxHeapifyP(Node *arr, int index)
{
    int leftVal = left(index);
    int rightVal = right(index);
    int largest;
    if(leftVal < heapsize && arr[leftVal].performance>arr[index].performance)
    {
        largest = leftVal;
    }
    else
    {
        largest = index;
    }
    if(rightVal < heapsize && arr[rightVal].performance>arr[largest].performance)
    {
        largest = rightVal;
    }
    if(largest != index)
    {
        swap(arr[index],arr[largest]);
        maxHeapifyP(arr,largest);
    }
}

//min Heapify function for performance score
void HeapSort::minHeapifyP(Node *arr, int index)
{
    int leftVal = left(index);
    int rightVal = right(index);
    int smallest;
    if(leftVal < heapsize && arr[leftVal].performance<arr[index].performance)
    {
        smallest = leftVal;
    }
    else
    {
        smallest = index;
    }
    if(rightVal < heapsize && arr[rightVal].performance<arr[smallest].performance)
    {
        smallest = rightVal;
    }
    if(smallest != index)
    {
        swap(arr[index],arr[smallest]);
        minHeapifyP(arr,smallest);
    }
}

//max heapify function for total calls
void HeapSort::maxHeapifyT(Node *arr, int index)
{
    int leftVal = left(index);
    int rightVal = right(index);
    int largest;
    if(leftVal < heapsize && arr[leftVal].totalCalls>arr[index].totalCalls)
    {
        largest = leftVal;
    }
    else
    {
        largest = index;
    }
    if(rightVal < heapsize && arr[rightVal].totalCalls>arr[largest].totalCalls)
    {
        largest = rightVal;
    }
    if(largest != index)
    {
        swap(arr[index],arr[largest]);
        maxHeapifyT(arr,largest);
    }
}

//min Heapify function for total calls
void HeapSort::minHeapifyT(Node *arr, int index)
{
    int leftVal = left(index);
    int rightVal = right(index);
    int smallest;
    if(leftVal < heapsize && arr[leftVal].totalCalls<arr[index].totalCalls)
    {
        smallest = leftVal;
    }
    else
    {
        smallest = index;
    }
    if(rightVal < heapsize && arr[rightVal].totalCalls<arr[smallest].totalCalls)
    {
        smallest = rightVal;
    }
    if(smallest != index)
    {
        swap(arr[index],arr[smallest]);
        minHeapifyT(arr,smallest);
    }
}

//build max heap function for performance it calls maxHeapify performance
void HeapSort::buildMaxHeapP(Node *arr)
{
    heapsize = length;

    for (int i=length/2-1; i>=0; i--)
    {
        maxHeapifyP(arr, i);
    }
}

//build min heap for performance it calls minHeapify performance
void HeapSort::buildMinHeapP(Node *arr)
{
    heapsize = length;
    for(int i = length/2-1; i>=0;i--)
    {
        minHeapifyP(arr, i);
    }
}

//build max heap total calls, it calls maxHeapify totalCalls
void HeapSort::buildMaxHeapT(Node *arr)
{
    heapsize = length;
    for (int i=length/2-1; i>=0; i--)
    {
        maxHeapifyT(arr, i);
    }
}

//build min heap total calls, it calls minHeapify totalCalls
void HeapSort::buildMinHeapT(Node *arr)
{
    heapsize = length;
    for(int i = length/2-1; i>=0;i--)
    {
        minHeapifyT(arr, i);
    }
}

//heapSort by increasing order for performance
void HeapSort::heapSortMaxP(Node *arr)
{
    buildMaxHeapP(arr);
    for (int i=length-1; i>=0; i--)
    {
        swap(arr[0], arr[i]);
        heapsize--;
        maxHeapifyP(arr, 0);
    }
}

//heapSort by decreasing order for performance
void HeapSort::heapSortMinP(Node *arr)
{
    buildMinHeapP(arr);
    for (int i=length-1; i>=0; i--)
    {
        swap(arr[0], arr[i]);
        heapsize--;
        minHeapifyP(arr, 0);
    }
}

//heapSort by increasing order for total calls
void HeapSort::heapSortMaxT(Node *arr)
{
    buildMaxHeapT(arr);
    for (int i=length-1; i>=0; i--)
    {
        swap(arr[0], arr[i]);
        heapsize--;
        maxHeapifyT(arr, 0);
    }
}

//heapSort by decreasing order for totalcalls
void HeapSort::heapSortMinT(Node *arr)
{
    buildMinHeapT(arr);
    for (int i=length-1; i>=0; i--)
    {
        swap(arr[0], arr[i]);
        heapsize--;
        minHeapifyT(arr, 0);
    }
}

//extract max function for performance
Node * HeapSort::heapExtractMaxP(Node *arr)
{
    if(heapsize< 1)
    {
        cout<<"Heap underflow"<<endl;
        return NULL;
    }
    Node *newnode = new Node[1];
    newnode[0] = arr[0];
    arr[0] = arr[heapsize-1];
    heapsize--;
    maxHeapifyP(arr, 0);
    return newnode;
}

//extract max function for total calls
Node * HeapSort::heapExtractMaxT(Node *arr)
{
    if(heapsize< 1)
    {
        cout<<"Heap underflow"<<endl;
        return NULL;
    }
    Node *newnode = new Node[1];
    newnode[0] = arr[0];
    arr[0] = arr[heapsize-1];
    heapsize--;
    maxHeapifyT(arr, 0);
    return newnode;
}

//extract min function for performance
Node * HeapSort::heapExtractMinP(Node *arr)
{
    if(heapsize< 1)
    {
        cout<<"Heap underflow"<<endl;
        return NULL;
    }
    Node *newnode = new Node[1];
    newnode[0] = arr[0];
    arr[0] = arr[heapsize-1];
    heapsize--;
    minHeapifyT(arr, 0);
    return newnode;
}

//extract min function for total calls
Node * HeapSort::heapExtractMinT(Node *arr)
{
    if(heapsize< 1)
    {
        cout<<"Heap underflow"<<endl;
        return NULL;
    }
    Node *newnode = new Node[1];
    newnode[0] = arr[0];
    arr[0] = arr[heapsize-1];
    heapsize--;
    minHeapifyT(arr, 0);
    return newnode;
}

//increase key function for performance
void HeapSort::heapIncreaseKeyP(Node *arr, int index, int key)
{
    if(key<arr[index].performance)
    {
        return;
    }
    arr[index].performance += key;  //updates the performance by adding the coming value
    while(index>0 && arr[parent(index)].performance < arr[index].performance)
    {
        swap(arr[index], arr[parent(index)]);
        index = parent(index);
    }
}

//increase key function for total calls
void HeapSort::heapIncreaseKeyT(Node *arr, int index, int key)
{
    if(key<arr[index].totalCalls)
    {
        return;
    }
    arr[index].totalCalls += key; //updates the totalcalls by adding the coming value
    while(index>0 && arr[parent(index)].totalCalls < arr[index].totalCalls)
    {
        swap(arr[index], arr[parent(index)]);
        index = parent(index);
    }
}

//insert function for totalcalls
void HeapSort::insertT(Node *arr, int id,int performance, int totCall)
{
    //set the last element
    arr[length].empId = -1;
    arr[length].performance = -1;
    arr[length].totalCalls = -1;
    //then update it by using coming values
    heapIncreaseKeyPforInsert(arr, length, id, performance, totCall);
}

//insert function for performance
void HeapSort::insertP(Node *arr, int id,int performance, int totCall)
{
    //set the last element
    arr[length].empId = -1;
    arr[length].performance = -1;
    arr[length].totalCalls = -1;
    //then update it by using coming values
    heapIncreaseKeyTforInsert(arr, length, id,performance,totCall);
}

//calculate performance function and it returns the performance score
int HeapSort::calculatePerformance(int call, int posfeed, int negfeed)
{
    return 2*call+(posfeed-negfeed);
}

//increase key function for performance by setting id,performance and total call values
void HeapSort::heapIncreaseKeyPforInsert(Node *arr, int index, int id, int performance, int totCall)
{
    if(performance<arr[index].performance)
    {
        return;
    }
    //set the necessary values
    arr[index].empId = id;
    arr[index].performance = performance;
    arr[index].totalCalls = totCall;
    while(index>0 && arr[parent(index)].performance < arr[index].performance)
    {
        swap(arr[index], arr[parent(index)]);
        index = parent(index);
    }
}

//increase key function for total calls and it sets the id,performance,totalCall values
void HeapSort::heapIncreaseKeyTforInsert(Node *arr, int index, int id, int performance, int totCall)
{
    if(totCall<arr[index].totalCalls)
    {
        return;
    }
    //set the values
    arr[index].empId = id;
    arr[index].performance = performance;
    arr[index].totalCalls = totCall;
    while(index>0 && arr[parent(index)].totalCalls < arr[index].totalCalls)
    {
        swap(arr[index], arr[parent(index)]);
        index = parent(index);
    }
}


