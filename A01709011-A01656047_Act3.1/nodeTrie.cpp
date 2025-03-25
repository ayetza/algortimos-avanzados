#include "nodeTrie.h"

nodeTrie::nodeTrie()
{
    letter = '\0';
    isLeaf = false;
    parent = nullptr;
    child = std::vector<nodeTrie *>(26, nullptr);
}
nodeTrie::nodeTrie(char c, nodeTrie *ptrParent)
{
    letter = c;
    isLeaf = false;
    parent = ptrParent;
    child = std::vector<nodeTrie *>(26, nullptr);
}

nodeTrie *nodeTrie::getChild(char c)
{
    return child[c - 'a'];
}

std::vector<nodeTrie *> nodeTrie::getChildren()
{
    return child;
}

void nodeTrie::setChild(nodeTrie *ptrChild)
{
    child[ptrChild->letter - 'a'] = ptrChild;
}

bool nodeTrie::getIsLeaf()
{
    return isLeaf;
}

void nodeTrie::setIsLeaf(bool value)
{
    isLeaf = value;
}

char nodeTrie::getLetter()
{
    return letter;
}
