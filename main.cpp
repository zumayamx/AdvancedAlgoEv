#include <iostream>
#include <fstream>
#include <vector>

using namespace std;




int main () {

    // Define the vector of strings for the name of the files
    vector<string> name_files = {"transmission1.txt", "transmission2.txt", "mcode1.txt", "mcode2.txt", "mcode3.txt"};
    int number_files = name_files.size();

    // Define the vector of strings for text of the files, initialize with the same size of the name_files
    vector<string> text_files(number_files);

    for (int i = 0; i < number_files; i++)
    {
        // Open the file to read
        ifstream file(name_files[i]);

        // Get the each line of the file
        while (getline(file, text_files[i]))
        {
            // Print each line of the file
            cout << text_files[i] << endl;
        }
    }

    return 0;
}