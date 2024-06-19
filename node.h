#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>

class Node {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

public:
  Node() : id_(nextId_++) {}
  int id() const { return id_; }
  std::vector<Link*> links_;
  virtual ~Node() {};
  virtual void receive(Packet* packet) = 0;
};

#endif