#include "bitacora.h"
#include "algoritmos.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// complejidad O(n)
string readFile(const std::string &filename)
{
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    string result;
    for (char ch : content)
    {
        if (ch != '\n' && ch != '\r')
            result += ch;
    }
    return result;
}

// complejidad O(n log n)
void generateReport()
{
    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");
    vector<string> mcodes = {readFile("mcode1.txt"), readFile("mcode2.txt"), readFile("mcode3.txt")};

    // Parte 1: Búsqueda de códigos maliciosos
    // O(n+m)
    cout << "Parte 1" << endl;
    for (size_t i = 0; i < mcodes.size(); i++)
    {
        vector<int> t1_pos = findAllOccurrences(transmission1, mcodes[i]);
        vector<int> t2_pos = findAllOccurrences(transmission2, mcodes[i]);

        auto printResults = [](const vector<int> &positions)
        {
            if (positions.empty())
                cout << "false" << endl;
            else
            {
                cout << "true ";
                for (size_t j = 0; j < positions.size(); j++)
                {
                    cout << positions[j] << (j < positions.size() - 1 ? " " : "");
                }
                cout << endl;
            }
        };

        printResults(t1_pos);
        printResults(t2_pos);
    }

    // Parte 2: Palíndromos más largos
    // O(n)
    cout << "Parte 2" << endl;
    auto p1 = findLongestPalindrome(transmission1);
    auto p2 = findLongestPalindrome(transmission2);
    cout << p1.first.first << " " << p1.first.second << " " << p1.second << endl;
    cout << p2.first.first << " " << p2.first.second << " " << p2.second << endl;

    // Parte 3: Subcadena común más larga
    // O(n log n)
    cout << "Parte 3" << endl;
    findLCS(transmission1, transmission2);
}