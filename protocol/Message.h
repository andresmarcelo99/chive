//
// Created by Marcelo Garcia on 11/21/26.
//

#ifndef CHIVE_MESSAGE_H
#define CHIVE_MESSAGE_H
#include <QString>


class Message {
public:
    enum class MsgType {
        TEL, HB, PONG, AUTH, ATK, CMD, MSG
    };

    static inline const QString TELEMETRY = "TEL";
    static inline const QString HEARTBEAT = "HB";
    static inline const QString PONG = "PONG";
    static inline const QString ATTACK = "ATK";
    static inline const QString AUTH = "AUTH";
    static inline const QString COMMAND = "CMD";
    static inline const QString MESSAGE = "MSG";

    Message() = default;
    Message(MsgType type, const QString &idNode, int cpu, int ram, int latency,
            const QString &payload);

    QString serialize() const;
    static bool parse(const QString &line, Message &out, QString &error);

    QString getIdNode() {return this->idNode_;}
    QString getPayload() {return this->payload_;}
    MsgType getMsgType() {return this->type_;}
    int getCpu() {return this->cpu_;}
    int getRam() {return this->ram_;}
    int getLatency() {return this->latency_;}

private:
    static QString msgTypeToString(MsgType t);
    static bool msgTypeFromString(const QString &t, MsgType &out);
    static int checksum(const QString &text);

    QString idNode_;
    QString payload_;
    MsgType type_ = MsgType::TEL;
    int cpu_ = 0;
    int ram_ = 0;
    int latency_ = 0;

};


#endif //CHIVE_MESSAGE_H
