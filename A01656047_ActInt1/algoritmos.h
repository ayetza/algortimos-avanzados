#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <vector>
#include <string>
#include <utility>

std::vector<int> findAllOccurrences(const std::string &text, const std::string &pattern);
std::pair<std::pair<int, int>, std::string> findLongestPalindrome(const std::string &text);
void findLCS(const std::string &T1, const std::string &T2);

#endif