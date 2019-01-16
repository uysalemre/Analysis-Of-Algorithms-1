//
//  Hash.cpp
//  AoA3
//
//  Created by Emre Uysal on 3.12.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <map>
#include "Hash.h"

using namespace std;

// constructor sets the parameters
Hash::Hash(vector<string> &voc, int size)
{
    vocabulary = voc;
    M = size;
    linearTable.resize(M);
    doubleTable.resize(M);
    collusionForUniversal = 0;
    collusionForLinear = 0;
    collusionForDouble = 0;
    sColD = 0;
    sColL = 0;
    sColU = 0;
}


// this function returns index for table
int Hash::linearProbing(int key)
{
    int index = key % M;                            //calculate the index
    while(linearTable[index] != "" && index < M)    //increase index for avoiding collusion until reaches m-1
    {
        collusionForLinear++;
        index++;
    }
    return index;
}

// insert function for linear probing method
void Hash::insertForLinearProbing()
{
    for (vector<string>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it)
    {
        // alternative for distance it - vec.begin()
        int currentIndex = distance(vocabulary.begin(), it);
        int index = linearProbing(currentIndex);    //send current index to calculate linear probing index
        linearTable[index] = vocabulary[currentIndex];
    }
}

// double hashing h1 function
int Hash::doubleHashingH1(int key)
{
    return key % M;
}

// double hashing h2 function
int Hash::doubleHashingH2(int key)
{
    // in this part find the biggest prime number before M
    int primeNum;
    for (int i = 2; i < M; i++)
    {
        if (findPrime(i))
        {
            primeNum = i;
        }
    }
    return primeNum-(key % primeNum);
}

// double hash function that manages h1 and h2 functions according to collusion
int Hash::doubleHashing(int key)
{
    int index = doubleHashingH1(key);                   // calculate h1
    if(doubleTable[index] != "")                        // collusion
    {
        int index2 = doubleHashingH2(key);              // calculate h2
        int i=1;
        while (true)
        {
            int newIndex = (index + i * index2) % M;    // find new index
            if(doubleTable[newIndex] == "")             // if new index is available
            {
                return newIndex;                        // return it
            }
            i++;
            collusionForDouble++;                       // or increase collusion
        }
    }
    return index;                                       // no collusion occurs for this index
}

// for finding prime number returns true if it is prime
bool Hash::findPrime(int number)
{
    if (number <= 1)
        return false;
    
    // find until m-1
    for (int i = 2; i < number; i++)
        if (number % i == 0)
            return false;
    return true;
}

// double hashing insert function
void Hash::insertForDouble()
{
    for (vector<string>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it)
    {
        // alternative for distance it - vec.begin()
        int currentIndex = distance(vocabulary.begin(), it);
        int index = doubleHashing(currentIndex);                //send current index to calculate linear probing index
        doubleTable[index] = vocabulary[currentIndex];          // insert into index
    }
}

// this function set the prime number for univsersal set and changes it's size
void Hash::setPrimeNumForUniversal()
{
    // find the prime number before given M
    int primeNum;
    for (int i = 2; i <= M; i++)
    {
        if (findPrime(i))
        {
            primeNum = i;
        }
    }
    universalSize = primeNum;
    universalTable.resize(universalSize);
}


// universal hash function
int Hash::universalHash(int key)
{
    // decompose key into 2 digits
    vector<int> k;
    int key_0,key_1,key_2;
    key_2 = (key / 1) % 100;
    key_1 = (key / 100) % 1000;
    key_0 = (key / 100000) % 10000;
    k.push_back(key_0);
    k.push_back(key_1);
    k.push_back(key_2);
    
    // pic randomly generated m
    vector<int> a;
    srand(time(NULL));
    for (int i = 0; i < 3; i++)
    {
        a.push_back(rand() % universalSize);
    }
    
    int index = 0;
    for (int i = 0 ; i < 3; i++)
    {
        index += (a[i]*k[i]);           // calculate index
    }
    return index % universalSize;
    
}

// insert function for universal hashing
void Hash::insertForUniversal()
{
    setPrimeNumForUniversal();      // first set the prime number
    for (vector<string>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it)
    {
        // alternative for distance it - vec.begin()
        int currentIndex = distance(vocabulary.begin(), it);
        int index = universalHash(currentIndex);    //send current index to calculate linear probing index
       
        // collusion occurs and use linear probing
        //increase index for avoiding collusion until reaches m-1
        while(universalTable[index] != "" && index < universalSize)
        {
            collusionForUniversal++;
            index++;
        }
        universalTable[index] = vocabulary[currentIndex];       // insert
    }
}


// set the search file
void Hash::setSearchFile(vector<string> &file)
{
    searchKeys = file;
}


// search function that uses linear probing
void Hash::searchForLinear()
{
    // for each element in the search.txt call linear probing function to find index
    for (vector<string>::iterator it = searchKeys.begin(); it != searchKeys.end(); ++it)
    {
        int currentIndex = distance(searchKeys.begin(), it);
        // make linear probing prosedure for searching
        int index = currentIndex % M;
        while (linearTable[index] != searchKeys[currentIndex] && index < M)
        {
            sColL++;
            index++;       // collusion Number
        }
        
    }
    

}

// searcg function that uses double hashing
void Hash::searchForDouble()
{
    for (vector<string>::iterator it = searchKeys.begin(); it != searchKeys.end(); ++it)
    {
        int currentIndex = distance(searchKeys.begin(), it);
        // make double hashing in here to find
        int index = doubleHashingH1(currentIndex);
        if(doubleTable[index] != searchKeys[currentIndex])
        {
            int index2 = doubleHashingH2(currentIndex);
            int i=1;
            while (true && i< M)
            {
                int newIndex = (index + i * index2) % M;
                if(doubleTable[newIndex] == searchKeys[currentIndex])
                {
                    return;     // finded
                }
                i++;            // collusion
                sColD++;
            }
            cout<<"Could not able to find :"<<searchKeys[currentIndex]<<endl;
        }
    }
}

// search function that uses universal hashing
void Hash::searchForUniversal()
{
    for (vector<string>::iterator it = searchKeys.begin(); it != searchKeys.end(); ++it)
    {
        int currentIndex = distance(searchKeys.begin(), it);
        int index = universalHash(currentIndex);
        while(universalTable[index] != searchKeys[currentIndex] && index < universalSize)
        {
            sColU++;
            index++;
        }
    }
}

// getter functions
int Hash::getCollusionForDouble()
{
    return collusionForDouble;
}

int Hash::getCollusionForLinear()
{
    return collusionForLinear;
}

int Hash::getCollusionForUniversal()
{
    return collusionForUniversal;
}


int Hash::getSearchCollusionForDouble()
{
    return sColD;
}

int Hash::getSearchCollusionForLinear()
{
    return sColL;
}

int Hash::getSearchCollusionForUniversal()
{
    return sColU;
}


int Hash::getSize()
{
    return M;
}
