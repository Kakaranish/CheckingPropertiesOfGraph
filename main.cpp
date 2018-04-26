#include <iostream>
#include <cstdio>
#include <conio.h>

#include "Graph.h"


int main(int argc, char* argv[]){

	


	_getch();
	return 0;
}



//Testy
/*
	//Bigraph test
	Graph g(false); //undirected graph
	g.setFirstVertIsZero(false);
	if(!g.loadGraph("Testy/bigraph.txt"))
		std::cout << "Unable to load given file!" << std::endl;
	g.showEdges();
	if (g.isBigraph())
		std::cout << "Given graph is bigraph." << std::endl;
	else
		std::cout << "Given graph isn't bigraph." << std::endl;
	

	//Topological sort test
	Graph g(true); //directed graph
	if (!g.loadGraph("Testy/topological_sort.txt"))
	std::cout << "Unable to load given file!" << std::endl;
	g.showEdges();
	g.sortTopologically();


	//Bridges test
	Graph g(false);
	if (!g.loadGraph("Testy/bridges2.txt"))
	std::cout << "Unable to load given file!" << std::endl;
	g.showEdges();
	std::cout << "Bridges: \t";
	g.findBridges();


	//Articulation points test
	Graph g(false); //undirected graph
	if (!g.loadGraph("Testy/articulation.txt"))
		std::cout << "Unable to load given file!" << std::endl;
	g.showEdges();
	g.findArticulationPoints();
*/