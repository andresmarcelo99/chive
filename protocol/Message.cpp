//
// Created by Marcelo Garcia on 11/21/26.
//

#include "Message.h"
#include <QStringList>

Message::Message(MsgType type, const QString &idNode, int cpu, int ram, int latency,
                 const QString &payload)
    : idNode_(idNode), payload_(payload), type_(type),
      cpu_(cpu), ram_(ram), latency_(latency) {}

//TIPO|ID_NODO|CPU|RAM|LATENCIA|PAYLOAD|CHECKSUM\n
QString Message::serialize() const {
    QString s = msgTypeToString(type_) + QString("|") + idNode_ + QString("|") + QString::number(cpu_) +
        QString("|") + QString::number(ram_) + QString("|") + QString::number(latency_) + QString("|") + payload_;
    int c = checksum(s);
    return s + QString("|") + QString::number(c) + QString("\n");
}

bool Message::parse(const QString &line, Message &out, QString &error) {
    if (line.isEmpty()) {
        error = "empty message";
        return false;
    }
    QStringList parts = line.split("|");
    if (parts.size() != 7) {
        error = "7 fields were expected, received: " + QString::number(parts.size());
        return false;
    }
    MsgType type;
    if (!msgTypeFromString(parts[0], type)) {
        error = "unknown type: " + parts[0];
        return false;
    }

    const QString &id = parts[1];
    if (id.isEmpty() || id.length()>32) {
        error = "ID_NODE with invalid length";
        return false;
    }

    for (QChar c : id) {
        if (!c.isLetterOrNumber() && c!='-') {
            error = "ID_NODE with invalid character: " + QString(c);
            return false;
        }
    }

    bool ok = false;
    int cpu = parts[2].toInt(&ok);
    if (!ok) {
        error = "CPU is not an int";
        return false;
    }

    int ram = parts[3].toInt(&ok);
    if (!ok) {
        error = "RAM is not an int";
        return false;
    }
    int latency = parts[4].toInt(&ok);
    if (!ok) {
        error = "LATENCY is not an int";
        return false;
    }
    int received = parts[6].toInt(&ok);
    if (!ok) {
        error = "CHECKSUM is not an int";
        return false;
    }

    if (cpu < 0 || cpu > 100) {
        error = "CPU out of range: " + parts[2];
        return false;
    }
    if (ram < 0 || ram > 100) {
        error = "RAM out of range: " + parts[3];
        return false;
    }
    if (latency < 0) {
        error = "LATENCY out of range: " + parts[4];
        return false;
    }

    const QString &payload = parts[5];
    if (payload.isEmpty()) {
        error = "empty PAYLOAD (use '-')";
        return false;
    }

    // El checksum cubre todo lo anterior al último '|'
    QString body = line.left(line.lastIndexOf('|'));
    if (checksum(body) != received) {
        error = "invalid checksum: expected " + QString::number(checksum(body))
                + ", received " + parts[6];
        return false;
    }

    out = Message(type, id, cpu, ram, latency, payload);
    return true;
}

int Message::checksum(const QString &text) {
    int result = 0;
    for (char b : text.toUtf8())
        result ^= static_cast<unsigned char>(b);   // XOR conversion
    return result;
}

QString Message::msgTypeToString(MsgType t) {
    switch (t) {
        case MsgType::TEL: return TELEMETRY;
        case MsgType::ATK: return ATTACK;
        case MsgType::HB: return HEARTBEAT;
        case MsgType::AUTH: return AUTH;
        case MsgType::CMD: return COMMAND;
        case MsgType::MSG: return MESSAGE;
        case MsgType::PONG: return PONG;
    }
    return "";
}

bool Message::msgTypeFromString(const QString &t, MsgType &out) {
    if (t == TELEMETRY){out = MsgType::TEL; return true;}
    if (t == AUTH){out = MsgType::AUTH; return true;}
    if (t == ATTACK){out = MsgType::ATK; return true;}
    if (t == HEARTBEAT){out = MsgType::HB; return true;}
    if (t == COMMAND){out = MsgType::CMD; return true;}
    if (t == MESSAGE){out = MsgType::MSG; return true;}
    if (t == PONG){out = MsgType::PONG; return true;}
    return false;
}
