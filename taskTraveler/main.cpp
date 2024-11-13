/*
 * Traveler Problem with Backtracking
 * Analysis and design of advanced algorithms
 */

/*
 * José Manuel García Zumaya - A01784238
 * Lisette Melo Reyes - A01028066
 * Diego Valencia Moreno - A01784568
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

/*
 * Function to solve the Traveler Problem with Backtracking
 *
 * Args:
 * - cities_graph_matrix: matrix with the "distances" between cities (reference to work over the same matrix)
 * - current_city: current city
 * - visited: set with the visited cities (reference to work over the same set)
 * - cost: current cost accumulated
 * - min_cost: last minimum cost
 *
 * Returns:
 * - min_cost: the minimum cost to visit all cities and return to the starting city
 *
 * Complexity:
 * - O(n!), since for each city we have n-1 options to visit, so n * (n-1) * (n-2) * ... * 1 = n!
 */
int back_tracking(vector<vector<int>> &cities_graph_matrix,
                  int current_city,
                  unordered_set<int> &visited,
                  int cost,
                  int min_cost,
                  int initial_city)
{
    /*
     * Define the number of cities
     */
    int num_cities = cities_graph_matrix.size();

    /*
     * If we have visited all cities and we can return to the initial city,
     * only if there are a path between the current city and the initial city.
     * This is the stop condition for our recursion too
     */
    if (visited.size() == num_cities && cities_graph_matrix[current_city][initial_city] > 0)
    {
        /*
         * Select the minimum cost between the acumulated cost plus the cost to return to the initial city
         * and the last minimum cost found in another "branch" of the recursion
         */
        min_cost = min(min_cost, cost + cities_graph_matrix[current_city][initial_city]);

        /*
         * Return the minimum cost
         */
        return min_cost;
    }

    /*
     * For each city, we check if we have visited it and if there is a path between the current city and the next city,
     * and if we haven't visited all cities yet
     */
    for (int next_city = 0; next_city < num_cities; next_city++)
    {
        /*
         * If we haven't visited the next city and there is a path between the current city and the next city.
         */
        if (visited.find(next_city) == visited.end() && cities_graph_matrix[current_city][next_city] > 0)
        {
            /*
             * We add the next city to the visited set
             */
            visited.insert(next_city);

            /*
             * We call the function recursively, passing the same cities graph matrix and visited set,
             * with the next city as the current city to simulate the movement to the next city,
             * and we add the cost to move to the next city (acumulated cost), update the minimum cost
             * finally we save the initial city to return to it.
             */
            min_cost = back_tracking(cities_graph_matrix,
                                     next_city,
                                     visited,
                                     cost + cities_graph_matrix[current_city][next_city],
                                     min_cost,
                                     initial_city);

            /*
             * We remove the next city from the visited set to allow to recursion to visit all
             * possible options to move to another cities.
             *
             * That is, in each recursion call we pass the next city (that is the current city of it's recursion call),
             * then that city we need to process all possible paths, but without forgetting the cities
             * that we have already visited, that's why we pass the same visited set to the next recursion call
             * and that's why use the for loop to iterate over all posible paths checking if the path exists.
             *
             * So one time that we have reached the stop condition (visited all cities) and reutrn to the initial city,
             * we have found a minimum cost, then we return to the previous recursion call and remove the next city,
             * that in the last case is the last city visited, so if the current city have paths to other
             * cities yet (for loop), that allows to visit all cities and to have a correct history of visited cities.
             */
            visited.erase(next_city);
        }
    }

    /*
     * Return the minimum cost
     */
    return min_cost;
}

int main()
{
    vector<vector<int>> cities_graph = {
        {
            0,
            259,
            177,
            611,
            504,
            899,
            827,
            971,
            969,
            1007,
        },
        {
            259,
            0,
            277,
            546,
            492,
            906,
            912,
            1045,
            1049,
            1110,
        },
        {
            177,
            277,
            0,
            440,
            327,
            723,
            670,
            811,
            830,
            859,
        },
        {
            611,
            546,
            440,
            0,
            139,
            385,
            507,
            597,
            612,
            702,
        },
        {
            504,
            492,
            327,
            139,
            0,
            415,
            453,
            569,
            578,
            655,
        },
        {
            899,
            906,
            723,
            385,
            415,
            0,
            274,
            270,
            296,
            401,
        },
        {
            827,
            912,
            670,
            507,
            453,
            274,
            0,
            146,
            124,
            202,
        },
        {
            971,
            1045,
            811,
            597,
            569,
            270,
            146,
            0,
            28,
            131,
        },
        {
            969,
            1049,
            830,
            612,
            578,
            296,
            124,
            28,
            0,
            105,
        },
        {
            1007,
            1110,
            859,
            702,
            655,
            401,
            202,
            131,
            105,
            0,
        }};

    /*
     * Uncoment the next lines to test the function with a smaller matrix
     */
    // vector<vector<int>>
    //     cities_graph = {
    //         {0, 10, 15},
    //         {10, 0, 20},
    //         {15, 20, 0}};

    /*
     * Define the minimum cost as the maximum integer value that can be stored in a variable,
     * it's like a "infinite" value to compare with the real minimum cost,
     * and the initial city to start the travel.
     *
     * Also, we define a set to store the visited cities and we add the initial city to it.
     * We define out of the function to avoid to create the set in each recursion call.
     */
    int min_cost = INT_MAX;
    unordered_set<int> visited;
    visited.insert(0);

    /*
     * Cities and it's indexes:
     * 0 - Y
     * 1 - CH
     * 2 - CA
     * 3 - TG
     * 4 - V
     * 5 - O
     * 6 - X
     * 7 - P
     * 8 - T
     * 9 - PA
     */
    int initial_city = 0;

    /*
     * Call the function to solve the Traveler Problem with Backtracking
     */
    int cost = back_tracking(cities_graph, initial_city, visited, 0, min_cost, initial_city);

    cout << "El costo mínimo para visitar todas las ciudades es: " << cost << endl;

    return 0;
}
