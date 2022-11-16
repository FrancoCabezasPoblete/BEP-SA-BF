Ent2: Ent2.o functions.o functions.h
	g++ -g Ent2.o functions.o -o Ent2

Ent2.o: Ent2.cpp
	g++ -c Ent2.cpp

functions.o: functions.cpp functions.h
	g++ -c functions.cpp

clean:
	rm *.o Ent2 