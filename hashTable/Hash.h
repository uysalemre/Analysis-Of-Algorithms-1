//
//  Hash.h
//  AoA3
//
//  Created by Emre Uysal on 3.12.2018.
//  Copyright © 2018 Emre Uysal. All rights reserved.
//

#ifndef Hash_h
#define Hash_h

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Hash
{
    public:
        Hash(vector<string> &, int size);           //  constructor that sets the size and vocabulary file
        int linearProbing(int);                     //  calculate linear probing hash function
        void insertForLinearProbing();              //  insert into linear probing set
        int doubleHashingH1(int);                   //  h1 function for double hashing
        int doubleHashingH2(int);                   //  h2 function for double hashing
        int doubleHashing(int);                     //  h function for double hashing
        void insertForDouble();                     //  insert function for double hashing
        bool findPrime(int);                        //  find the biggest prime number according to M
        void setPrimeNumForUniversal();             //  universal hash set prime number according to M
        int universalHash(int key);                 //  universal hash function
        void insertForUniversal();                  //  insert function for universal hashing
        void setSearchFile(vector<string> &);       //  sets the search.txt
        void searchForLinear();                     //  linear probing search
        void searchForDouble();                     //  double hash search
        void searchForUniversal();                  //  universal hash search
        int getCollusionForLinear();                //  return collusion number for Linear Probing
        int getCollusionForDouble();                //  return collusion number for double hash
        int getCollusionForUniversal();             //  return collusion number for universal hash
        int getSearchCollusionForLinear();          //  return search collusion number for linear probing
        int getSearchCollusionForDouble();          //  return search collusion number for double hashing
        int getSearchCollusionForUniversal();       //  return search collusion number for universal hashing
        int getSize();                              //  return size of the hash set
    
    private:
        int M;                              // size of the hash sets
        int universalSize;                  // universal set size when calculating prime
        vector<string> linearTable;         // linear probing set
        vector<string> doubleTable;         // double hash set
        vector<string> universalTable;      // universal hash set
        vector<string> vocabulary;          // vocab file vector
        vector<string> searchKeys;          // search file vector
        int collusionForLinear;             // collusion number for linear probing
        int collusionForDouble;             // collusion number for double hashing
        int collusionForUniversal;          // collusion number for universal hashing
        int sColL;                          // search collusion number for linear probing
        int sColD;                          // search collusion number for double hashing
        int sColU;                          // search collusion number for universal hashing

};

#endif /* Hash_h */
