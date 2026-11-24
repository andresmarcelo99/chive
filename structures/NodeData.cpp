//
// Created by Marcelo Garcia on 11/23/26.
//

#include "NodeData.h"

NodeData::NodeData(const QString &id, const QString &ip, quint16 port, const QString &hostname,
                   qintptr socketDesc, quint64 lastHb)
    : id(id), ip(ip), port(port), hostname(hostname),
      socketDesc(socketDesc), lastHb(lastHb) {}
