#ifndef NODE_H
#define NODE_H
#endif

class Node {
public:
  Node(int c = 0, char v = '\0', Node* l = nullptr, Node* r = nullptr); 
  void display(void) const;
  int get_cost(void) const;
  void inc_cost(void);
  void set_left(Node* n);
  void set_right(Node* n);
  void traverse(const std::string buffer = "") const;

private:
  Node* left;
  Node* right;
  int cost;
  char value; 
};