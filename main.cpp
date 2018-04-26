#include <iostream>
#include <cstdio>
#include <conio.h>

#include "Stack.h"
#include "Stack.cpp"
#include "Queue.h"
#include "Queue.cpp"

#include "Graph.h"


int main(int argc, char* argv[]){

	Graph g(false); //undirected graph
	if (!g.loadGraph("Testy/articulation.txt"))
		std::cout << "Unable to load given file!" << std::endl;
	//g.showAdjMatrix();
	
	g.findArticulationPoints();
	


	_getch();
	return 0;
}