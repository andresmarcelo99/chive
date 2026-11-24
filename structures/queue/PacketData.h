//
// Created by Marcelo Garcia on 11/23/26.
//

#ifndef CHIVE_PACKETDATA_H
#define CHIVE_PACKETDATA_H
#include <QString>
#include "protocol/Message.h"

struct PacketData {
    PacketData() = default;
    PacketData(Message msg, QString srcIp, qint64 arrivalMs);

    Message msg;
    QString srcIp;
    qint64 arrivalMs = 0;
};


#endif //CHIVE_PACKETDATA_H
