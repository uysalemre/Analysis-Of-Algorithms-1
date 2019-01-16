//  main.cpp
//  AnalysisOfAlgorithms1
//  150160510
//  Created by Emre Uysal on 13.10.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <vector>
#include <time.h>
#include "merge.h"
#include "insertion.h"

using namespace std;

int main(int argc, const char * argv[]) {
    //create vectors for all lines and header line also for timestamp and last_price columns
    vector<string> allValues,timeParam,header;
    vector<float> priceColumn;
    //convert total data lines to integer for reading spesific number of lines
    int numOfFields = atoi(argv[6]);
    //string parameters for passing and initializing to vectors using getline
    string line,timestamp,last_price;
    
    // read from file into vectors
    ifstream dataFile;
    dataFile.open("log_inf.csv");   //open file
    if(dataFile.is_open())          //control for opened or not
    {
        getline(dataFile,line); // get the header line
        header.push_back(line); // push the headers into header vector
        //control total number of lines and file ending
        while(!dataFile.eof() && numOfFields)
        {
            getline(dataFile, line);       // get all line
            stringstream ss(line);         // parse the line for getting columns
            getline(ss, timestamp, ',');   //get timestamp column using delimeter
            getline(ss, last_price, ',');  //pass instrument_token column using delimeter
            getline(ss, last_price, ',');  //get last_price column using delimeter
            
            allValues.push_back(line);  //push all line into allValues vector
            timeParam.push_back(timestamp); //push timestamp into timeParam vector
            priceColumn.push_back(atof(last_price.c_str())); //convert string to float and push the last_price into vector
            --numOfFields;  //decrease the total number of line that needs to read
        }
    }
    else
    {
        cout<<"Unable to read file .";  //give error message if cannot read file
    }
    dataFile.close();   //close file
    clock_t time;
    
    //make categorizations according to command line parameters
    if(strcmp(argv[2], "m") == 0)   //-algo is merge
    {
        
        if(strcmp(argv[4],"t")==0)  //criteration is timestamp
        {
            Merger <string> mergeForTime;   //create an object from class and give string to template class parameter
            time = clock(); // run clock
            mergeForTime.mergeSort(timeParam, 0, timeParam.size()-1, allValues);    //call sort function for timestamp
            time = clock()-time;    //stop clock
            cout<<"Elapsed time "<< ((float)time)/CLOCKS_PER_SEC <<" seconds"<<endl;    //write time to console
            mergeForTime.writeToFile(allValues, header);    //call function for writing into file
        }
        else if(strcmp(argv[4],"p")==0) //criteration is last_price
        {
            Merger <float> mergeForPrice;   //create an object from class and give float to template class parameter
            time=clock();   //run clock
            mergeForPrice.mergeSort(priceColumn,0,priceColumn.size()-1,allValues); //call sort function for last_price vector
            time = clock()-time;    //stop clock
            cout<<"Elapsed time "<< ((float)time)/CLOCKS_PER_SEC <<" seconds"<<endl; //write time to console
            mergeForPrice.writeToFile(allValues,header);    //call function for writing into file
        }
        else
        {
            cout<<"Criteration is not valid. Use t or p instead";   //if criteration is not p or t, write an error message to console.
        }
    }
    else if (strcmp(argv[2], "i") == 0) //-algo is insertion
    {
        if(strcmp(argv[4],"t")==0)  //criteration is timestamp
        {
            Insertion <string> sortByTime;  //give string to template class and create an object from class
            time=clock();   //run clock
            sortByTime.InsertionSort(timeParam, allValues); //call sort function for timestamp vector
            time = clock()-time;    //stop clock
            cout<<"Elapsed Time :  "<< ((float)time)/CLOCKS_PER_SEC <<" seconds"<<endl; //write time to console
            sortByTime.writeToFile(allValues, header);  //call function for writing into file
        }
        else if(strcmp(argv[4],"p")==0) //criteration is last_price
        {
            Insertion <float> sortByPrice;  //give float to template class and create an object
            time=clock();   //run clock
            sortByPrice.InsertionSort(priceColumn, allValues);  //call sort function for last_price vector
            time = clock()-time;    //stop clock
            cout<<"Elapsed Time :  "<< ((float)time)/CLOCKS_PER_SEC <<" seconds"<<endl; //write time to console
            sortByPrice.writeToFile(allValues, header); //call function for writing into file
        }
        else
        {
            cout<<"Criteration is not valid. Use t or p instead";   //if criteration is not p or t, write an error message to console.
        }
    }
    else
    {
        cout<<"Algorithm type is not valid ! Use m or i" <<endl;    //-algo type is not valid write an error to console
    }
    return 0;   //end the program successfully
}

