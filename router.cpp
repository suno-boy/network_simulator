#include "router.h"

void Router::receive(Packet* packet) {
    this->forwardPacket(packet);
}

void Router::forwardPacket(Packet* packet) {
    std::string srcAddress = packet->srcAddress().toString();
    std::string destAddress = packet->destAddress().toString();
    unsigned long Byte = packet->data().size();

    for (const RoutingEntry& routingEntry : routingTable_) {
        if (routingEntry.destination == packet->destAddress()) {
            logForwarding(srcAddress, destAddress, Byte);
            routingEntry.nextLink->sendPacket(this, packet);
            return;
        }
    }

    logNoRoute(srcAddress, destAddress, Byte);
}

void Router::logForwarding(const std::string& srcAddress, const std::string& destAddress, unsigned long fileBytes) const {
    std::cout << "Router #" << this->id() << ": forwarding packet (from: " << srcAddress << ", to: " << destAddress << ", " << fileBytes << " bytes)" << std::endl;
}

void Router::logNoRoute(const std::string& srcAddress, const std::string& destAddress, unsigned long fileBytes) const {
    std::cout << "Router #" << this->id() << ": no route for packet (from: " << srcAddress << ", to: " << destAddress << ", " << fileBytes << " bytes)" << std::endl;
}
