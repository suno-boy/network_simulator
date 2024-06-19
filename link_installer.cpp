#include "link_installer.h"
#include "link.h"

Link* LinkInstaller::createLink(Node* a, Node* b) {
    return new Link(a, b);
}

void LinkInstaller::addLinkToNode(Node* node, Link* link) {
    node->links_.push_back(link);
}

Link* LinkInstaller::install(Node* a, Node* b) {
    Link* link = createLink(a, b);
    addLinkToNode(a, link);
    addLinkToNode(b, link);
    return link;
}
