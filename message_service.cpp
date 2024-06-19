#include "message_service.h"
#include "packet.h"
#include <iostream>

void MessageService::send(std::string message) {
    Address srcAddress = Service::host_->address();
    short srcPort = Service::port_;
    
    Address destAddress = this->destAddress_;
    short destPort = this->destPort_;

    Packet* packet = new Packet(srcAddress, destAddress, srcPort, destPort, message);

    // Ensure packet is sent before returning control
    if (Service::host_) {
        Service::host_->send(packet);
    } else {
        std::cerr << "Error: Host is not available." << std::endl;
        delete packet;
    }
}

void MessageService::receivePacket(Packet* packet) {
    if (!packet) {
        std::cerr << "Error: Received null packet." << std::endl;
        return;
    }

    std::cout << "MessageService: received \"" << packet->dataString() << "\" from "
              << packet->srcAddress().toString() << ":" << packet->srcPort() << std::endl;

    delete packet;
}
