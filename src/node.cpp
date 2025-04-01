#include <iostream>
#include "node.h"

/**
 * @brief constructor
 */
Node::Node(int c, char v, Node* l, Node* r) {
  left = l;
  right = r;
  cost = c;
  value = v;
}

/**
 * @brief the value and cost of the node
 */
void Node::display(void) const {
  std::cout << "Val: " << value << " Cost: " << cost << '\n';
}

/**
 * @brief getter for cost
 */
int Node::get_cost(void) const {
  return cost;
}

/**
 * @brief increments cost by 1
 */
void Node::inc_cost(void) {
  ++cost; 
}

/**
 * @brief setter for left
 */
void Node::set_left(Node* n) {
  left = n;
}

/**
 * @brief setter for right
 */
void Node::set_right(Node* n) {
  right = n;
}