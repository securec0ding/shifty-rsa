all: rsa

rsa: rsa.cpp
	g++ -g -o rsa rsa.cpp

clean:
	rm rsa