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

#include "Stack.h"
#include "Queue.h"
#include <list>


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
	~Graph();

	inline void setFirstVertIsZero(bool value) {
		firstVertIsZero = value;
	}
	bool loadGraph(std::string filename);
	void showAdjMatrix();

	bool isBigraph();
	void sortTopologically();
	void findBridges();
	void findArticulationPoints() {
		
		int n = numOfVertices; //liczba wierzcho³ków w grafie
		std::list<int> L; //lista wierzcho³ków, które s¹ punktami artykulacji
		int dv; //przechowuje numery wierzcho³ków dla DFS
		int nc; //liczba synów na drzewie rozponaj¹cym
		int* D; //dynamiczna tablica dla numerów wierzcho³ków nadawanych przez DFS

		D = new int[n];
		for (int i = 0; i < n; ++i)
			D[i] = 0;

		std::function<int(int,int)> DFSap = [&](int v, int vf)->int {
			int Low, temp;
			bool test;

			D[v] = dv;
			Low = dv;
			++dv;
			test = false;

			for (int u = 0; u < n; u++) {
				if (!adj_matrix[v][u])
					continue;
				if (u != vf) {
					if (D[u] == 0) {
						temp = DFSap(u, v);
						if (temp < Low)
							Low = temp;
						if (temp >= D[v])
							test = true;
					}
					else if (D[u] < Low)
						Low = D[u];
				}
			}
			if (test)
				L.push_back(v);

			return Low;
		};


		for (int i = 0; i < n; ++i) {
			if (D[i] > 0)
				continue;
			dv = 2; //pocz¹tek numeracji DFS dla synów
			nc = 0;
			D[i] = 1; //korzeñ ma zawsze DFS równy 1

			for (int u = 0; u < n; u++) {
				if (!adj_matrix[i][u]) //sprawdzamy czy wierzcho³ek jest s¹siadem
					continue;
				if (D[u] == 0) {
					++nc;
					DFSap(u, i);
				}
					
			}
			if (nc > 1)
				L.push_back(i);
		}

		std::cout << "Found articulation points: " << std::endl;
		for (auto& x : L)
			std::cout << x << std::endl;
	}
	
	
		

};

