//
// Created by Marcelo Garcia on 11/23/26.
//

#include "PacketQueue.h"

PacketQueue::~PacketQueue() {
    clear();
}

bool PacketQueue::dequeue(PacketData &out) {
    if (front_ == nullptr) {
        return false;
    }
    PacketNode *tmp = front_;
    front_ = front_->next_;
    if (front_ == nullptr) {
        back_ = nullptr;
    }
    out = tmp->data;
    delete tmp;
    counter_--;
    return true;
}

bool PacketQueue::enqueue(const PacketData &d) {
    if (counter_ == MAX_QUEUE_SIZE) {
        return false;
    }
    auto* pn = new PacketNode(d);

    if (front_ == nullptr) {
        front_ = pn;
        back_ = pn;
    }else {
        back_->next_ = pn;
        back_ = pn;
    }
    counter_++;
    return true;
}

bool PacketQueue::isEmpty() {
    return front_ == nullptr;
}

qint64 PacketQueue::size() const {
    return counter_;
}

void PacketQueue::clear() {
    PacketData discard;
    while (dequeue(discard));
}
