#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "node.h"

/**
 * @brief populated hashmap containing the counts of characters in a string
 * 
 * @param s the string to be counted
 * @param counts the hashmap to be populated
 */
void count_chars(const std::string& s, std::unordered_map<char, int>& counts) {
  if (!counts.empty())
    throw std::invalid_argument("A non-empty unordered_map was passed in!");

  for (char c : s) {
    if (counts.find(c) != counts.end())
      ++counts[c];
    else
      counts[c] = 1;
  }
}

std::unique_ptr<Node> build_tree(const std::unordered_map<char, int>& counts) {
  class NodeComp {
  public:
    bool operator()(const std::unique_ptr<Node>& a, const std::unique_ptr<Node>& b) {
      return a->get_cost() >= b->get_cost();
    }
  };

  std::priority_queue
    <std::unique_ptr<Node>, std::vector<std::unique_ptr<Node>>, NodeComp> pq1;
  std::priority_queue
    <std::unique_ptr<Node>, std::vector<std::unique_ptr<Node>>, NodeComp> pq2;
  
  // Populate the first queue
  for (const auto& p : counts)
    pq1.push(std::make_unique<Node>(p.second, p.first));

  // READ MORE ABOUT SMART POINTERS BEFORE DOING
  while(!pq1.empty() || !pq2.empty()) {
    // 1 is empty -> empty 2
    // 2 is empty -> take top 2 from 1 (unless 1 only has 1)
    pq1.top()->display();
    pq1.pop();
  }

  return nullptr;
  
  // CHECK FOR MEMORY LEAKS SOMEHOW
}

int main() {
  std::unordered_map<char, int> map;
  count_chars("FortniteIsAVideoGameGameGameGamdfshfFfdsjk", map);
  build_tree(map);
  return 0;
}