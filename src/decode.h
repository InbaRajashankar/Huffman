#ifndef DECODE_H
#define DECODE_H
#endif

#include <string>
#include <vector>
#include <unordered_map>
#include "node.h"

std::shared_ptr<Node> rebuild_tree(const std::vector<bool>& bits);
std::string decode_bits(const std::vector<bool>& bits, const Node& root);