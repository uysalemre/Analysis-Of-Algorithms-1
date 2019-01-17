//  merge.h
//  AoA1

//  Created by Emre Uysal on 16.10.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.

#ifndef merge_h
#define merge_h
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

// this is a template class because it must have capable to make comparisons with float and string
template <class T>
class Merger
{
    public:
        //merge function gets a column vector in T type and indexes for conquering
        void merge(vector<T>& data,int left,int mid,int right,vector<string>& allData)
        {
            //Create sub arrays and initialize vector size for column and all data
            vector<T> subL, subR;   //left and right sub vectors for column vector
            vector<string> tempAllLeft,tempAllRight;    //left and right sub vectors for all lines
            tempAllLeft.resize(mid-left+2);
            tempAllRight.resize(right-mid+1);
            subL.resize(mid-left+2);
            subR.resize(right-mid+1);
            
            // Create sub vectors with using column vectors
            for(int i = 0; i< mid-left + 1; i++)
            {
                subL[i] = data[left+i];     //sub vector left for column vector
                tempAllLeft[i] = allData[left+i];   //sub vector right for all lines
            }
            for(int j = 0; j< right - mid; j++)
            {
                subR[j] = data[mid+j+1];    //sub vector right for column vector
                tempAllRight[j] = allData[mid+j+1]; //sub vector right for all lines
            }
            //    for debug you can replace comments to see what contains sub arrays in every step
            //    cout<< "Left Sub Array : -----------" <<endl<<endl;
            //    for(vector<string>::iterator i=subL.begin(); i !=subL.end(); i++)
            //    {
            //        cout<<*i<<endl<<endl;
            //    }
            //    cout<< "Right Sub Array : -----------" <<endl<<endl;
            //    for(vector<string>::iterator i=subR.begin(); i !=subR.end(); i++)
            //    {
            //        cout<<*i<<endl<<endl;
            //    }
            
            // make initializations for counters
            int i = 0, j = 0, k = 0 ;
            
            //Compare left sub vector and right sub vector
            while(i<mid-left + 1 && j<right - mid)
            {
                    if(subL[i]<=subR[j])    //left sub vector value smaller or equal than right
                    {
                        data[left+k] = subL[i];
                        allData[left+k] = tempAllLeft[i];   //change all data line
                        i++;
                    }
                    else
                    {
                        data[left+k] = subR[j];
                        allData[left+k] = tempAllRight[j];  //change all data line
                        j++;
                    }
                    k++;
            }
            
            // for remaining elements make initializations
            while(i<mid-left + 1)
            {
                data[left+k] = subL[i];
                allData[left+k] = tempAllLeft[i];
                i++;
                k++;
            }
            while(j<right - mid)
            {
                data[left+k] = subR[j];
                allData[left+k] = tempAllRight[j];
                j++;
                k++;
            }
            
            // for debug replace comment what contains the all data array
            //    cout<< "Data Array : -----------" <<endl<<endl;
            //    for(vector<string>::iterator i=data.begin(); i !=data.end(); i++)
            //    {
            //        cout<<*i<<endl<<endl;
            //    }
            //
            //    cout<< "ALL  Array : -----------" <<endl<<endl;
            //    for(vector<string>::iterator i=allData.begin(); i !=allData.end(); i++)
            //    {
            //        cout<<*i<<endl<<endl;
            //    }
        };
    
        // this function makes devide operation using recursion methodology
        void mergeSort(vector<T>& data, int left, int right,vector<string>& allData)
        {
            if(left<right)
            {
                int midd = (left+right)/2;  //calculate midpoint
                mergeSort(data,left,midd,allData);  //call devide operation until left part devided
                mergeSort(data,midd+1,right,allData);//call devide operation until right part devided
                merge(data,left,midd,right,allData);//call conquer operation
            }
        };
    
        //this function writes into file sorted data
        void writeToFile(vector<string>& data,vector<string>& header)
        {
            ofstream outputFile;
            outputFile.open("sorted.csv");
            if(outputFile.is_open())
            {
                outputFile<<header[0]<<endl;    //write header into file
                for(vector<string>::iterator i=data.begin(); i != data.end(); i++)//iterate over data
                {
                    outputFile<<*i<<endl;   //write line into file
                }
            }
            else
            {
                cout<<"Cannot open sorted.csv"<<endl;
                return;
            }
            outputFile.close(); //close file
        };
};

#endif /* merge_h */
