# Toy-RSA
A toy implementation of RSA cryptography system.
Created by Dennis Bounded, David Brewer, Shane Hughes
CS4840 Computer Security and Cryptography Spring 2016

# Build Instructions
run make in the source directory

# Usage
rsa -e "encrypts" [exponent in decimal] [modulus n in hexidecimal] [plain text in double quotes]
    -d "decrypt w/ private key" [ciphertext in double quotes]
    -s "sign/encrypt with private key" [plaintext in double quotes]
    -v "verify/decrypt with public key pair" [exponent in decimal] [modulus n in hexidecimal] [ciphertext in double quotes]
    -keys "print my public key pair"
