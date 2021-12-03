

CXX = g++
CXXFLAGS = -Wall -DNDEBUG -g3 -O2 -Wall -Wextra 

LIBS =   -lpthread -lgmpxx -lgmp -lsodium -lcurl


all: peer servidor  

peer: peer.c utils.c random_l.c
	$(CXX) $(CXXFLAGS) -o peer peer.c utils.c random_l.c ctaes.cpp AES.cpp sha256.cpp public-ip.cpp $(LIBS)

servidor: servidor.c utils.c
	$(CXX) $(CXXFLAGS) -o servidor servidor.c utils.c public-ip.cpp $(LIBS)





clean:
	$(RM) server peer  U
