#pragma once
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <fstream>
#include <exception>
#include <stdexcept>	
#include <string>
#include <regex>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include "Utility.h"


class Graph {
private:
	bool isDirected = true;
	bool firstVertIsZero = true;

	std::size_t numOfVertices = 0;
	bool** adj_matrix = nullptr;

	void clearAdjMatrix();
	void dealocateAdjMatrix();
public:
	Graph() = default;
	Graph(bool _isDirected);
	Graph(std::size_t _numOfVertices, bool _isDirected);
	Graph(std::string filename, bool _isDirected);


	inline void setFirstVertIsZero(bool value) {
		firstVertIsZero = value;
	}
	bool loadGraph(std::string filename);
	void showAdjMatrix();

	bool isBigraph();
	void sortTopologically();


};
