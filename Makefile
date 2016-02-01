changeslow: changeslow.o
	g++ -o changeslow changeslow.o

changeslow.o: changeslow.cpp
	g++ -c changeslow.cpp

changegreedy: changegreedy.o
	g++ -o changegreedy changegreedy.o

changegreedy.o: changegreedy.cpp
	g++ -c changegreedy.cpp

changedp: changedp.o
	g++ -o changedp changedp.o

changedp.o: changedp.cpp
	g++ -c changedp.cpp