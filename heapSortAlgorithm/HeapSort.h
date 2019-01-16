//
//  HeapSort.h
//  AoA2Class
//
//  Created by Emre Uysal on 17.11.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.
//

#ifndef HeapSort_h
#define HeapSort_h
#include "Node.h"

class HeapSort
{
public:
    //getter functions
    int parent(int);                //for getting the parent index
    int left(int);                  //for getting left index
    int right(int);                 //for getting right index
    
    //max-min heapify functions
    void maxHeapifyT(Node *, int);    //max Heapify function for totalCalls
    void minHeapifyT(Node *, int);    //min Heapify function for totalCalls
    void maxHeapifyP(Node *, int);    //max Heapify function for performance
    void minHeapifyP(Node *, int);    //min Heapify function for performance
    
    //build max-min heap functions
    void buildMaxHeapT(Node *);       //build Max Heap function for totalCalls
    void buildMinHeapT(Node *);       //build Min Heap function for totalCalls
    void buildMaxHeapP(Node *);       //build Max Heap function for performance
    void buildMinHeapP(Node *);       //build Min Heap function for performance
    
    //extract max-min functions returns Node
    Node * heapExtractMaxP(Node *arr);   //extract max function for performance
    Node * heapExtractMaxT(Node *arr);   //extract max function for totalCalls
    Node * heapExtractMinP(Node *arr);   //extract min function for performance
    Node * heapExtractMinT(Node *arr);   //extract min function for totalCalls
    
    //increase key functions
    void heapIncreaseKeyP(Node *,int,int);    //increase key function for performance
    void heapIncreaseKeyT(Node *,int,int);    //increase key function for totalCalls
    void heapIncreaseKeyPforInsert(Node *,int,int,int,int);    //increase key function for perforamce and it sets the id,performance,totalCalls
    void heapIncreaseKeyTforInsert(Node *,int,int,int,int);    //increase key function for totalCalls and it sets the id,performance,totalCalls
    
    //insert functions
    void insertT(Node *arr, int,int,int);  //insert function for totalCalls
    void insertP(Node *arr, int,int,int);  //insert function for performance
    
    //heapSort functions
    void heapSortMaxP(Node *);   //HeapSort Function for builded performance Max Heap
    void heapSortMinP(Node *);   //heapSort function for builded performance min heap
    void heapSortMaxT(Node *);   //HeapSort Function for builded totalCalls Max Heap
    void heapSortMinT(Node *);   //heapSort function for builded totalCalls min heap
    
    //performance calculator and necesary variables
    int calculatePerformance(int ,int ,int );   //performance calculation
    int heapsize,length;            //heapsize and length variables
   
};


#endif /* HeapSort_h */
