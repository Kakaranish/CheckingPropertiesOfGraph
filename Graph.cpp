#include "Graph.h"

void Graph::dealocateAdjMatrix() {
	for (int i = 0; i < numOfVertices; i++)
		delete[] adj_matrix[i];
	delete[] adj_matrix;

	numOfVertices = 0;
	adj_matrix = nullptr;
}

void Graph::clearAdjMatrix() {
	for (int i = 0; i < numOfVertices; i++)
		for (int j = 0; j < numOfVertices; j++)
			adj_matrix[i][j] = false;
}

Graph::Graph(bool _isDirected = true) : isDirected(_isDirected) {}


Graph::Graph(std::string filename, bool _isDirected = true) : isDirected(_isDirected) {

}

Graph::Graph(std::size_t _numOfVertices, bool _isDirected = true) : isDirected(_isDirected) ,
numOfVertices(_numOfVertices) {
	adj_matrix = new bool*[numOfVertices];
	for (int i = 0; i < numOfVertices; i++)
		adj_matrix[i] = new bool[numOfVertices];

	clearAdjMatrix();
}

bool Graph::loadGraph(std::string filename) {
	std::ifstream file;
	file.open(filename, std::ios::in);

	//Sprawdzamy, czy zadany plik istnieje
	if (!file.good())
		return false;

	std::string currLine;
	{
		std::size_t newNumOfVertices;

		//Probujemy wczytac pierwsza linijke zawierajaca informacje o ilosci wierzcholkow w grafie
		std::getline(file, currLine);
		try {
			newNumOfVertices = std::stoi(currLine);
		}
		catch (std::invalid_argument& e) {
			return false;
			std::cout << e.what() << std::endl;
		}
		numOfVertices = newNumOfVertices;

		//Jezeli aktualnie istnieje juz jakas tablica sasiedztwa i ma inny rozmiar niz wymagany, wowczas ja dealokujemy
		if (numOfVertices && !adj_matrix && numOfVertices != newNumOfVertices) 
			dealocateAdjMatrix();
		else {
			
			adj_matrix = new bool*[numOfVertices];
			for (int i = 0; i < numOfVertices; i++)
				adj_matrix[i] = new bool[numOfVertices];	

			clearAdjMatrix();
		}
	}


	std::regex pairRegex("\\([0-9]+,[0-9]+\\)");
	std::vector<int> edge;

	//Dodawanie kolejnych krawedzi do tablicy sasiedztwa
	while (!file.eof()) {
		std::getline(file, currLine);

		if (std::regex_match(currLine, pairRegex)) {
			edge = extractIntegers(currLine);

			if (edge[0] < 0 || edge[0] >= numOfVertices + !firstVertIsZero || edge[1] < 0 || edge[1] >= numOfVertices + !firstVertIsZero)
				throw std::out_of_range("Out of range in adjacency matrix");
			else {
				adj_matrix[firstVertIsZero ? edge[0] : edge[0] - 1][firstVertIsZero ? edge[1] : edge[1] - 1] = true;
				
				//Je¿eli graf jest nieskierowany
				if(!isDirected)
					adj_matrix[firstVertIsZero ? edge[1] : edge[1] - 1][firstVertIsZero ? edge[0] : edge[0] - 1] = true;
			}
				
		}
	}

	return true;
}

void Graph::showAdjMatrix() {
	for (int i = 0; i < numOfVertices; i++) {
		for (int j = 0; j < numOfVertices; j++)
			std::cout << adj_matrix[i][j] << "\t";
		std::cout << std::endl;
	}
}


bool Graph::isBigraph() {
	int n = numOfVertices;
	int* C = new int[n];
	
	for (int i = 0; i < n; i++)
		C[i] = 0;

	std::queue<int> Q;

	//Oczywiscie wykorzystujemy algorytm przeszukiwania BFS

	for (int i = 0; i < n; i++) {
		if (C[i] != 0)
			continue;
		C[i] = 1;
		Q.push(i);

		while (!Q.empty()) {
			int v = Q.front();
			Q.pop();

			for (int u = 0; u < n; u++) {
				if (!adj_matrix[v][u])
					continue;
				if (C[u] == C[v]) //znaleziono pêtle w grafie
					return false;
				if (C[u] != 0)
					continue;
				C[u] = -C[v];
				Q.push(u);
			}

		}

	}
	return true;
}


void Graph::sortTopologically() {
	
	int n = numOfVertices;
	std::stack<int> S;

	enum Color{WHITE=0, GRAY,GREEN};


	int* colorArr = new int[n];
	for (int i = 0; i < n; i++)
		colorArr[i] = WHITE;

	std::function<bool(int)> sortFunction = [&](int vertice)->bool {
		if (colorArr[vertice] == GRAY)
			return false;
		if (colorArr[vertice] == GREEN)
			return true;

		colorArr[vertice] = GRAY;

		for (int i = 0; i < n; i++) {
			if (!adj_matrix[vertice][i])
				continue;
			
			if (!sortFunction(i))
				return false;
		}

		colorArr[vertice] = GREEN;
		S.push(vertice);


		return true;
	};


	for (int i = 0; i < n; i++) {
		if (colorArr[i] != WHITE)
			continue;
		else
			if (!sortFunction(i)) {
				std::cout << "Graf nie jest acykliczny! Sortowanie topologiczne nie powiodlo sie!" << std::endl;
				return;
			}
	}

	
	while (!S.empty()) {
		std::cout << S.top() << "\t";
		S.pop();
	}
	std::cout << std::endl;
			



}