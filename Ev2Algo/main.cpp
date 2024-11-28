#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void read_file_matrix(vector<vector<int>> &matrix, string file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        vector<int> row;
        stringstream ss(line);
        int value;

        while (ss >> value)
        {
            row.push_back(value);
        }

        matrix.push_back(row);
    }

    file.close();
}

int main()
{
    vector<vector<int>> matrix;
    string file_name = "matrix.txt";

    read_file_matrix(matrix, file_name);

    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}