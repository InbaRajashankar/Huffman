#ifndef NODE_H
#define NODE_H
#endif

class Node {
public:
  Node(Node* l = nullptr, Node* r = nullptr, int c = 0, char v = '\0'); 
  void to_string(void) const;
  void inc_cost(void);

private:
  Node* left;
  Node* right;
  int cost;
  char value; 
};