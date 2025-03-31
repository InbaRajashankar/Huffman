#include <iostream>
#include "node.h"

/**
 * @brief constructor
 */
Node::Node(Node* l = nullptr, Node* r = nullptr, int c = 0, char v = '\0') {
  left = l;
  right = r;
  cost = c;
  value = v;
}

/**
 * @brief the value and cost of the node
 */
void Node::to_string(void) const {
  std::cout << "Val: " << value << " Cost: " << cost << '\n';
}

/**
 * @brief increments cost by 1
 */
void Node::inc_cost(void) {
  ++cost; 
}