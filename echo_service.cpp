#include "echo_service.h"
#include <iostream>

// 패킷 수신 시 처리하는 함수
void EchoService::receivePacket(Packet* packet) {
    // 수신된 패킷 정보를 출력
    std::cout << "EchoService: received \"" << packet->dataString() 
              << "\" from " << packet->srcAddress().toString() 
              << ":" << packet->srcPort() 
              << ", sending reply with the same data" << std::endl;
    
    // 패킷을 처리하여 응답을 전송
    this->processAndSendReply(packet);
}

// 패킷을 처리하여 응답을 전송하는 함수
void EchoService::processAndSendReply(Packet* packet) {
    Packet* replyPacket = createReplyPacket(packet);
    this->host_->send(replyPacket);

    // 기존 패킷을 삭제하여 메모리 누수 방지
    delete packet;
}

// 응답 패킷을 생성하는 함수
Packet* EchoService::createReplyPacket(Packet* packet) {
    Address srcAddress = this->host_->address();
    short srcPort = this->getPort();

    Address destAddress = packet->srcAddress();
    short destPort = packet->srcPort();

    // 새 패킷 생성 및 반환
    return new Packet(srcAddress, destAddress, srcPort, destPort, packet->data());
}
