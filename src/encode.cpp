#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "node.h"

/**
 * @brief populated hashmap containing the counts of characters in a string
 * 
 * @param s the string to be counted
 * @param counts the hashmap to be populated
 */
void count_chars(const std::string& s, std::unordered_map<char, int>& counts) {
  if (!counts.empty())
    throw std::invalid_argument("A non-empty unordered_map was passed in!");

  for (char c : s) {
    if (counts.find(c) != counts.end())
      ++counts[c];
    else
      counts[c] = 1;
  }
}