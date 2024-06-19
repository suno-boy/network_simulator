#include "host.h"
#include <iostream>
#include <map>
#include <vector>

// Helper functions to separate concerns
void logPacketSend(int hostId, const std::string& srcAddress, const std::string& destAddress, unsigned long fileBytes) {
    std::cout << "Host #" << hostId << ": sending packet (from: " << srcAddress << ", to: " << destAddress << ", " << fileBytes << " bytes)" << std::endl;
}

void logNoService(int hostId, const std::string& srcAddress, const std::string& destAddress, unsigned long fileBytes) {
    std::cout << "Host #" << hostId << ": no service for packet (from: " << srcAddress << ", to: " << destAddress << ", " << fileBytes << " bytes)" << std::endl;
}

void logPacketReceived(int hostId, short destPort) {
    std::cout << "Host #" << hostId << ": received packet, destination port: " << destPort << std::endl;
}

void Host::initialize() {
    openPort();
}

void Host::openPort() {
    for (auto& service : services_) {
        short port = service->getPort();

        if (port < 0) port = INIT_CLIENT_PORT;
        while (portToService_.find(port) != portToService_.end()) {
            port++;
        }

        service->setPort(port);
        portToService_[port] = service;
    }
}

void Host::send(Packet* packet) {
    if (!links_.empty()) {
        std::string srcAddress = packet->srcAddress().toString();
        std::string destAddress = packet->destAddress().toString();
        unsigned long fileBytes = packet->data().size();

        logPacketSend(id(), srcAddress, destAddress, fileBytes);
        links_.front()->sendPacket(this, packet);
    }
}

void Host::receive(Packet* packet) {
    auto it = portToService_.find(packet->destPort());
    if (it == portToService_.end()) {
        std::string srcAddress = packet->srcAddress().toString();
        std::string destAddress = packet->destAddress().toString();
        unsigned long fileBytes = packet->data().size();

        logNoService(id(), srcAddress, destAddress, fileBytes);
        return;
    }
    Service* service = it->second;
    logPacketReceived(id(), packet->destPort());
    service->receivePacket(packet);
}

Host::~Host() {
    for (auto& service : services_) {
        delete service;
    }
}
