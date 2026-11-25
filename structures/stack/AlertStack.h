//
// Created by Marcelo Garcia on 11/24/26.
//

#ifndef CHIVE_ALERTSTACK_H
#define CHIVE_ALERTSTACK_H
#include "AlertData.h"
#include "AlertNode.h"


class AlertStack {
public:
    static constexpr int MAX_STACK_SIZE = 64;
    AlertStack() = default;
    ~AlertStack();

    AlertStack(const AlertStack&) = delete;
    AlertStack& operator=(const AlertStack&) = delete;

    bool pop(AlertData &out);
    bool push(const AlertData &d);
    const AlertNode* head() const;
    void clear();
    bool peek(AlertData &out) const;
    bool isEmpty();
    qint64 size() const;

private:
    AlertNode* top_ = nullptr;
    qint64 counter_ = 0;
};


#endif //CHIVE_ALERTSTACK_H
