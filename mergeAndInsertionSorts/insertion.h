//  insertion.h
//  AoA1

//  Created by Emre Uysal on 16.10.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.

#ifndef insertion_h
#define insertion_h
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

// this is a template class because it must have capability for comparisons with float and string
template <class T>
class Insertion
{
    public:
        void InsertionSort(vector<T>& values,vector<string>& allData)   //takes T column and all string data
        {
            int counter;
            for(int i = 1 ; i < values.size(); i++) //iteration starts from second element
            {
                counter = i-1;
                T status = values[i];   //T type status variable for using as a key
                string all_stat = allData[i];   //for all lines status variable
                while(counter>=0 && values[counter]>status) //conditional loop checks the values and counter
                {
                    values[counter+1] = values[counter];    //make initialization for column
                    allData[counter+1] = allData[counter];  //make initialization for line
                    counter--;  //decrement counter
                }
                values[counter+1] = status;     //make changes in the vectors elements positions in column vector
                allData[counter+1] = all_stat;  //in all lines vector make changes for elements positions
            }
        };
    
        void writeToFile(vector<string> data,vector<string> header) // get all lines and header line
        {
            ofstream outputFile;
            outputFile.open("sorted.csv");  //open file
            if(outputFile.is_open())
            {
                outputFile<<header[0]<<endl;    //write header into file
                //iterate over the vector
                for(vector<string>::iterator i=data.begin(); i != data.end(); i++)
                {
                    outputFile<<*i<<endl;  //write sorted content into file
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

#endif /* insertion_h */
