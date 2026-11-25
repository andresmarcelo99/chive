//
// Created by Marcelo Garcia on 11/24/26.
//

#include "AlertStack.h"

AlertStack::~AlertStack() {
    clear();
}

bool AlertStack::pop(AlertData &out) {
    if (top_ == nullptr) {
        return false;
    }
    AlertNode *tmp = top_;
    top_ = top_->next_;
    out = tmp->data;
    delete tmp;
    counter_--;
    return true;
}

bool AlertStack::push(const AlertData &d) {
    if (counter_ == MAX_STACK_SIZE) {
        AlertNode *prev = top_;
        AlertNode *curr = top_->next_;
        while (curr->next_ != nullptr) {
            prev = prev->next_;
            curr = curr->next_;
        }
        prev->next_ = nullptr;
        delete curr;
        counter_--;
    }

    auto* an = new AlertNode(d);
    if (top_==nullptr) {
        top_ = an;
    }else {
        an->next_ = top_;
        top_ = an;
    }
    counter_++;
    return true;
}

const AlertNode * AlertStack::head() const {
    return top_;
}

void AlertStack::clear() {
    AlertData discard;
    while (pop(discard));
}

bool AlertStack::peek(AlertData &out) const {
    if (top_==nullptr) {
        return false;
    }
    AlertData ad =  top_->data;
    out = ad;
    return true;
}

bool AlertStack::isEmpty() {
    return top_ == nullptr;
}

qint64 AlertStack::size() const {
    return counter_;
}
