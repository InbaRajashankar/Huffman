#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "node.h"

class Encode {
public:
  Encode(std::string str) : s(str) {}
  void count_chars();
  std::shared_ptr<Node> build_tree(void);
  void build_e_map(const std::shared_ptr<Node> root);
  std::unordered_map<char, std::vector<bool>> get_e_map(void) const;
  void build_embedding(std::vector<bool>& vec) const;
private:
  const std::string s;
  std::unordered_map<char, int> counts;
  std::vector<Node> nodes;
  std::unordered_map<char, std::vector<bool>> embeddings;
};