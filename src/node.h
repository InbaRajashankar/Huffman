#pragma once

class Node {
public:
  Node(int c = 0, char v = '\0', std::shared_ptr<Node> l = nullptr, std::shared_ptr<Node> r = nullptr); 
  void display(void) const;
  int get_cost(void) const;
  char get_value(void) const;
  std::shared_ptr<Node> get_left(void) const;
  std::shared_ptr<Node> get_right(void) const;
  void inc_cost(void);
  void set_value(char c);
  void set_left(std::shared_ptr<Node> n);
  void set_right(std::shared_ptr<Node> n);
  void traverse(const std::string buffer = "") const;

private:
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;
  int cost;
  char value; 
};