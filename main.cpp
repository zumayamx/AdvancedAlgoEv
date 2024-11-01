// Integrative Activity 1
// Analysis and design of advanced algorithms

// Equipo 2:
// - José Manuel García Zumaya
// - Lisette Melo Reyes
// - Diego Valencia Moreno

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// First part: verify if the content of any mcodeX.txt is in the each transmissionX.txt,
// to solve this task we use the KMP algorithm, this returns "true" and the position of the first match
// if the content of the mcode is in the transmission, otherwise returns "false"

// Function
// Args:
// - pattern: string, the content of the mcodeX.txt
// - text: string, the content of the transmissionX.txt

// Return:
// - None, only print the result
void is_content_in_transmissionKMP(string pattern, string text)
{
    // First we find the pi array

    // Define the len of pattern
    int len_pattern = pattern.size();

    // Define the vector of integers for the pi array, to store the max len of the prefix-suffix in pattern
    vector<int> pi(pattern.size(), 0);

    // Define the max len of the prefix-suffix in pattern, beggin with 0
    int len_prefix_suffix = 0;

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

        // If the character of actual position is different to the character of the pattern in the position len_prefix_suffix
        else
        {
            // If the len_prefix_suffix is different to 0
            if (len_prefix_suffix != 0)
            {
                // Set the len_prefix_suffix to the previous value of the pi array in the position len_prefix_suffix - 1
                // to avoid starting the comparison from the beginning of the pattern, instead resume from a prefix-suffix that has already been matched
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

    // Define the index of pattern to iterate over the pattern
    int index_pattern = 0;

    // Define the index of text to iterate over the text
    int index_text = 0;

    // Iterate over the text to find the pattern
    while ((len_text - index_text) >= (len_pattern - index_pattern))
    {
        // If the character of the pattern is equal to the character of the text sum one to the index_pattern and index_text
        // to continue with the next's characters
        if (pattern[index_pattern] == text[index_text])
        {
            index_pattern++;
            index_text++;
        }

        // If the index_pattern is equal to the len_pattern, it means that we have found the pattern in the text
        if (index_pattern == len_pattern)
        {
            // Save the position of the match, and add one to
            // the position in terms of "position" and not in terms of "index"
            positions.push_back(index_text - index_pattern + 1);

            // Set index_pattern to the previous value in the pi array at position index_pattern - 1
            // to avoid starting from the beginning of the pattern and instead resume from a prefix-suffix that has already been matched
            // to continue find other occurrences of the pattern in the text
            index_pattern = pi[index_pattern - 1];
        }

        // If the index_text is less than the len_text, it means that we have not reached the end of the text and
        // the character of the pattern is different to the character of the text in the position index_text
        else if (index_text < len_text && pattern[index_pattern] != text[index_text])
        {
            if (index_pattern != 0)
            {
                // If index_pattern is different from 0, set index_pattern to the previous value in the pi array at position index_pattern - 1
                // to avoid starting from the beginning of the pattern and instead resume from a prefix-suffix that has already been matched
                index_pattern = pi[index_pattern - 1];
            }
            else
            {
                // If the index_pattern is 0, increase the index_text to continue with the next character in the text
                index_text++;
            }
        }
    }

    // Print the result if the content of the mcodeX.txt is in the transmission
    if (positions.size() > 0)
    {
        // positions.front() to get the first position of the match, since the algorithm iterate from left to right
        cout << "true " << positions.front() << endl;
    }
    else
    {
        cout << "false" << endl;
    }
}

// Second part: check if the content of the transmission files have a "mirroring code", that is, a palidrome
// to solve this task we use the Manacher algorithm, first we concatenate the text with a special character
// then we generate the LPS (Longest-Prefix-Suffix) array, and finally we find the maximum length palindrome

// Function
// Args:
// - text: string, the content of the transmissionX.txt

// Return:
// - None, only print the result
void mirroring_codeManacher(string text)
{
    // Initialize the special character empty
    string text_special = "";
    for (char e : text)
    {
        // Concatenate the special character between each character of the text
        text_special += "$";
        text_special += e;
    }
    text_special += "$";

    // Define the length of the text with the special character
    int len_text_special = text_special.size();

    // Define the vector of integers for the LPS array
    vector<int> LPS(len_text_special, 0);

    // Initialize the center and right position
    int center = 0, right = 0;

    // Iterate over the text with the special character to generate the LPS array
    for (int i = 1; i < len_text_special - 1; i++)
    {
        // Get the mirror position to avoid unnecessary comparisons
        int mirror = 2 * center - i;

        // If the current position is less than the right position
        // set the LPS at the minimum between the right position minus the current position (that is, the maximun prefix-suffix that we can use)
        // and the LPS at the mirror position to avoid unnecessary comparisons
        if (i < right)
            LPS[i] = min(right - i, LPS[mirror]);

        // Expand the palindrome centered at the current position
        // Check the current position plus one plus the LPS at the current position is less than the length of the text with the special character
        // and the current position minus one minus the LPS at the current position is greater or equal to 0 to avoid out of bounds
        // and most important check if the character at the right of the current position is equal to the character at the left of the current position
        // to expand the palindrome
        while ((i + 1 + LPS[i] < len_text_special) && (i - 1 - LPS[i] >= 0) &&
               (text_special[i + 1 + LPS[i]] == text_special[i - 1 - LPS[i]]))
            LPS[i]++;

        // Update the center and right position if the current position plus the LPS at the current position is greater than the right position
        // that is, we have found a longer palindrome
        if (i + LPS[i] > right)
        {
            center = i;
            right = i + LPS[i];
        }
    }

    // Now we can find the maximum length palindrome

    // Set the maximum length palindrome
    int max_len_palindrome = 0;

    // Set the center position of the maximum length palindrome
    int center_position = 0;

    // Iterate over each position of the text_special and find the maximum length palindrome
    for (int i = 0; i < len_text_special; i++)
    {
        // If we have found a longer palindrome
        if (LPS[i] > max_len_palindrome)
        {
            // Update the maximum length palindrome and the center position
            max_len_palindrome = LPS[i];
            center_position = i;
        }
    }

    // -- Uncoment to print the greater palindrome
    // for (int i = 0; i < text_special.size(); i++)
    // {
    //     if (LPS[i] == max_len_palindrome)
    //     {
    //         cout << endl;
    //         cout << "The greater palindrome is: ";
    //         for (int j = i - max_len_palindrome; j <= i + max_len_palindrome; j++)
    //         {
    //             if (text_special[j] != '$')
    //             {
    //                 cout << text_special[j];
    //             }
    //         }
    //         cout << endl;
    //         break;
    //     }
    // }

    // Calculate the start and end position in the original text
    // add one to get the position in terms of "position" and not in terms of "index"
    int start = (center_position - max_len_palindrome) / 2 + 1;
    int end = start + max_len_palindrome - 1;

    cout << "Posición inicial: " << start << endl;
    cout << "Posición final: " << end << endl;
}

// Third part: check the longest common substring between the two transmission files,
// to solve this task we use the Suffix Array algorithm, first we build the suffix array
// of the concatenated text, then we sort the suffix array lexicographically, and finally we
// traverse the sorted suffix array to find the longest common substring,
// we also do a substr function to get suffixes

// Function
// Args:
// - text: string, the content of a text
// - start: int, the start position to get the substring
// - end: int, the end position to get the substring
string mySubstr(string text, int start, int end = -1)
{
    if (end == -1 || end > text.size())
    {
        end = text.size();
    }
    string result = "";
    for (int i = start; i < end; i++)
    {
        result += text[i];
    }
    return result;
}

// Fuction
// Args:
// - text1: string, the content of the first transmission file
// - text2: string, the content of the second transmission file

// Return:
// - None, only print the result
void similitude_content_transmissionSuffixArray(string text1, string text2)
{
    // Concatenate both texts with a special character to avoid similarities between the texts
    string concatenated_text = text1 + "$" + text2;

    // Define the length of the concatenated text
    int len_concatenated_text = concatenated_text.size();

    // Define the vector of strings for the suffix array of each text
    // We use a tuple to get the origin position of the suffix
    vector<pair<string, int>> suffix_array_text(concatenated_text.size());

    // Build the suffix array with positions in terms of "position"
    for (int i = 0; i < concatenated_text.size(); i++)
    {
        // Call the function mySubstr to get the suffix and store it in the suffix_array_text
        suffix_array_text[i] = {mySubstr(concatenated_text, i), i + 1};
    }

    // -- Uncoment to print the unsorted suffix array
    // cout << "Unsorted suffix array:" << endl;
    // for (auto e : suffix_array_text)
    // {
    //     cout << e.first << " at position " << e.second << endl;
    // }

    // Sort the suffix array lexicographically with .sort() function of the STL
    sort(suffix_array_text.begin(), suffix_array_text.end());

    // -- Uncoment to print the sorted suffix array
    // Print the sorted suffix array
    // cout << "Sorted suffix array:" << endl;
    // for (auto e : suffix_array_text)
    // {
    //     cout << e.first << " at position " << e.second << endl;
    // }

    // Initialize the maximum similitude
    int max_similitude = 0;

    // Initialize the longest common substring
    string longest_common_substring;

    // Initialize the suffix's with the longest common substring
    pair<string, int> result_suffix_text1;
    pair<string, int> result_suffix_text2;

    // Define the split index to separate the two texts (position of the special character)
    int split_index = text1.size();

    // Iterate over the sorted suffix array to find the longest common substring
    // init i = 1 to difference between two suffixes
    for (int i = 1; i < suffix_array_text.size(); i++)
    {
        // Back suffix position
        int pos1 = suffix_array_text[i - 1].second;

        // Current suffix position
        int pos2 = suffix_array_text[i].second;

        // Check that the suffixes are from different parts (one from text1, the other from text2)
        // that is, one suffix is from the first text and the other is from the second text
        if ((pos1 < split_index && pos2 > split_index) || (pos1 > split_index && pos2 < split_index))
        {
            // Calculate LCP between suffix_array_text[i - 1] and suffix_array_text[i]
            int lcp_length = 0;

            // Compare the characters of the suffixes until they differ or until the end of one suffix is reached.
            // The first and second conditions prevent out-of-bounds errors by ensuring lcp_length does not exceed the suffix length.
            // The third condition checks if the characters of both suffixes at the current lcp_length position are equal.
            while (lcp_length < suffix_array_text[i - 1].first.size() &&
                   lcp_length < suffix_array_text[i].first.size() &&
                   suffix_array_text[i - 1].first[lcp_length] == suffix_array_text[i].first[lcp_length])
            {
                // Increase the lcp_length to continue with the next character
                lcp_length++;
            }

            // If the lcp_length is greater than the maximum similitude, update the maximum similitude and the longest common substring
            if (lcp_length > max_similitude)
            {
                max_similitude = lcp_length;
                longest_common_substring = mySubstr(suffix_array_text[i].first, 0, lcp_length);
                result_suffix_text1 = {suffix_array_text[i - 1].first, suffix_array_text[i - 1].second};
                result_suffix_text2 = {suffix_array_text[i].first, suffix_array_text[i].second};
            }
        }
    }
    // Print the position of the longest common substring in each text
    // It's not neccesary to add one to the position since the second element of the pair is in terms of "position" and not in terms of "index"
    // but we substract one since max_similitude is the length of the longest common substring
    cout << "Posición inicial en texto 1: " << result_suffix_text1.second << endl;
    cout << "Posición final en texto 1: " << result_suffix_text1.second + max_similitude - 1 << endl;
    cout << endl;
    cout << "Posición inicial en texto 2: " << result_suffix_text2.second - text1.size() << endl;
    cout << "Posición final en texto 2: " << (result_suffix_text2.second - text1.size()) + max_similitude - 1 << endl;

    // -- Uncoment to print the longest common substring
    // cout << "La subcadena más larga es: " << longest_common_substring << endl;
}

int main()
{
    // Define the vector of strings for the different types of files, so you can add more files of any type if it is necessary
    vector<string> name_transmission_files = {"transmission1.txt", "transmission2.txt"};
    vector<string> name_mcode_files = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};

    int number_transmission_files = name_transmission_files.size();
    int number_mcode_files = name_mcode_files.size();

    // Concatenate both vectors for processing all files together
    vector<string> name_files;
    name_files.insert(name_files.end(), name_transmission_files.begin(), name_transmission_files.end());
    name_files.insert(name_files.end(), name_mcode_files.begin(), name_mcode_files.end());

    int number_files = name_files.size();

    // Define the vector of strings for text of the files, initialized with the same size as name_files
    vector<string> text_files(number_files);

    for (int i = 0; i < number_files; i++)
    {
        // Open the file to read
        ifstream file(name_files[i]);

        if (!file.is_open())
        {
            cerr << "Error: Could not open file " << name_files[i] << endl;
            continue;
        }

        // Temporary variable to store each line
        string line;
        // Ensure it’s empty before accumulating content
        text_files[i] = "";

        // Read each line of the file and accumulate it in text_files[i]
        while (getline(file, line))
        {
            text_files[i] += line;
        }

        // Close the file
        file.close();
    }

    // Check if the files are not empty
    for (int i = 0; i < text_files.size(); i++)
    {
        if (text_files[i].empty())
        {
            cout << "Warning: The file " << name_files[i] << " is empty" << endl;
            return 1;
        }
    }

    // Part 1: verify if the content of any mcodeX.txt is in each transmissionX.txt
    cout << "Parte 1, verificar si el contenido de cualquier mcodeX.txt está en cada transmissionX.txt" << endl
         << endl;
    for (int i = number_transmission_files; i < number_files; i++)
    {
        cout << name_files[i] << endl;

        for (int j = 0; j < number_transmission_files; j++)
        {
            cout << name_files[j] << ": ";

            // Here, call the function that checks if the mcode is in the transmission
            is_content_in_transmissionKMP(text_files[i], text_files[j]);
        }

        cout << endl;
    }

    // Part 2: check if the content of the transmission files has a "mirroring code", or the largest palindrome
    cout << "Parte 2, verificar si el contenido de los archivos de transmisión tiene un \"código espejo\", es decir, el palíndromo más grande" << endl
         << endl;
    for (int i = 0; i < number_transmission_files; i++)
    {
        cout << name_files[i] << endl;
        // Here, call the function that checks if the transmission has a mirroring code
        mirroring_codeManacher(text_files[i]);
        cout << endl;
    }

    // Part 3: check for the longest common substring between transmission files
    cout << "Parte 3, verificar cual es la subcadena común más larga entre los archivos de transmisión" << endl
         << endl;
    for (int i = 0; i < number_transmission_files - 1; i++)
    {
        for (int j = i + 1; j < number_transmission_files; j++)
        {
            // Here, call the function that checks the longest common substring between the transmission files
            // We can modify the function to find the longest common substring between any number of files in the future
            // cause now only works for two files
            similitude_content_transmissionSuffixArray(text_files[i], text_files[j]);
        }
    }

    return 0;
}