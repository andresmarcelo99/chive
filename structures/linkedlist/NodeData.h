//
// Created by Marcelo Garcia on 11/23/26.
//

#ifndef CHIVE_NODEDATA_H
#define CHIVE_NODEDATA_H
#include <QString>

enum class NodeStatus {
    ACTIVE, WARNING, BLOCKED, DISCONNECTED
};

struct NodeData {
    NodeData() = default;
    NodeData(const QString &id, const QString &ip, quint16 port, const QString &hostname,
             qintptr socketDesc, quint64 lastHb);

    QString id;
    QString ip;
    quint16 port = 0;
    QString hostname;
    NodeStatus status = NodeStatus::ACTIVE;
    qintptr socketDesc = 0;
    quint64 lastHb = 0;
};

#endif //CHIVE_NODEDATA_H
