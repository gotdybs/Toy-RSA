//
//  RSA.h
//  RSA Term Project
//
//  Created by Dennis Bounded, David Brewer, Shane Hughes 4/27/16.
//  Copyright © 2016 All rights reserved.
//

#ifndef RSA_h
#define RSA_h

void encrypt(unsigned long exponent, unsigned long modulus, std::string plaintext);

void decrypt(unsigned long exponent, unsigned long modulus, std::string ciphertext);

long mypowmod(long x, long y, long mod);

long xgcd(long a, long b, long *x, long *y);

bool isPrime(long number);

#endif /* RSA_h */
