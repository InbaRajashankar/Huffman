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
  void build_embeddings(const std::shared_ptr<Node> root);
  std::vector<bool> build_embeddings(const std::string s, Node& root);
private:
  std::vector<Node> nodes;
  std::unordered_map<char, std::vector<bool>> embeddings;
};