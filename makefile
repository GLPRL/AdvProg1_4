server.out: knnServer.o Algorithms.o MainDistance.o TypeVector.o fileData.o
	g++ knnServer.o Algorithms.o MainDistance.o TypeVector.o fileData.o -o server.out

knnServer.o: knnServer.cpp knnServer.h
	g++ -c knnServer.cpp

Algorithms.o: Algorithms.cpp Algorithms.h
	g++ -c Algorithms.cpp

MainDistance.o: MainDistance.cpp
	g++ -c MainDistance.cpp

TypeVector.o: TypeVector.cpp TypeVector.h
	g++ -c TypeVector.cpp

fileData.o: fileData.cpp fileData.h
	g++ -c fileData.cpp

clean:
	rm *.o server.out