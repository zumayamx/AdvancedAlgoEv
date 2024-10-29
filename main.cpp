// Integrity activity 1
// Design and analisys of advanced algorithms

// - José Manuel García Zumaya
// - Lisette Melo Reyes
// - Diego Valencia Moreno

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Fisrt part: verify if the content of any mcodeX.txt is in the each transmissionX.txt
// To solve this task we use the KMP algorithm, this returns "true" and the position of the first match
// if the content of the mcode is in the transmission, otherwise returns "false"

vector<int> is_content_in_transmissionKMP(string pattern, string text)
{
    // First we find the pi array

    // Define the len of pattern
    int len_pattern = pattern.size();

    // Define the max len of the prefix-suffix in pattern, beggin with 0
    int len_prefix_suffix = 0;

    // Define the vector of integers for the pi array
    vector<int> pi(pattern.size(), 0);

    int i = 1;
    while(i < len_pattern)
    {
        // If the character of actual position is equal to the character of the pattern in the position len_prefix_suffix
        if (pattern[i] == pattern[len_prefix_suffix])
        {
            // Increase the len_prefix_suffix since the character is equal and the len of prefix-suffix is increased
            len_prefix_suffix++;

            // Save the len_prefix_suffix in the pi array that corresponds to the position character i
            pi[i] = len_prefix_suffix;

            // Increase the i to continue with the next character
            i++;
        }
        else
        {
            // If the character of actual position is different to the character of the pattern in the position len_prefix_suffix
            if (len_prefix_suffix != 0)
            {
                // Set the len_prefix_suffix to the previous value of the pi array in the position len_prefix_suffix - 1
                // to verify if there are coincidences with a len of prefix-suffix minor
                len_prefix_suffix = pi[len_prefix_suffix - 1];
            }
            else
            {
                // If the len_prefix_suffix is 0, set the pi[i] to 0 and increase the i to continue with the next character
                pi[i] = 0;
                i++;
            }
        }
    }

    // Now we find the pattern in the text

    // Define the len of text
    int len_text = text.size();

    // Define the vector of integers to save the positions of the matches
    vector<int> positions;

    // Define the index of pattern
    int index_pattern = 0;

    // Define the index of text
    int index_text = 0;

    while ((len_text - index_text) >= (len_pattern - index_pattern))
    {
        if (pattern[index_pattern] == text[index_text])
        {
            index_pattern++;
            index_text++;
        }

        if (index_pattern == len_pattern)
        {
            // If the index_pattern is equal to the len_pattern, save the position of the match
            positions.push_back(index_text - index_pattern);

            // Set the index_pattern to the previous value of the pi array in the position index_pattern - 1
            // to verify if there are coincidences with a len of prefix-suffix minor
            index_pattern = pi[index_pattern - 1];
        }
        else if (index_text < len_text && pattern[index_pattern] != text[index_text])
        {
            if (index_pattern != 0)
            {
                // If the index_pattern is different to 0, set the index_pattern to the previous value of the pi array in the position index_pattern - 1
                // to verify if there are coincidences with a len of prefix-suffix minor
                index_pattern = pi[index_pattern - 1];
            }
            else
            {
                // If the index_pattern is 0, increase the index_text to continue with the next character
                index_text++;
            }
        }
    }

    return positions;
}


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

        cout << "File: " << name_files[i] << endl;

        // Get the each line of the file
        while (getline(file, text_files[i]))
        {
            // Print each line of the file
            cout << text_files[i] << endl;
        }

        cout << endl;
    }

    // Verify if the content of any mcodeX.txt is in the each transmissionX.txt
    for (int i = 2; i < number_files; i++)
    {
        cout << "Is the content of " << name_files[i] << " in the each transmissionX.txt?" << endl;

        for (int j = 0; j < 2; j++)
        {
            cout << "Transmission" << j + 1 << ".txt: ";

            vector<int> positions = is_content_in_transmissionKMP(text_files[i], text_files[j]);

            if (positions.size() > 0)
            {
                cout << "true, position: ";
                for (int k = 0; k < positions.size(); k++)
                {
                    cout << positions[k] << " ";
                }
            }
            else
            {
                cout << "false";
            }

            cout << endl;
        }

        cout << endl;
    }

    return 0;
}