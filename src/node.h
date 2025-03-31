#ifndef NODE_H
#define NODE_H
#endif

class Node {
public:
  Node(int c = 0, char v = '\0', Node* l = nullptr, Node* r = nullptr); 
  void display(void) const;
  void inc_cost(void);
  int get_cost(void) const;

private:
  Node* left;
  Node* right;
  int cost;
  char value; 
};