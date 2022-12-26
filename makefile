all: client.out server.out

client.out:						#Client file
	g++ -std=c++11 KnnClient.cpp -o client.out

server.out: knnServer.o Algorithms.o MainDistance.o TypeVector.o		#Server files
	g++ -std=c++11 knnServer.o Algorithms.o MainDistance.o TypeVector.o -o server.out

knnServer.o: knnServer.cpp knnServer.h
	g++ -c knnServer.cpp

Algorithms.o: Algorithms.cpp Algorithms.h
	g++ -c Algorithms.cpp

MainDistance.o: MainDistance.cpp
	g++ -c MainDistance.cpp

TypeVector.o: TypeVector.cpp TypeVector.h
	g++ -c TypeVector.cpp

clean:
	rm *.o *.out
