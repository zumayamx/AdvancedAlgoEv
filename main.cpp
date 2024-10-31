// Integrity activity 1
// Design and analisys of advanced algorithms

// - José Manuel García Zumaya
// - Lisette Melo Reyes
// - Diego Valencia Moreno

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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
    while (i < len_pattern)
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

    cout << "len positions: " << positions.size() << endl;
    return positions;
}

// Second part: Check if the content of the transmission files have a "mirroring code", it's say the greater palindrome
void mirroring_codeManacher(string text)
{
    // Concatenate the text with special character
    string text_special = "";
    for (char e : text)
    {
        text_special += "$";
        text_special += e;
    }
    text_special += "$";

    // cout << "Text: " << text << endl;
    // cout << "Text special: " << text_special << endl;

    // Iterate over the text to find the greater palindrome
    int len_text_special = text_special.size();
    vector<int> LPS(len_text_special, 0);

    int current_element = 0;
    int rigth = -1;
    int left = 1;

    while (current_element < len_text_special)
    {
        if (rigth >= 0 && left < len_text_special && text_special[rigth] == text_special[left])
        {
            LPS[current_element]++;
            rigth++;
            left--;
        }
        else
        {
            current_element++;
            rigth = current_element + 1;
            left = current_element - 1;
        }
    }

    cout << "LPS: " << endl;
    for (int i = 0; i < text_special.size(); i++)
    {
        cout << text_special[i] << " ";
    }

    cout << endl;

    int max_len_palindrome = 0;
    for (int i = 0; i < text_special.size(); i++)
    {
        max_len_palindrome = max(max_len_palindrome, LPS[i]);
        cout << LPS[i] << " ";
    }

    for (int i = 0; i < text_special.size(); i++)
    {
        if (LPS[i] == max_len_palindrome)
        {
            cout << endl;
            cout << "The greater palindrome is: ";
            for (int j = i - max_len_palindrome; j <= i + max_len_palindrome; j++)
            {
                if (text_special[j] != '$')
                {
                    cout << text_special[j];
                }
            }
            cout << endl;
            break;
        }
    }
}

// Third part: check what way similitude has the content of the transmission files
void similitude_content_transmissionSuffixArray(string text1, string text2)
{
    cout << "Text1: " << text1 << endl;
    cout << "Text2: " << text2 << endl;

    // Concatenate both texts with a special character to avoid similarities between the texts
    string concatenated_text = text1 + "$" + text2;

    cout << "Concatenated text: " << concatenated_text << endl;

    // Define the vector of strings for the suffix array of each text
    vector<pair<string, int>> suffix_array_text(concatenated_text.size());

    // Build the suffix array with positions
    for (int i = 0; i < concatenated_text.size(); i++)
    {
        suffix_array_text[i] = {concatenated_text.substr(i), i};
    }

    // Print the unsorted suffix array
    cout << "Unsorted suffix array:" << endl;
    for (auto e : suffix_array_text)
    {
        cout << e.first << " at position " << e.second << endl;
    }

    // Sort the suffix array lexicographically
    sort(suffix_array_text.begin(), suffix_array_text.end());

    // Print the sorted suffix array
    cout << "Sorted suffix array:" << endl;
    for (auto e : suffix_array_text)
    {
        cout << e.first << " at position " << e.second << endl;
    }

    int max_similitude = 0;
    string longest_common_substring;
    int split_index = text1.size(); // Position of the separator ($)

    // Traverse the sorted suffix array to find the longest common substring
    for (int i = 1; i < suffix_array_text.size(); i++)
    {
        int pos1 = suffix_array_text[i - 1].second;
        int pos2 = suffix_array_text[i].second;

        // Check that the suffixes are from different parts (one from text1, the other from text2)
        if ((pos1 < split_index && pos2 > split_index) || (pos1 > split_index && pos2 < split_index))
        {
            // Calculate LCP between suffix_array_text[i - 1] and suffix_array_text[i]
            int lcp_length = 0;
            while (lcp_length < suffix_array_text[i - 1].first.size() &&
                   lcp_length < suffix_array_text[i].first.size() &&
                   suffix_array_text[i - 1].first[lcp_length] == suffix_array_text[i].first[lcp_length])
            {
                lcp_length++;
            }

            // Update maximum LCP and store the longest common substring
            if (lcp_length > max_similitude)
            {
                max_similitude = lcp_length;
                longest_common_substring = suffix_array_text[i].first.substr(0, lcp_length);
            }
        }
    }

    cout << "The similitude between the content of the transmission files is: " << max_similitude << endl;
    cout << "Longest common substring: " << longest_common_substring << endl;
}

int main()
{

    // Define the vector of strings for the name of the files
    vector<string> name_files = {"transmission1.txt", "transmission2.txt", "mcode1.txt", "mcode2.txt", "mcode3.txt"};
    int number_files = name_files.size();

    // Define the vector of strings for text of the files, initialize with the same size of the name_files
    vector<string> text_files(number_files);

    for (int i = 0; i < number_files; i++)
    {
        // Abre el archivo para leer
        ifstream file(name_files[i]);

        // cout << "File: " << name_files[i] << endl;

        // Variable temporal para almacenar cada línea
        string line;
        text_files[i] = ""; // Inicializamos para que esté vacío antes de acumular

        // Lee cada línea del archivo
        while (getline(file, line))
        {
            // Acumula cada línea en text_files[i], añadiendo un salto de línea entre ellas
            text_files[i] += line;

            // Imprime cada línea del archivo
            // cout << line << endl;
        }

        file.close(); // Cierra el archivo
    }

    cout << "Text files: " << endl;

    for (int i = 0; i < number_files; i++)
    {
        cout << "Text: " << endl;
        cout << text_files[i] << endl;
    }

    // Verify if the content of any mcodeX.txt is in the each transmissionX.txt
    for (int i = 2; i < number_files; i++)
    {
        cout << "Is the content of " << name_files[i] << " in the each transmissionX.txt?" << endl;

        for (int j = 0; j < 2; j++)
        {
            cout << "transmission" << j + 1 << ".txt: ";

            vector<int> positions = is_content_in_transmissionKMP(text_files[i], text_files[j]);

            if (positions.size() > 0)
            {
                // Here remember only print the first match
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

    // Part two: check if the content of the transmission files have a "mirroring code", it's say the greater palindrome
    for (int i = 0; i < 2; i++)
    {
        cout << "Transmission" << i + 1 << ".txt" << endl;
        mirroring_codeManacher(text_files[i]);
        cout << endl;
    }

    // Part three: check what way similitude has the content of the transmission files
    similitude_content_transmissionSuffixArray(text_files[0], text_files[1]);

    return 0;
}