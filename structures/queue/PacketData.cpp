//
// Created by Marcelo Garcia on 11/23/26.
//

#include "PacketData.h"

PacketData::PacketData(Message msg, QString srcIp, qint64 arrivalMs): msg(msg), srcIp(srcIp), arrivalMs(arrivalMs) {}
