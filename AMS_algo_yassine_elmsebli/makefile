all: main

main: main.o Arc.o Graphe.o Noeud.o
	g++ -o main main.o Arc.o Graphe.o Noeud.o -fno-stack-protector

main.o: main.cpp
	g++ -c main.cpp -fno-stack-protector

Graphe.o: Graphe.cpp Graphe.h Noeud.h Arc.h
	g++ -c Graphe.cpp  -fno-stack-protector
	
Arc.o: Arc.cpp Arc.h Noeud.h
	g++ -c Arc.cpp -fno-stack-protector

Noeud.o: Noeud.cpp Noeud.h Arc.h
	g++ -c Noeud.cpp -fno-stack-protector



clean:
	rm -f *.o main
