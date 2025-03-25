#include "algoritmos.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// O(m)
vector<int> preprocessKMP(const string &P)
{
    int m = P.length();
    vector<int> LPS(m, 0);
    int i = 1, j = 0;
    while (i < m)
    {
        if (P[i] == P[j])
        {
            LPS[i] = ++j;
            i++;
        }
        else
        {
            j != 0 ? j = LPS[j - 1] : (LPS[i++] = 0);
        }
    }
    return LPS;
}

// Complejidad O(n+m)
vector<int> KMP(const string &T, const string &P)
{
    vector<int> positions;
    int n = T.length(), m = P.length();
    if (m == 0)
        return positions;

    vector<int> LPS = preprocessKMP(P);
    int i = 0, j = 0;

    while (i < n)
    {
        if (T[i] == P[j])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            positions.push_back(i - j);
            j = LPS[j - 1];
        }
        else if (i < n && T[i] != P[j])
        {
            j != 0 ? j = LPS[j - 1] : i++;
        }
    }
    return positions;
}

// Complejidad O(n+m)
vector<int> findAllOccurrences(const string &text, const string &pattern)
{
    return KMP(text, pattern);
}

// Manacher para palíndromos
// Complejidad O(n)
pair<pair<int, int>, string> findLongestPalindrome(const string &text)
{
    if (text.empty())
        return {{0, 0}, ""};

    string processed = "#";
    for (char c : text)
        processed += string(1, c) + "#";

    int n = processed.size();
    vector<int> P(n, 0);
    int C = 0, R = 0, maxLen = 0, centerIndex = 0;

    for (int i = 0; i < n; i++)
    {
        int mirror = 2 * C - i;
        if (i < R)
            P[i] = min(R - i, P[mirror]);

        int a = i + (1 + P[i]);
        int b = i - (1 + P[i]);
        while (a < n && b >= 0 && processed[a] == processed[b])
        {
            P[i]++;
            a++;
            b--;
        }

        if (i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }

        if (P[i] > maxLen)
        {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2;
    return {{start, start + maxLen - 1}, text.substr(start, maxLen)};
}

// Estructura para el algoritmo de Suffix Array con las nuevas funciones
// O(n log n)
struct SuffixArray
{
    string S;
    int n;
    vector<int> sa, lcp;

    SuffixArray(const string &s) : S(s + "$"), n(S.length()), sa(n), lcp(n)
    {
        vector<pair<string, int>> suffixList = createSuffixArray(S);
        for (int i = 0; i < n; i++)
            sa[i] = suffixList[i].second;
        lcp = createPrefixArray(S, suffixList);
    }

    // O(n log n)
    vector<pair<string, int>> createSuffixArray(string T)
    {
        map<string, int> suffixMap;
        string sub = "";
        for (int i = T.length() - 1; i >= 0; i--)
        {
            sub = T[i] + sub;
            suffixMap[sub] = i;
        }
        vector<pair<string, int>> suffixList;
        for (auto &entry : suffixMap)
            suffixList.push_back(entry);
        return suffixList;
    }

    // O(n)
    vector<int> createPrefixArray(string T, vector<pair<string, int>> suffixList)
    {
        vector<int> inv(n, 0);
        for (int i = 0; i < n; i++)
            inv[suffixList[i].second] = i;
        int k = 0;
        vector<int> lcpArr(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (inv[i] == n - 1)
            {
                k = 0;
                continue;
            }
            int j = suffixList[inv[i] + 1].second;
            while (i + k < n && j + k < n && T[i + k] == T[j + k])
                k++;
            lcpArr[inv[i]] = k;
            if (k > 0)
                k--;
        }
        return lcpArr;
    }
};

// Suffix Array para LCS
// Complejidad O(n log n)
void findLCS(const string &T1, const string &T2)
{
    string S = T1 + "#" + T2;
    SuffixArray sa(S);
    int max_len = 0, start = 0, len1 = T1.length();

    for (int i = 0; i < S.length() - 1; i++)
    {
        if (sa.lcp[i] > max_len)
        {
            bool fromT1 = sa.sa[i] < len1;
            bool fromT2 = sa.sa[i + 1] < len1;
            if (fromT1 != fromT2)
            {
                max_len = sa.lcp[i];
                start = min(sa.sa[i], sa.sa[i + 1]);
            }
        }
    }

    if (max_len == 0)
        cout << "0 0 " << endl;
    else
        cout << start << " " << start + max_len - 1 << " " << S.substr(start, max_len) << endl;
}