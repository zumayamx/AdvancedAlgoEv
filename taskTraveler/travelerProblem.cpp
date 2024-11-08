#include <iostream>
#include <vector>

using namespace std;

int backTracking(const vector<vector<int>>& graph, vector<bool>& visited, int pos, int n, int count, int cost, int& minCost) {


}

int travelAlgo(const vector<vector<int>>& graph) {
    int numCities = graph.size(); // Numero de ciudades
    vector<bool> visited(numCities, false); // Vector de ciudades visitadas
    visited[0] = true;  // Iniciar desde la primera ciudad
    int minCost = INT_MAX; // Inicializar el costo minimo
    backTracking(graph, visited, 0, numCities, 1, 0, minCost); // Funcion para hager backtracking
    return minCost;
}
