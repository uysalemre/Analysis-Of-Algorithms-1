//
//  main.cpp
//  AoA3
//
//  Created by Emre Uysal on 3.12.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Hash.h"

using namespace std;

int main(int argc, const char * argv[])
{
    // read file into a vector
    vector<string> vocab;
    string line;
    ifstream file;
    file.open(argv[1]);
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line);
            vocab.push_back(line);
        }
    }
    else
    {
        cout<<"Can not open "<<argv[1]<<endl;
    }
    file.close();
    //end of file reading operation
    
    //create hash set for given number
    Hash createHash(vocab,17863);
    createHash.insertForLinearProbing();
    createHash.insertForDouble();
    createHash.insertForUniversal();
    
    // write the collusion numbers to screen
    cout<<"For M =  :"<<createHash.getSize() <<endl;
    cout<<"Linear Probing Collusion Number : "<<createHash.getCollusionForLinear()<<endl;
    cout<<"Double Hashing Collusion Number : "<<createHash.getCollusionForDouble()<<endl;
    cout<<"Universal Hashing Collusion Number : "<<createHash.getCollusionForUniversal()<<endl<<endl;
    
    // create hash set for given 2nd number
    Hash newHash(vocab,21929);
    newHash.insertForLinearProbing();
    newHash.insertForDouble();
    newHash.insertForUniversal();
    
    // write the collusion numbers to screen
    cout<<"For M =  :"<<newHash.getSize() <<endl;
    cout<<"Linear Probing Collusion Number : "<<newHash.getCollusionForLinear()<<endl;
    cout<<"Double Hashing Collusion Number : "<<newHash.getCollusionForDouble()<<endl;
    cout<<"Universal Hashing Collusion Number : "<<newHash.getCollusionForUniversal()<<endl<<endl;

   // read the search.txt into a vector
    vector<string> search;
    string sline;
    ifstream sfile;
    sfile.open(argv[2]);
    if(sfile.is_open())
    {
        while(!sfile.eof())
        {
            getline(sfile, sline);
            search.push_back(sline);
        }
    }
    else
    {
        cout<<"Can not open "<<argv[2]<<endl;
    }
    sfile.close();
    // end of file reading
    
    //first hash set search operation for first size
    createHash.setSearchFile(search);
    createHash.searchForLinear();
    createHash.searchForDouble();
    createHash.searchForUniversal();
    
    // print results to screen
    cout<<"For M = :"<<createHash.getSize() <<endl;
    cout<<"Linear Probing Search Collusion Number : "<<createHash.getSearchCollusionForLinear()<<endl;
    cout<<"Double Hashing Search Collusion Number : "<<createHash.getSearchCollusionForDouble()<<endl;
    cout<<"Universal Hashing Search Collusion Number : "<<createHash.getSearchCollusionForUniversal()<<endl<<endl;
    
    // second hash set search operation for second size
    newHash.setSearchFile(search);
    newHash.searchForLinear();
    newHash.searchForDouble();
    newHash.searchForUniversal();
    
    // print results to screen
    cout<<"For M = :"<<newHash.getSize() <<endl;
    cout<<"Linear Probing Search Collusion Number : "<<newHash.getSearchCollusionForLinear()<<endl;
    cout<<"Double Hashing Search Collusion Number : "<<newHash.getSearchCollusionForDouble()<<endl;
    cout<<"Universal Hashing Search Collusion Number : "<<newHash.getSearchCollusionForUniversal()<<endl<<endl;
    
    return 0;
}
