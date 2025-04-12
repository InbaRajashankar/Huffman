#include <iostream>

#include "decode.h"

/**
 * @brief form a tree that latently stores char embeddings from a map
 * 
 * @param map a map storing the characters and their bit embeddings
 */
void Decode::rebuild_tree(const std::unordered_map<char, std::vector<bool>>& map, bool debug) {
  
  if (debug) {
    std::cout << "EMBEDDING MAP READ IN\n";
    for (const auto& pair : map) {
      std::cout << pair.first << " : ";
      for (const bool& b : pair.second)
        std::cout << b;
      std::cout << '\n';
    }
  }

  std::shared_ptr<Node> root = std::make_shared<Node>(Node());
  // for each character...
  for (const auto& item : map) {
    std::shared_ptr<Node> temp = root;
    // traverse down the tree based on the embedding of the  character
    for (const bool& b : item.second) {
      if (b == false) {
        if (temp->get_left() == nullptr) temp->set_left(std::make_shared<Node>(Node()));
        temp = temp->get_left();
      } else {
        if (temp->get_right() == nullptr) temp->set_right(std::make_shared<Node>(Node()));
        temp = temp->get_right();
      }
    }
    temp->set_value(item.first);
  }
  embedding_tree_root = root;
}

/**
 * @brief decode bits into a string
 * 
 * @param bits a boolean vector representing the bits
 */
std::string Decode::decode_bits(const std::vector<bool>& bits) const {
  std::shared_ptr<Node> temp = embedding_tree_root;
  std::string s;
  // traverse through the tree based on the bit pattern, and add a char to the string
  // if a char-containing node is found
  for (const bool& b: bits) {
    if (temp->get_value() == '\0') {
      if (!b) {
        if (temp->get_left() != nullptr)
          temp = temp->get_left();
        else
          throw std::runtime_error("Error decoding");
      }
      else
        if (temp->get_right() != nullptr)
          temp = temp->get_right();
        else 
          throw std::runtime_error("Error decoding");
    } else {
      s += temp->get_value();
      temp = embedding_tree_root;
    }
  }
  return s;
}

// int main() {
//   std::unordered_map<char, std::vector<bool>> test_map;
//   test_map['a'] = {true, false, true};
//   test_map['b'] = {false, false, true, true, false};
//   test_map['c'] = {true, true, true, true};
//   test_map['d'] = {false};
//   test_map['e'] = {true, false, true, false, true, false, true, false};
//   test_map['f'] = {false, false, false};
//   test_map['g'] = {true, false, true, true, false, true, false, true, true, true};
//   test_map['z'] = {};
//   test_map['@'] = {true, true, false};
//   test_map['#'] = {false, true, false, true};
//   test_map['1'] = {true};
//   Decode d = Decode();
//   d.rebuild_tree(test_map);
//   return 0;
// }