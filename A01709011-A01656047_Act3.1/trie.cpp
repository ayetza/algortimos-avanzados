#include "trie.h"

trie::trie()
{
    root = new nodeTrie();
}

trie::~trie()
{
    deleteNode(root);
}

void trie::deleteNode(nodeTrie *node)
{
    if (node != nullptr)
    {
        for (nodeTrie *child : node->getChildren())
        {
            delete (child);
        }
    }
}

void trie::insert(std::string word)
{
    nodeTrie *current = root;
    for (int i = 0; i < (int)word.length(); i++)
    {
        if (current->getChild(word[i]) == nullptr)
        {
            nodeTrie *newNode = new nodeTrie(word[i], current);
            current->setChild(newNode);
        }
        current = current->getChild(word[i]);
    }
    current->setIsLeaf(true);
}

bool trie::search(std::string word)
{
    nodeTrie *current = root;
    if (current == nullptr)
        return false;
    for (int i = 0; i < (int)word.length(); i++)
    {
        current = current->getChild(word[i]);
        if (current == nullptr)
            return false;
    }
    return current->getIsLeaf();
}

void trie::dfs()
{
    std::string word;
    dfsHelper(root, word);
}

void trie::dfsHelper(nodeTrie *node, std::string &word)
{
    if (node == nullptr)
        return;

    if (node->getIsLeaf())
    {
        std::cout << word << std::endl;
    }
    for (nodeTrie *child : node->getChildren())
    {
        if (child != nullptr)
        {
            word.push_back(child->getLetter());
            dfsHelper(child, word);
            word.pop_back();
        }
    }
}

void trie::autoComplete(std::string prefix)
{
    nodeTrie *current = root;
    for (char c : prefix)
    {
        current = current->getChild(c);
        if (current == nullptr)
        {
            return;
        }
    }

    std::string word = prefix;
    autoCompleteHelper(current, word);
}

void trie::autoCompleteHelper(nodeTrie *node,
                              std::string &word)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->getIsLeaf())
    {
        std::cout << word << std::endl;
    }

    for (nodeTrie *child : node->getChildren())
    {
        if (child != nullptr)
        {
            word.push_back(child->getLetter());
            autoCompleteHelper(child, word);
            word.pop_back();
        }
    }
}
