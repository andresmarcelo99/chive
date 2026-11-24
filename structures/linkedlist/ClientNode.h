//
// Created by Marcelo Garcia on 11/23/26.
//

#ifndef CHIVE_CLIENTNODE_H
#define CHIVE_CLIENTNODE_H
#include "NodeData.h"

struct ClientNode {
    explicit ClientNode(const NodeData &data);

    NodeData data;
    ClientNode* next = nullptr;
};

#endif //CHIVE_CLIENTNODE_H
