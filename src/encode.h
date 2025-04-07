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
  std::shared_ptr<Node> build_tree(const std::unordered_map<char, int>& counts);
  void build_e_map(const std::shared_ptr<Node> root);
  void build_embedding(const std::string& s, std::vector<bool>& vec);
private:
  std::vector<Node> nodes;
  std::unordered_map<char, std::vector<bool>> embeddings;
};