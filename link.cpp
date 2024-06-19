#include "link.h"
#include "node.h"
#include <iostream>
#include <string>

void Link::sendPacket(Node* sender, Packet* packet) {
    if (!sender || !packet) {
        std::cerr << "Error: Invalid sender or packet." << std::endl;
        return;
    }

    Node* receiver = this->other(sender);
    if (!receiver) {
        std::cerr << "Error: Could not determine receiver node." << std::endl;
        return;
    }

    int srcId = sender->id();
    int destId = receiver->id();

    std::cout << "Link: forwarding packet from node #" << srcId << " to node #" << destId << std::endl;
    receiver->receive(packet);
}
