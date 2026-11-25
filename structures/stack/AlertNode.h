//
// Created by Marcelo Garcia on 11/24/26.
//

#ifndef CHIVE_ALERTNODE_H
#define CHIVE_ALERTNODE_H
#include "AlertData.h"


class AlertNode {
public:
    explicit AlertNode(const AlertData &data);
    AlertData data;
    AlertNode *next_ = nullptr;
};


#endif //CHIVE_ALERTNODE_H
