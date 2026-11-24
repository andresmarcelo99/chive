//
// Created by Marcelo Garcia on 11/23/26.
//

#ifndef CHIVE_PACKETQUEUE_H
#define CHIVE_PACKETQUEUE_H
#include "PacketNode.h"


class PacketQueue {
public:
    static constexpr int MAX_QUEUE_SIZE = 64;
    PacketQueue() = default;
    ~PacketQueue();

    PacketQueue(const PacketQueue&) = delete;
    PacketQueue& operator=(const PacketQueue&) = delete;

    bool dequeue(PacketData &out);
    bool enqueue(const PacketData &d);
    bool isEmpty();
    qint64 size() const;
    void clear();


private:
    PacketNode* front_ = nullptr;
    PacketNode* back_ = nullptr;
    qint64 counter_ = 0;
};


#endif //CHIVE_PACKETQUEUE_H
