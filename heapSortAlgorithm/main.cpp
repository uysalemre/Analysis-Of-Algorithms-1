//
//  main.cpp
//  AoA2Class
//
//  Created by Emre Uysal on 17.11.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <string.h>
#include "HeapSort.h"
#include "Node.h"

using namespace std;

int main(int argc, const char * argv[])
{
    //strings for coming parameters from the file
    string empId,totalCalls,posCalls,negCalls,line;

    Node *performM = new Node[1600];    //for max performance heap
    Node *totCallM = new Node[1600];    //for max total Call heap
    Node *performN = new Node[1600];    //for min performance heap
    Node *totCallN = new Node[1600];    //for min total Call heap
    
    ifstream day1;
    day1.open("day1.csv");  //open file
    int counter = 0;
    if(day1.is_open())
    {
        while (!day1.eof())
        {
            getline(day1, line);                    //get the line
            stringstream ss(line);                   //parse the line
            getline(ss, empId, ',');                //get the line into empId until ,
            getline(ss, totalCalls, ',');           //get the line into empId until ,
            getline(ss, posCalls, ',');             //get the line into posCalls until ,
            getline(ss, negCalls, ',');             //get the line into negCalls until ,
            
            //convert strings to integer
            int temp1 = atoi(empId.c_str());
            int temp2 = atoi(totalCalls.c_str());
            int temp3 = atoi(posCalls.c_str());
            int temp4 = atoi(negCalls.c_str());
            
            //calculate performance and push the array
            HeapSort calculator;
            int performanceScore = calculator.calculatePerformance(temp2, temp3, temp4);
            
            //assign the values into arrays
            //all arrays are the type of Node Class so they have id,performance and totalCalls
            performM[counter].empId = temp1;
            performM[counter].totalCalls = temp2;
            performM[counter].performance = performanceScore;
            
            performN[counter].empId = temp1;
            performN[counter].totalCalls = temp2;
            performN[counter].performance = performanceScore;
            
            totCallM[counter].empId = temp1;
            totCallM[counter].totalCalls = temp2;
            totCallM[counter].performance = performanceScore;
            
            totCallN[counter].empId = temp1;
            totCallN[counter].totalCalls = temp2;
            totCallN[counter].performance = performanceScore;
            counter++;
        }
    }
    else
    {
        cout<<"Unable to read day1.csv"<<endl;
    }
    day1.close();
    
    clock_t time;
    time = clock(); // run clock
    HeapSort object1;                           //create an object from HeapSort Class
    object1.length = counter;                   //set the length of the heap
    object1.buildMaxHeapP(performM);             //build the max heap for performance M array
    
    Node *temp = new Node[counter];             //create a temp Node array
    memcpy(temp, performM, counter*sizeof(Node));//copy the original perfermance M array into the temp
    HeapSort objectTemp;                        //create an object from HeapSort class
    objectTemp.length = counter;                //set the length of the heap
    objectTemp.buildMaxHeapP(temp);              //create max heap
    
    HeapSort object2;                           //create an object from HeapSort Class
    object2.length = counter;                   //set the length of the heap
    object2.buildMinHeapP(performN);             //build the min heap for the performance N array
    
    Node *temp2 = new Node[counter];             //create a temp Node array
    memcpy(temp2, performN, counter*sizeof(Node));//copy the original performance N array into the temp
    HeapSort objectTemp2;                        //create an object from HeapSort class
    objectTemp2.length = counter;                //set the length of the heap
    objectTemp2.buildMinHeapP(temp2);             //create min heap
   
    HeapSort object3;                            //create an object from HeapSort Class
    object3.length = counter;                    //set the length of the heap
    object3.buildMaxHeapT(totCallM);              //build the max heap for the total Calls M array
    
    Node *temp3 = new Node[counter];             //create a temp Node array
    memcpy(temp3, totCallM, counter*sizeof(Node));//copy the original total Call M array into temp
    HeapSort objectTemp3;                        //create an object from HeapSort
    objectTemp3.length = counter;                //set the heap size
    objectTemp3.buildMaxHeapT(temp3);             //create max heap
    
    HeapSort object4;                            //create an object frım HeapSort
    object4.length = counter;                    //set the length of the heap
    object4.buildMinHeapT(totCallN);              //build the min heap for total Calls N array
    
    Node *temp4 = new Node[counter];              //create a temp Node array
    memcpy(temp4, totCallN, counter*sizeof(Node));//copy the original total Call N into temp
    HeapSort objectTemp4;                        //create an object from HeapSort class
    objectTemp4.length = counter;                //set the length of the heap
    objectTemp4.buildMinHeapT(temp4);             //create min heap

    //in this I printed the necessary output by using extract min/max functions
    cout<<"AFTER - day1.csv"<<endl;
    cout<<"MAXIMUM PERFORMANCE : " <<objectTemp.heapExtractMaxP(temp)->empId<<","<<objectTemp.heapExtractMaxP(temp)->empId<<","<<objectTemp.heapExtractMaxP(temp)->empId<<endl;
    cout<<"MINUMUM PERFORMANCE : "  <<objectTemp2.heapExtractMinP(temp2)->empId<<","<<objectTemp2.heapExtractMinP(temp2)->empId<<","<<objectTemp2.heapExtractMinP(temp2)->empId<<endl;
    cout<<"MAXIMUM CALLS : "<<objectTemp3.heapExtractMaxT(temp3)->empId<<","<<objectTemp3.heapExtractMaxT(temp3)->empId<<","<<objectTemp3.heapExtractMaxT(temp3)->empId<<endl;
    cout<<"MINIMUM CALLS : "<<objectTemp4.heapExtractMinT(temp4)->empId<<","<<objectTemp4.heapExtractMinT(temp4)->empId<<","<<objectTemp4.heapExtractMinT(temp4)->empId<<endl;
    cout<<"Elapsed time "<< ((float)time)/CLOCKS_PER_SEC <<" seconds"<<endl;    //write time to console
    cout<<endl;
    
    // extract operations happened on the temporary heaps, so I can delete them
    delete[] temp;
    delete[] temp2;
    delete[] temp3;
    delete[] temp4;
    
    // I created filenames array for reading other files in a sequence
    string files[10] = {"day2.csv","day3.csv","day4.csv","day5.csv","day6.csv","day7.csv","day8.csv","day9.csv","day10.csv"};
    bool reader = true;
    int fileCounter = 0;        //fileCounter variable for counting the arrays elements
    HeapSort tempCalc;          //create a calculator object for calculating performance
    while (reader)
    {   clock_t time;
        ifstream otherFiles;
        otherFiles.open(files[fileCounter].c_str()); //open the file
        if (otherFiles.is_open())
        {
            while (!otherFiles.eof())
            {
                //set the flags for finded employee
                bool findedForPerforM = false;
                bool findedForPerforN = false;
                bool findedForCallM = false;
                bool findedForCallN = false;
                //read the lines
                getline(otherFiles, line);
                stringstream ss(line);
                getline(ss, empId, ',');
                getline(ss, totalCalls, ',');
                getline(ss, posCalls, ',');
                getline(ss, negCalls, ',');
                int temp1 = atoi(empId.c_str());
                int temp2 = atoi(totalCalls.c_str());
                int temp3 = atoi(posCalls.c_str());
                int temp4 = atoi(negCalls.c_str());
                //calculate the performance
                int performanceVal = tempCalc.calculatePerformance(temp2, temp3, temp4);
                //make search operations in the for loops for each heap and set the flag for each heap
                for(int i = 0; i < object1.length; i++)
                {
                    if(performM[i].empId == temp1 && findedForPerforM == false)
                    {
                        //if the empId finded call the increase key
                        object1.heapIncreaseKeyP(performM, i, performanceVal);
                        findedForPerforM = true;
                    }
                }
                for(int i = 0; i < object2.length; i++)
                {
                    if(performN[i].empId == temp1 && findedForPerforN == false)
                    {
                        //if the empId finded call the increase key
                        object2.heapIncreaseKeyP(performN, i, performanceVal);
                        findedForPerforN = true;
                    }
                }
                for(int i = 0; i < object3.length; i++)
                {
                    if(totCallM[i].empId == temp1 && findedForCallM == false)
                    {
                        //if the empId finded call the increase key
                        object3.heapIncreaseKeyT(totCallM, i, temp2);
                        findedForCallM = true;
                    }
                }
                for(int i = 0; i < object4.length; i++)
                {
                    if(totCallN[i].empId == temp1 && findedForCallN == false)
                    {
                        //if the empId finded call the increase key
                        object4.heapIncreaseKeyT(totCallN, i, temp2);
                        findedForCallN = true;
                    }
                }
                if (findedForPerforM == false)
                {
                    //if not finded the empId call the insert
                    object1.insertP(performM, temp1, performanceVal, temp2);
                    object1.length++;
                }
                if (findedForPerforN == false)
                {
                    //if not finded the empId call the insert
                    object2.insertP(performN, temp1, performanceVal, temp2);
                    object2.length++;
                }
                if (findedForCallM == false)
                {
                    //if not finded the empId call the insert
                    object3.insertT(totCallM, temp1, performanceVal, temp2);
                    object3.length++;
                }
                if (findedForCallN == false)
                {
                    //if not finded the empId call the insert
                    object4.insertT(totCallN, temp1, performanceVal, temp2);
                    object4.length++;
                }

            }
            time = clock(); // run clock
            //copy the original heaps into temp heaps
            Node *temp = new Node[object1.length];
            memcpy(temp, performM, object1.length*sizeof(Node));
            HeapSort objectTemp;
            objectTemp.length = counter;
            objectTemp.buildMaxHeapP(temp);
            
            Node *temp2 = new Node[object2.length];
            memcpy(temp2, performN, object2.length*sizeof(Node));
            HeapSort objectTemp2;
            objectTemp2.length = counter;
            objectTemp2.buildMinHeapP(temp2);
            
            Node *temp3 = new Node[object3.length];
            memcpy(temp3, totCallM, object3.length*sizeof(Node));
            HeapSort objectTemp3;
            objectTemp3.length = counter;
            objectTemp3.buildMaxHeapT(temp3);
            
            Node *temp4 = new Node[object4.length];
            memcpy(temp4, totCallN, object4.length*sizeof(Node));
            HeapSort objectTemp4;
            objectTemp4.length = counter;
            objectTemp4.buildMinHeapT(temp4);

            //print the output by extraxcting values from the temporary heaps
            cout<<"AFTER - "<<files[fileCounter]<<endl;
            cout<<"MAXIMUM PERFORMANCE : " <<objectTemp.heapExtractMaxP(temp)->empId<<","<<objectTemp.heapExtractMaxP(temp)->empId<<","<<objectTemp.heapExtractMaxP(temp)->empId<<endl;
            cout<<"MINUMUM PERFORMANCE : "  <<objectTemp2.heapExtractMinP(temp2)->empId<<","<<objectTemp2.heapExtractMinP(temp2)->empId<<","<<objectTemp2.heapExtractMinP(temp2)->empId<<endl;
            cout<<"MAXIMUM CALLS : "<<objectTemp3.heapExtractMaxT(temp3)->empId<<","<<objectTemp3.heapExtractMaxT(temp3)->empId<<","<<objectTemp3.heapExtractMaxT(temp3)->empId<<endl;
            cout<<"MINIMUM CALLS : "<<objectTemp4.heapExtractMinT(temp4)->empId<<","<<objectTemp4.heapExtractMinT(temp4)->empId<<","<<objectTemp4.heapExtractMinT(temp4)->empId<<endl;
            cout<<"Elapsed time "<< ((float)time)/CLOCKS_PER_SEC <<" seconds"<<endl;    //write time to console
            cout<<endl;
            
            //delete the temporary heaps
            delete[] temp;
            delete[] temp2;
            delete[] temp3;
            delete[] temp4;
            
            fileCounter++;

        }
        else
        {
            reader = false;
        }
        otherFiles.close();
    }

    //THIS PART IS SORTING THE NUMBERS.CSV FILE
    Node *number = new Node[2000000];       //create a Node array with the size of 2000000
    ifstream numbers;
    string liner;
    int counterNumber = 0;
    numbers.open("numbers.csv");            //open the file
    if(numbers.is_open())
    {
        while (!numbers.eof())
        {
            getline(numbers,liner);
            int value = atoi(liner.c_str());            //convert the line to integer
            number[counterNumber].empId = value;       //set the values
            number[counterNumber].performance = value;
            number[counterNumber].totalCalls = value;
            counterNumber++;
        }
    }
    else
    {
        cout<<" Can not open numbers.csv "<<endl;
    }

    HeapSort newheap;                   //create a heap object
    newheap.length = counterNumber;     //set the length
    newheap.buildMaxHeapP(number);       //build the max heap with number array
    ofstream file;
    file.open("sorted.csv");             //open a new file
    if(file.is_open())
    {
        clock_t time;                   //for calculating the elapsed time
        for (int i = 0; i<10; i++)      //in ten steps
        {
            time = clock(); // run clock
            cout<<"height is : "<<ceil(log2(newheap.heapsize+1))-1<<" in the "<<i<<" step "<<endl;  //find the height of the heap
            for (int j = 0; j<200000; j++)      //by getting 200000 elements in a one step
            {
                Node *newnode = new Node;       // create a Node
                newnode = newheap.heapExtractMaxP(number);  // extract the max value
                file<<newnode->empId<<endl; //put it into the file
                delete newnode;     //delete the node
            }
            time = clock()-time;    //stop clock
            cout<<"Elapsed time "<< ((float)time)/CLOCKS_PER_SEC <<" seconds"<<endl;    //write time to console
        }
    }
    else
    {
        cout<<"Cant able to create sorted.csv"<<endl;
    }
    file.close();
    //at the end sorted.csv is sorted in descending order
    return 0;
}
