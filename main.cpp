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

void is_content_in_transmissionKMP(string pattern, string text)
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
            positions.push_back(index_text - index_pattern + 1);

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

    if (positions.size() > 0)
    {
        cout << "true " << positions.front() << endl;
    }
    else
    {
        cout << "false" << endl;
    }
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

    int max_len_palindrome = 0;
    int beginning_position_palindrome = 0;
    for (int i = 0; i < text_special.size(); i++)
    {
        max_len_palindrome = max(max_len_palindrome, LPS[i]);
        beginning_position_palindrome = (max_len_palindrome == LPS[i]) ? i : beginning_position_palindrome;
    }

    cout << "Beginning poistion of the greater palindrome: " << beginning_position_palindrome - (max_len_palindrome / 2) << endl;
    cout << "Length of the greater palindrome: " << max_len_palindrome << endl;
    cout << "Finish position of the greater palindrome: " << beginning_position_palindrome + (max_len_palindrome / 2) << endl;
}

// Function to get a substring from a text
string mySubstr(string text, int start, int end)
{
    string result = "";
    for (int i = start; i < end; i++)
    {
        result += text[i];
    }
    return result;
}

// Third part: check what way similitude has the content of the transmission files
void similitude_content_transmissionSuffixArray(string text1, string text2)
{
    // cout << "Text1: " << text1 << endl;
    // cout << "Text2: " << text2 << endl;

    // Concatenate both texts with a special character to avoid similarities between the texts
    string concatenated_text = text1 + "$" + text2;
    int len_concatenated_text = concatenated_text.size();

    // cout << "Concatenated text: " << concatenated_text << endl;

    // Define the vector of strings for the suffix array of each text
    vector<pair<string, int>> suffix_array_text(concatenated_text.size());

    // Build the suffix array with positions
    for (int i = 0; i < concatenated_text.size(); i++)
    {
        suffix_array_text[i] = {mySubstr(concatenated_text, i, len_concatenated_text), i};
    }

    // Print the unsorted suffix array
    // cout << "Unsorted suffix array:" << endl;
    // for (auto e : suffix_array_text)
    // {
    //     cout << e.first << " at position " << e.second << endl;
    // }

    // Sort the suffix array lexicographically
    sort(suffix_array_text.begin(), suffix_array_text.end());

    // Print the sorted suffix array
    // cout << "Sorted suffix array:" << endl;
    // for (auto e : suffix_array_text)
    // {
    //     cout << e.first << " at position " << e.second << endl;
    // }

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

    // cout << "The similitude between the content of the transmission files is: " << max_similitude << endl;
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

        // Variable temporal para almacenar cada línea
        string line;
        // Inicializamos para que esté vacío antes de acumular
        text_files[i] = "";

        // Lee cada línea del archivo
        while (getline(file, line))
        {
            // Acumula cada línea en text_files[i], añadiendo un salto de línea entre ellas
            text_files[i] += line;
        }

        // Cierra el archivo
        file.close();
    }

    // Part 1: verify if the content of any mcodeX.txt is in the each transmissionX.txt
    cout << "PARTE 1: Verificar si el contendido de cualquier mcodeX.txt está en cada transmissionX.txt" << endl;
    for (int i = 2; i < number_files; i++)
    {
        cout << endl;
        cout << name_files[i] << endl;

        for (int j = 0; j < 2; j++)
        {
            cout << name_files[j] << ": ";

            is_content_in_transmissionKMP(text_files[i], text_files[j]);
        }

        cout << endl;
    }

    // Part two: check if the content of the transmission files have a "mirroring code", it's say the greater palindrome
    cout << "PARTE 2: Verificar si el contenido de los archivos de transmisión tiene un \"código espejo\", es decir, el palíndromo más grande" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << name_files[i];
        mirroring_codeManacher(text_files[i]);
        cout << endl;
    }

    // Part three: check what way similitude has the content of the transmission files
    cout << "PARTE 3: Verificar cual es la subcadena común más larga entre los archivos de transmisión" << endl;
    similitude_content_transmissionSuffixArray(text_files[0], text_files[1]);

    return 0;
}