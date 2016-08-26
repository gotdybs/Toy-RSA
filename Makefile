# Dennis Bounded, David Brewer, Shane Hughes
# CS4840 Computer Security and Cryptography
# RSA Term Project

# Object file list
OBJS = RSA.o main.o

# Executable Name
EXENAME = rsa

# Macros
CC = g++
CCOPTS = -c 
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

# LINK OBJECT FILES
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS)
	rm -f *.o

# COMPILE OBJECT FILES
main.o : main.cpp
	$(CC) $(CCOPTS) main.cpp 

RSA.o : RSA.cpp RSA.h
	$(CC) $(CCOPTS) RSA.cpp
clean :
	rm -f *.o $(EXENAME)
