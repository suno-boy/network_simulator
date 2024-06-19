#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;
};

class Router : public Node {

public :
  void receive(Packet* packet) override;
  virtual ~Router() {};
  void logForwarding(const std::string& srcAddress, const std::string& destAddress, unsigned long fileBytes) const;
  void logNoRoute(const std::string& srcAddress, const std::string& destAddress, unsigned long fileBytes) const;
  void forwardPacket(Packet* packet);

protected:
  std::vector<RoutingEntry> routingTable_;
};

#endif