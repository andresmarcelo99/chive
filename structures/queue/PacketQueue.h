//
// Created by Marcelo Garcia on 11/23/26.
//

#ifndef CHIVE_PACKETQUEUE_H
#define CHIVE_PACKETQUEUE_H
#include "PacketNode.h"


class PacketQueue {
public:
    PacketQueue();
    ~PacketQueue();

    PacketQueue(const PacketQueue&) = delete;
    PacketQueue& operator=(const PacketQueue&) = delete;

    bool dequeue(PacketData &out);
    bool enqueue(const PacketData &d);
    bool isEmpty();
    qint64 size();
    void clear();


private:
    PacketNode* front_ = nullptr;
    PacketNode* back_ = nullptr;
    qint64 counter_ = 0;
    int MAX_SIZE_ = 50;
};


#endif //CHIVE_PACKETQUEUE_H
