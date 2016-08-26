//
//  RSA.cpp
//  RSA Term Project
//
//  Created by Dennis Bounded, David Brewer, Shane Hughes on 4/27/16.
//  Copyright © 2016 All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "RSA.h"

void encrypt(unsigned long exponent, unsigned long modulus, std::string plaintext)
{
    using namespace std;

    // Needed to convert string from the command line into appropiate type
    stringstream converter;
    unsigned long plain;
    unsigned long length = plaintext.length();
    unsigned long blockNumber = 0;
    
     //Break Message into 24 bits blocks and encrypts
    for(int i = 0; i < length - (length % 3) ; i += 3)
    {
        plain = (((plaintext[i] << 8) | plaintext[i+1]) << 8) | plaintext[i+2];   //concat bit strings
        cout << setfill('0') << setw(8) << hex << uppercase << mypowmod(plain, exponent, modulus) << " ";
        plain = 0;
        // Every 8th block print a newline
        blockNumber++;
        if (blockNumber % 8 == 0)
            cout << endl;
    }
    
    plain = 0;
    
    // case of 1 char left for a block
    if (length % 3 == 1)
    {
        plain = plaintext[length - 1];
        cout << setfill('0') << setw(8) << hex << uppercase << mypowmod(plain, exponent, modulus) << " ";
    }
    
    // case of 2 char left for a block
    else if (length % 3 == 2)
    {
        plain = ((plaintext[length - 2] << 8) | plaintext[length - 1]);
        cout << setfill('0') << setw(8) << hex << uppercase << mypowmod(plain, exponent, modulus) << " ";
    }
    
    cout << "\n";
    
}

void decrypt(unsigned long exponent, unsigned long modulus, std::string ciphertext)
{
    using namespace std;
    
    // Needed to convert hex string from the command line into approiate type
    stringstream converter;
    long bitMask1 = 16711680;       // 111111110000000000000000 in bin
    long bitMask2 = 65280;          // 000000001111111100000000 in bin
    long bitMask3 = 255;            // 000000000000000011111111 in bin
    long unsigned decValue, plain;
    
    // Remove blank spaces and newlines
    ciphertext.erase(remove(ciphertext.begin(),ciphertext.end(),' '),ciphertext.end());
    ciphertext.erase(remove(ciphertext.begin(),ciphertext.end(),'\n'),ciphertext.end());
    
    // Check if a block is of size 8
    if (ciphertext.length() % 8 != 0)
        throw "A block is not of length 8\n";
    
    // Convert hexstring into dec and then decrypt
    for(int i = 0 ; i < ciphertext.length() ; i+= 8)
    {
        converter.str(ciphertext.substr(i,8));
        converter >> hex >> decValue;
        plain = mypowmod(decValue, exponent, modulus);
        cout << (char)((plain & bitMask1) >> 16) // reads 1st 8 bits from left
        << (char)((plain & bitMask2) >> 8)  // reads 2nd 8 bits from left
        << (char)(plain & bitMask3);        // reads 3rd 8 bits from left
        converter.clear();
    }
    
    cout << "\n\n";
    
}

long mypowmod(long x, long y, long mod)
{
    
    unsigned long result;
    
    result = 1;
    
    if (y < 1)
        return result;
    
    if (y == 1)
        return x % mod;
    
    result = mypowmod(x, y / 2, mod) % mod;
    result = (result * result) % mod;
    
    if (y & 1)
        result = (result * x) % mod;
    
    return result;
    
}

long xgcd(long a, long b, long *x, long *y)
{
    long x1, y1, gcd;
    
    if(b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    gcd = xgcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}

bool isPrime(long number)
{
    if(number<2)
        return false;
    if(number==2)
        return true;
    if(number%2==0)
        return false;
    for(int i=3;i<=sqrt(number);i += 2)
    {
        if(number%i==0)
            return false;
    }
    return true;
}



