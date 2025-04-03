#include <iostream>
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
Node* Encode::build_tree(const std::unordered_map<char, int>& counts) {
  class NodeComp {
  public:
    bool operator()(const Node* a, const Node* b) {
      return a->get_cost() >= b->get_cost();
    }
  };

  std::priority_queue <Node*, std::vector<Node*>, NodeComp> pq1;
  std::priority_queue <Node*, std::vector<Node*>, NodeComp> pq2;
  
  // Populate the first queue
  nodes.reserve(2 * counts.size());
  for (const auto& p : counts) {
    nodes.push_back(Node(p.second, p.first));
    pq1.push(&nodes.back());
  }

  std::cout << "pq1 Populated" << '\n';

  while(!pq1.empty() || !pq2.empty()) {

    std::cout << pq1.size() << " " << pq2.size() << " " << (pq1.size() + pq2.size() == 1) << '\n';

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
      return &nodes.back();
    }

    // Otherwise, make the two smallest nodes the child of a new node in pq2
    Node* temp_left = nullptr;
    Node* temp_right = nullptr;
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
    pq2.push(&nodes.back());

    std::cout << "new_parent: ";
    nodes.back().display();
  }

  return nullptr;
}

void Encode::build_embeddings(const Node* root) {

}

int main() {
  std::unordered_map<char, int> map;
  Encode e = Encode();
  e.count_chars("FortniteIsAVideoGameGafmeGameGamdfshfFfdsjk", map);
  Node* n = e.build_tree(map);
  std::cout << &n << '\n';
  n->traverse();
  return 0;
}