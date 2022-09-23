#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w []= {0,0,0,0,0};
        int pos = k.size();
        for( int i = 4; i>=0; i--)
        {
            if(pos>=6)
            {
                std::string mystr = k.substr(pos-6, 6);
                w[i]+= letterDigitToNumber(mystr[0]);
                for(int j =1; j<6; j++)
                {
                    w[i]*= 36;
                    w[i]+= letterDigitToNumber(mystr[j]);
                }
                pos-=6;
            }
            else if (pos>0)
            {
                std::string mystr = k.substr(0,pos);
                w[i]+= letterDigitToNumber(mystr[0]);
                for(int j =1; j<pos; j++)
                {
                    w[i]*= 36;
                    w[i]+= letterDigitToNumber(mystr[j]);
                }
                pos=0;

            }
            else{
                w[i]=0;
            }
        }
        unsigned long long rv =0;
        for(int k=0; k<5; k++)
        {
            rv+=rValues[k]*w[k];
        }
        return rv;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T num;
        if(std::isdigit(letter))
            num = letter-22;
        else
            num = std::tolower(letter)-97;
        return num;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
