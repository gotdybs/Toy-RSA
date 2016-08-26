//
//  Dennis Bounded, David Brewer, Shane Hughes
//  CS4840 Computer Security and Cryptography
//  RSA Term Project
//
//  main.cpp
//  Created by Dennis Bounded, David Brewer, Shane Hughes on 4/25/16.
//  Copyright © 2016 All rights reserved.
//  "Toy" demostration version of the Rivest/Shamir/Adlemant
//  public key cryptography system. Using "small" 15 bit primes.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include "RSA.h"
#define usageMsg \
"usage: rsa -e \"encrypts\" [exponent in decimal] [modulus n in hexidecimal] [plain text in double quotes]\n\
           -d \"decrypt w/ private key\" [ciphertext in double quotes]\n\
           -s \"sign/encrypt with private key\" [plaintext in double quotes]\n\
           -v \"verify/decrypt with public key pair\" [exponent in decimal] [modulus n in hexidecimal] [ciphertext in double quotes]\n\
           -keys \"print my public key pair\"\n"

// Step 1 – find two 15 bit primes
// Look at primes15bit.txt for prime numbers
const static unsigned long my_p = 26633;
const static unsigned long my_q = 32749;
const static unsigned long my_e = 65537;
const static unsigned long min15bit = 16384; // 100000000000000 in bin
const static unsigned long max15bit = 32767; // 111111111111111 in bin

// Step 2 – set n = p ∗ q
static unsigned long my_n = my_p * my_q;

// Step 3 – Note that ϕ(n)= (p − 1) ∗ (q − 1)
static unsigned long  phi = (my_p - 1) * (my_q - 1);

// Step 4 – We choose a (relatively small) encryption exponent e
// (making sure GCD(e, ϕ(n)) = 1)
// Step 5 – Calculate 1 = GCD(e, φ(n)) = f ∗ e + x ∗ φ(n)
// (using the extended GCD algorithm)
static long f, x = 0;
static long  gcd = xgcd(my_e, phi, &f, &x);

static unsigned long d = 0;

int main(int argc, const char * argv[]) {
    
    using namespace std;
    
    // Stuff I need to convert stuff from command line
    stringstream converter;
    string plaintext, ciphertext, option;
    unsigned long exponent;
    unsigned long modulus;
    
    // Step 6 – Set the decryption exponent d to be such that 1 < d < φ(n) and d ≡ f mod φ(n)
    if(f < 0)
        d = (f + phi) % phi;
    else
        d = f % phi;
    
    try {
        
        if (my_p > max15bit || my_p < min15bit || my_q > max15bit || my_q < min15bit)
            throw "p or q is bigger or smaller than a 15 bit integer\n";
        if (!(isPrime(my_p)) || !(isPrime(my_p)))
            throw "p or q is not prime\n";
        if (gcd != 1)
            throw "GCD(e, φ(n)) != 1\n";
        if (argc == 1)
            throw "";
        
        // first flag : -e, -d, -s, -v
        option = argv[1];
        
        // Encrypt
        if (option.compare("-e") == 0)
        {
            if (argc < 5)
                throw "";
            
            // get exponent value
            converter.str(argv[2]);
            converter >> dec >> exponent;
            converter.clear();
            
            // get modulus value
            converter.str(argv[3]);
            converter >> hex >> modulus;
            converter.clear();
            
            // get plaintext
            plaintext = argv[4];
            
            // print encrypted message
            encrypt(exponent, modulus, plaintext);
            
        }
        
        
        // Decrypt with private key
        else if (option.compare("-d") == 0 )
        {
            if (argc < 3)
                throw "";
            // Get Ciphertext
            ciphertext = argv[2];
            
            // Decrypt and Print Message
            decrypt(d, my_n, ciphertext);

        }
        
        // Sign (Encrypt with my private key)
        else if (option.compare("-s") == 0)
        {
            if (argc < 3)
                throw "";
            
            // Get Plaintext
            plaintext = argv[2];
            
            // Encrypt and Print Message
            encrypt(d, my_n, plaintext);
        }
        
        // Verify (Decrypt with public key pair)
        else if (option.compare("-v") == 0)
        {
            if (argc < 4)
                throw "";
            
            // Get Exponent
            converter.str(argv[2]);
            converter >> dec >> exponent;
            converter.clear();
            
            // Get Modulus
            converter.str(argv[3]);
            converter >> hex >> modulus;
            converter.clear();
            
            // Get Ciphertext
            ciphertext = argv[4];
            
            // Decrypt with public key pair and print message
            decrypt(exponent, modulus, ciphertext);
        }
        
        //Publishing my public keys
        else if (option.compare("-keys") == 0)
            cout << "My Public Keys:\ne = " << dec << my_e << "\nn = " << hex << uppercase << my_n << endl;
        
        // Default : display usage message
        else
            throw "";
    
        
    } catch(const char* errormsg) {
        cerr << errormsg; cerr << usageMsg;
    }
    
    return 0;
    
}
