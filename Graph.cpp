#include "Graph.h"
#include "Stack.cpp"
#include "Queue.cpp"

/*
	PRIVATE METHODS
*/

void Graph::clearAdjMatrix() {
	for (int i = 0; i < numOfVertices; i++)
		for (int j = 0; j < numOfVertices; j++)
			adj_matrix[i][j] = false;
}
void Graph::dealocateAdjMatrix() {
	for (int i = 0; i < numOfVertices; i++)
		delete[] adj_matrix[i];
	delete[] adj_matrix;

	numOfVertices = 0;
	adj_matrix = nullptr;
}

/*
	PUBLIC METHODS
*/

//CONSTRUCTORS AND DESTRUCTOR
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
Graph::~Graph() {
	if (!numOfVertices)
		return;
	
	for (int i = 0; i< numOfVertices; i++)
		delete[] adj_matrix[i];
	delete[] adj_matrix;
}

//UTILITY FUNCTIONS
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
void Graph::showEdges(){
	for (int i = 0; i < numOfVertices; i++) 
		for (int j = 0; j < numOfVertices; j++)
			if (adj_matrix[i][j])
				std::cout << "(" << i << "," << j << ")\t";
	std::cout << std::endl;
	
}

//HOMEWORK PART
bool Graph::isBigraph() {	
	
	enum Color{BLUE=-1, GRAY=0, RED=1};
	int* vertColor = new int[numOfVertices];
	Queue<int> queue;
	
	for (int i = 0; i < numOfVertices; i++)
		vertColor[i] = GRAY;

	//Oczywiscie wykorzystujemy algorytm przeszukiwania BFS
	for (int i = 0; i < numOfVertices; i++) {
		if (vertColor[i] != GRAY)
			continue;
		vertColor[i] = RED;
		queue.push(i);

		while (!queue.empty()) {
			int v = queue.front();
			queue.pop();

			for (int u = 0; u < numOfVertices; u++) {
				if (!adj_matrix[v][u]) //chcemy, aby wierzcho³ek u by³ s¹siadek wierzcho³ka v
					continue;
				if (vertColor[u] == vertColor[v]) //znaleziono pêtle w grafie
					return false;
				if (vertColor[u] != GRAY)
					continue;
				vertColor[u] = -vertColor[v];
				queue.push(u);
			}
		}
	}
	return true;
}
void Graph::sortTopologically() {
	if (!isDirected)
		throw std::exception("Unable to perform topological sort! Required directed graph!");

	Stack<int> stack;
	enum Color{WHITE=0, GRAY,GREEN};

	int* vertColor = new int[numOfVertices];
	for (int i = 0; i < numOfVertices; i++)
		vertColor[i] = WHITE;

	std::function<bool(int)> sortFunction = [&](int v)->bool {
		if (vertColor[v] == GRAY)
			return false;
		if (vertColor[v] == GREEN)
			return true;

		vertColor[v] = GRAY;

		for (int u = 0; u < numOfVertices; u++) {
			if (!adj_matrix[v][u])
				continue;
			
			if (!sortFunction(u))
				return false;
		}
		vertColor[v] = GREEN;
		stack.push(v);

		return true;
	};


	for (int i = 0; i < numOfVertices; i++) {
		if (vertColor[i] != WHITE)
			continue;
		else
			if (!sortFunction(i)) {
				std::cout << "Graf nie jest acykliczny! Sortowanie topologiczne nie powiodlo sie!" << std::endl;
				return;
			}
	}


	while (!stack.empty()) {
		std::cout << stack.top() << "\t";
		stack.pop();
	}
	std::cout << std::endl;
}
void Graph::findBridges() {
	if (isDirected)
		throw std::exception("Unable to find bridges! Required undirected graph!");

	int vertex_counter; //przechowuje numery wierzcholkow dla DFS, liczba calkowita
	int *DFS_arr = new int[numOfVertices]; //dynamiczna tablica dla numerów wierzcho³ków nadawanych przez DFS
	for (int i = 0; i<numOfVertices; i++)
		DFS_arr[i] = 0;


	std::function<int(int, int)> DFS_bridge = [&](int v, int v_father)->int {
		int low, temp;

		DFS_arr[v] = vertex_counter;
		low = vertex_counter;
		++vertex_counter;

		for (int u = 0; u < numOfVertices; u++) {
			if (!adj_matrix[v][u]) //wierzcho³ek u nie jest s¹siadem wierzcho³ka v
				continue;

			if (u != v_father) { //s¹siad nie mo¿e byæ ojcem v
				if (DFS_arr[u] == 0) { //jeœli s¹siad nie by³ wczeœniej odwiedzany, to w sposób rekurencyjny go odwiedzamy


					temp = DFS_bridge(u, v); //ojcem s¹siada u jest oczywiœcie v
					if (temp < low)
						low = temp;
				}
				else if (DFS_arr[u] < low)
					low = DFS_arr[u];
			}
		}
		if (low == DFS_arr[v] && v_father > -1  )
			std::cout << "(" << v << "," << v_father << ")\t";
		
		return low;
	};

	for (int i = 0; i < numOfVertices; i++) {
		if (DFS_arr[i] != 0)
			continue;
		vertex_counter = 1;
		DFS_bridge(i, -1); //na poczatku wierzcholek nie ma ojca, wiec wpisujemy -1
	}
}
void Graph::findArticulationPoints() {

	int n = numOfVertices; //liczba wierzcho³ków w grafie
	std::list<int> L; //lista wierzcho³ków, które s¹ punktami artykulacji
	int dv; //przechowuje numery wierzcho³ków dla DFS
	int nc; //liczba synów na drzewie rozponaj¹cym
	int* D; //dynamiczna tablica dla numerów wierzcho³ków nadawanych przez DFS

	D = new int[n];
	for (int i = 0; i < n; ++i)
		D[i] = 0;

	std::function<int(int, int)> DFSap = [&](int v, int vf)->int {
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