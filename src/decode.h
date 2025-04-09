#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "node.h"

class Decode {
public:
  void rebuild_tree(const std::unordered_map<char, std::vector<bool>>& map);
  std::string decode_bits(const std::vector<bool>& bits) const;
private:
  std::shared_ptr<Node> embedding_tree_root;
};