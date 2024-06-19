#include "echo_service_installer.h"

EchoService *EchoServiceInstaller::install(Host *host) {
  EchoService* echoService = new EchoService(host, this->listenPort_);
  ServiceInstaller::install(host, echoService);
  return echoService;
}