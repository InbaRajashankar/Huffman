#ifndef ENCODE_H
#define ENCODE_H
#endif

#include <string>
#include <vector>
#include <unordered_map>
#include "node.h"

class Encode {
public:
  void count_chars(const std::string& s, std::unordered_map<char, int>& counts);
  Node* build_tree(const std::unordered_map<char, int>& counts);  
  std::vector<bool> encode_string(const std::string s, Node& root);
private:
  std::vector<Node> nodes;
};