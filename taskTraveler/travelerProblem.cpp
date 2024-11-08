#include <iostream>
#include <vector>

using namespace std;

int backTracking(const vector<vector<int>>& graph, vector<bool>& visited, int pos, int n, int count, int cost, int& minCost) {


}


vector<vector<int>> grafo() {
    // Grafo de ejemplo (matriz de adyacencia)
    const vector<vector<int>>& graph= {
       {0, 259, 177, 611, 504, 899, 827, 971, 969, 1007,},
        {259, 0, 277, 546, 492, 906, 912, 1045, 1049, 1110,},
        {177, 277, 0, 440, 327, 723, 670, 811, 830, 859,},
        {611, 546, 440, 0, 139, 385, 507, 597, 612, 702,},
        {504, 492, 327, 139, 0, 415, 453, 569, 578, 655,},
        {899, 906, 723, 385, 415, 0, 274, 270, 296, 401,},
        {827, 912, 670, 507, 453, 274, 0, 146, 124, 202,},
        {971, 1045, 811, 597, 569, 270, 146, 0, 28, 131,},
        {969, 1049, 830, 612, 578, 296, 124, 28, 0, 105,},
        {1007, 1110, 859, 702, 655, 401, 202, 131, 105, 0,}

    };
   
    return graph;
}

int main() {
    vector<vector<int>> graph = grafo();
    int numCities = graph.size(); // Numero de ciudades
    vector<bool> visited(numCities, false); // Vector de ciudades visitadas
    visited[0] = true;  // Iniciar desde la primera ciudad
    int minCost = INT_MAX; // Inicializar el costo minimo
    backTracking(graph, visited, 0, numCities, 1, 0, minCost); // Funcion para hager backtracking
    return minCost;
}
