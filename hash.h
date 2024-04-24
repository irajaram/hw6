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
        HASH_INDEX_T w[5] = {0};
        int len = k.length();
        //step 1: find the number of substrings size 6
        double subString = std::ceil((len/6.0)); //get number of substrings as a floating point so then you can round up if there is a substring not of size 6
        int numString = static_cast<int>(subString);

        int multiply = 1; //to multiply 36 without use of pow
        int letterDig = 0; //converting letter or digit to number 1-35
        int product = 0;
        
        int startInd = 0; //starting index of each substring
        int wInd = 4; //index of W

        HASH_INDEX_T h = 0;
        //outer loop is to iterate through all substrings
        for(int i= 0; i<numString; i++){
             startInd = (len-1)-(6*i);
            if(startInd<0){
              break;
            }
            //inner loop to iterate through each letter in each substring
            for (int j=startInd; j>=startInd - 5; j--){
                if(j<0){
                  break;
                }
                letterDig = letterDigitToNumber(k[j]);
                product = letterDig * multiply;
                multiply*=36;
                w[wInd]+= product;
            }  

            multiply = 1;
            //std::cout << "w[" << wInd << "] = " << w[wInd] << std::endl;
            wInd--;
        }
        /*while(index < len){
            HASH_INDEX_T curr = 0;
            int count = std::min(6,len-index); //len-index gives starting index
            for (int i =0; i<6; i++){
                char c = tolower(k[index+i]);
                if(isalpha(c)){
                    curr = curr * 36 + (c - 'a');
                }
                else if (isdigit(c)){
                    curr = curr * 36 + (c - '0' + 26);  // because starting from 0 it is 27, so add 26 to convert number
                }
            }

            w[index/6] = curr;
            index+=6;
        }*/
       
        for(int i=0; i<5; i++){
            h +=(rValues[i]*w[i]);
        }

        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        letter = tolower(letter);
        // Add code here or delete this helper function if you do not want it
        if(isalpha(letter)){
            return letter - 'a';
        }
        else if(isdigit(letter)){
            return letter - '0' + 26; // because starting from 0 it is 27, so add 26 to convert number
        }
        return 0;

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
