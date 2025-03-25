#ifndef _TRIE_H
#define _TRIE_H

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "nodeTrie.h"

class trie
{
private:
    nodeTrie *root;
    void deleteNode(nodeTrie *node);
    void dfsHelper(nodeTrie *node, std::string &word);
    void autoCompleteHelper(nodeTrie *node, std::string &word);

public:
    trie();
    ~trie();
    void insert(std::string word);
    bool search(std::string word);
    void dfs();
    void autoComplete(std::string prefix);
};

#endif // _TRIE_H