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
  for (const auto& p : counts) {
    nodes.push_back(Node(p.second, p.first));
    pq1.push(&nodes.back());
  }

  std::cout << "pq1 Populated" << '\n';

  int i = 0;
  // READ MORE ABOUT SMART POINTERS BEFORE DOING
  while(!pq1.empty() || !pq2.empty()) {

    std::cout << pq1.size() << " " << pq2.size() << '\n';

    // Base case: if there is only one node left, return
    if (pq1.size() + pq2.size() == 1) {
      if (pq1.size() == 1) {
        Node* ret = pq1.top();
        pq1.pop();
        return ret;
      } else {
        Node* ret = pq2.top();
        pq1.pop();
        return ret;
      }
    // Base case: if there is one node in each queue, return a parent of both
    } else if (pq1.size() == 1 && pq2.size() == 1) {
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
      if (pq2.empty()) {
        temp_left = pq1.top();
        pq1.pop();
        temp_right = pq1.top();
        pq1.pop();
      } else if (pq1.empty()) {
        temp_left = pq2.top();
        pq1.pop();
        temp_right = pq2.top();
        pq1.pop();
      } else {
        if (pq1.top()->get_cost() <= pq2.top()->get_cost()) {
          if (temp_left == nullptr) {
            temp_left = pq1.top();
            pq1.pop();
          } else {
            temp_right = pq1.top();
            pq1.pop();
          }
        } else {
          if (temp_left == nullptr) {
            temp_left = pq2.top();
            pq2.pop();
          } else {
            temp_right = pq2.top();
            pq2.pop();
          }
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
    
    ++i;
    if (i > 40) break;
  }

  return nullptr;
  
  // CHECK FOR MEMORY LEAKS SOMEHOW
}

int main() {
  std::unordered_map<char, int> map;
  Encode e = Encode();
  e.count_chars("FortniteIsAVideoGameGameGameGamdfshfFfdsjk", map);
  e.build_tree(map);
  return 0;
}