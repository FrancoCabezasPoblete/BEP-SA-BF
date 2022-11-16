entrega-2: entrega-2.o functions.o functions.h
	g++ -g entrega-2.o functions.o -o entrega-2

entrega-2.o: entrega-2.cpp
	g++ -c entrega-2.cpp

functions.o: functions.cpp functions.h
	g++ -c functions.cpp

clean:
	rm *.o entrega-2 