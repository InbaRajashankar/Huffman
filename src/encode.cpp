#include <iostream>
#include <stack>
#include "encode.h"

/**
 * @brief populated hashmap containing the counts of characters in a string
 * 
 * @param s the string to be counted
 */
void Encode::count_chars() {
  std::cout << "s: " << s << '\n';
  for (const char& c : s) {
    if (counts.find(c) != counts.end())
      ++counts[c];
    else
      counts[c] = 1;
  }
  std::cout << "CHAR COUNTS:\n";
  for (const auto& pair: counts) {
    std::cout << pair.first << " " << pair.second << '\n';
  }
}

/**
 * @brief builds the tree that latently represents the embedding of each character
 */
std::shared_ptr<Node> Encode::build_tree(void) {
  class NodeComp {
  public:
    bool operator()(const std::shared_ptr<Node> a, const std::shared_ptr<Node> b) {
      return a->get_cost() >= b->get_cost();
    }
  };

  std::priority_queue <std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComp> pq1;
  std::priority_queue <std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComp> pq2;

  if (counts.empty())
    throw std::runtime_error("Encoder: counts not populated when build_tree called");
  
  // Populate the first queue
  nodes.reserve(2 * counts.size());
  for (const auto& p : counts) {
    std::cout << p.first << '\n';
    nodes.push_back(Node(p.second, p.first));
    pq1.push(std::make_shared<Node>(nodes.back()));
  }

  while(!pq1.empty() || !pq2.empty()) {
    std::cout << '\n';
    nodes.back().traverse();
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
          pq2.pop();
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
 * 
 * @param root the root of the embedding tree
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
}

/**
 * @brief getter for embeddings map
 */
std::unordered_map<char, std::vector<bool>> Encode::get_e_map(void) const {
  return embeddings;
}

/**
 * @brief creates boolean (bit) vector from string
 * the hashmap embeddings should be populated!
 * 
 * @param s the string to be converted
 * @param vec a vector of boolean to store the embeddings
 */
void Encode::build_embedding(std::vector<bool>& vec) const {
  if (embeddings.empty())
    throw std::runtime_error("embeddings not initialized before build_embeddding");
  for (const char& c : s)
    try {
      for (const bool& b : embeddings.at(c))
        vec.push_back(b);
    } catch (std::out_of_range& e) {
      std::cerr << c << " is not found in embeddings!\n";
      throw;
    }
}

int main() {
  std::unordered_map<char, int> map;
  Encode e = Encode("FortniteIsAVideoGameGafmeGameGamdfshfFfdsjk");
  e.count_chars();
  std::shared_ptr<Node> d = e.build_tree();
  d->traverse();
  e.build_e_map(d);
  std::cout << "\nEmbeddings Map built!\n";
  std::unordered_map<char, std::vector<bool>> m = e.get_e_map();
  for (const auto& pair : m) {
    std::cout << pair.first << " ";
    for (const bool& b : pair.second) {
      std::cout << b;
    }
    std::cout << '\n';
  }
  std::vector<bool> v;

  e.build_embedding(v);
  for (const bool& b : v) {
    std::cout << b;
  }
  std::cout << std::endl;
  return 0;
}