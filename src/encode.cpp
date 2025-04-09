#include <iostream>
#include <stack>
#include "encode.h"

/**
 * @brief populated hashmap containing the counts of characters in a string
 * 
 * @param s the string to be counted
 * @param counts the hashmap to be populated
 */
void Encode::count_chars(const std::string& s, std::unordered_map<char, int>& counts) {
  if (!counts.empty())
    throw std::invalid_argument("A non-empty unordered_map was passed in!");

  for (char c : s) {
    if (counts.find(c) != counts.end())
      ++counts[c];
    else
      counts[c] = 1;
  }
}

/**
 * @brief builds the tree that latently represents the embedding of each character
 * 
 * @param counts a map storing character counts in the string
 */
std::shared_ptr<Node> Encode::build_tree(const std::unordered_map<char, int>& counts) {
  class NodeComp {
  public:
    bool operator()(const std::shared_ptr<Node> a, const std::shared_ptr<Node> b) {
      return a->get_cost() >= b->get_cost();
    }
  };

  std::priority_queue <std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComp> pq1;
  std::priority_queue <std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComp> pq2;
  
  // Populate the first queue
  nodes.reserve(2 * counts.size());
  for (const auto& p : counts) {
    nodes.push_back(Node(p.second, p.first));
    pq1.push(std::make_shared<Node>(nodes.back()));
  }

  while(!pq1.empty() || !pq2.empty()) {
    // Base case: if there is only one node left, return
    if (pq1.size() + pq2.size() == 1) return pq1.empty() ? pq2.top() : pq1.top();
    
    // Base case: if there is one node in each queue, return a parent of both
     else if (pq1.size() == 1 && pq2.size() == 1) {
      nodes.push_back(Node(
        pq1.top()->get_cost() + pq2.top()->get_cost(),
        '\0',
        pq1.top(),
        pq2.top()
      ));
      return std::make_shared<Node>(nodes.back());
    }

    // Otherwise, make the two smallest nodes the child of a new node in pq2
    std::shared_ptr<Node> temp_left = nullptr;
    std::shared_ptr<Node> temp_right = nullptr;
    while (temp_left == nullptr || temp_right == nullptr) {
      // if second pq is empty, take a node from first
      if (pq2.empty()) {
        temp_left == nullptr ? temp_left = pq1.top() : temp_right = pq1.top();
        pq1.pop();

      // if first pq is empty, take a node from second
      } else if (pq1.empty()) {
        temp_left == nullptr ? temp_left = pq2.top() : temp_right = pq2.top();
        pq2.pop();

      // if both queues have nodes, take the minimal nodes
      } else {
        if (pq1.top()->get_cost() <= pq2.top()->get_cost()) {
          temp_left == nullptr ? temp_left = pq1.top() : temp_right = pq1.top();
          pq1.pop();
        } else {
          temp_left == nullptr ? temp_left = pq2.top() : temp_right = pq2.top();
          pq1.pop();
        }
      }
    }

    nodes.push_back(Node(
      temp_left->get_cost() + temp_right->get_cost(),
      '\0',
      temp_left,
      temp_right
    ));
    pq2.push(std::make_shared<Node>(nodes.back()));
  }

  return nullptr;
}

/**
 * @brief build a hashmap containing the char to bool embeddings
 */
void Encode::build_e_map(const std::shared_ptr<Node> root) {
  // traverse through the tree, and add the embedding mapping to embeddings
  // left child -> add 0 to embedding
  // right child -> add 1 to embedding
  std::stack<std::pair<const std::shared_ptr<Node>, std::vector<bool>>> to_visit;
  to_visit.push({root, std::vector<bool>()});
  while (!to_visit.empty()) {
    std::pair<const std::shared_ptr<Node>, std::vector<bool>> cur = to_visit.top();
    to_visit.pop();
    if (cur.first->get_value() != '\0') {
      embeddings[cur.first->get_value()] = cur.second;
    }
    if (cur.first->get_left() != nullptr) {
      std::vector<bool> l_v = cur.second;
      l_v.push_back(false);
      to_visit.push({cur.first->get_left(), l_v});
    }
    if (cur.first->get_right() != nullptr) {
      std::vector<bool> l_r = cur.second;
      l_r.push_back(true);
      to_visit.push({cur.first->get_right(), l_r});
    }
  }
  // print
  for (const auto& pair : embeddings) {
    std::cout << pair.first << ' ';
    for (const bool& b: pair.second) {
      std::cout << b;
    }
    std::cout << std::endl;
  }
}

/**
 * @brief creates boolean (bit) vector from string
 * the hashmap embeddings should be populated!
 */
void Encode::build_embedding(const std::string& s, std::vector<bool>& vec) {
  if (embeddings.empty())
    throw std::runtime_error("embeddings not initialized before build_embeddding");
  for (const char& c : s)
    for (const bool& b: embeddings[c])
      vec.push_back(b);
}

// int main() {
//   std::unordered_map<char, int> map;
//   Encode e = Encode();
//   e.count_chars("FortniteIsAVideoGameGafmeGameGamdfshfFfdsjk", map);
//   std::shared_ptr<Node> d = e.build_tree(map);
//   // d->traverse();
//   e.build_e_map(d);
//   std::vector<bool> v;
//   e.build_embedding("FortniteIsAVideoGameGafmeGameGamdfshfFfdsjk", v);
//   for (const bool& b : v) {
//     std::cout << b;
//   }
//   std::cout << std::endl;
//   return 0;
// }