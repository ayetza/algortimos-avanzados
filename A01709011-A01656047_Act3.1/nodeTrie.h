#ifndef _NODETRIE_H
#define _NODETRIE_H

#include <iostream>
#include <vector>

class nodeTrie
{
private:
    char letter;
    bool isLeaf;
    nodeTrie *parent;
    std::vector<nodeTrie *> child;

public:
    nodeTrie();
    nodeTrie(char c, nodeTrie *p);
    nodeTrie *getChild(char c);
    std::vector<nodeTrie *> getChildren();
    void setChild(nodeTrie *ptrChild);
    bool getIsLeaf();
    void setIsLeaf(bool value);
    char getLetter();
};

#endif // _NODETRIE_H