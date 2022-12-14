main: main.o functions.o functions.h
	g++ -Wall -g main.o functions.o -o main

main.o: main.cpp
	g++ -Wall -c main.cpp

functions.o: functions.cpp functions.h
	g++ -Wall -c functions.cpp

clean:
	rm *.o main solution.txt