//
// Created by Marcelo Garcia on 11/23/26.
//

#ifndef CHIVE_PACKEDNODE_H
#define CHIVE_PACKEDNODE_H
#include "PacketData.h"
#include "protocol/Message.h"


class PacketNode {
public:
    explicit PacketNode(const PacketData &data);
    PacketData data;
    PacketNode *next_ = nullptr;

};

#endif //CHIVE_PACKEDNODE_H
