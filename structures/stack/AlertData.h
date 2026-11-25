//
// Created by Marcelo Garcia on 11/24/26.
//

#ifndef CHIVE_ALERTDATA_H
#define CHIVE_ALERTDATA_H
#include <QString>

enum class AlertType {
    LATENCY, FLOOD, BRUTE, ATTACK
};

enum class SeverityType {
    LOW, MID, HIGH
};

struct AlertData {
    AlertData() = default;
    AlertData(const QString &id, const QString &ip, const QString &description, AlertType alertType, SeverityType severity, qint64 datetime);
    QString nodeId;
    QString srcIp;
    QString description;
    AlertType alertType = AlertType::LATENCY;
    SeverityType severity = SeverityType::LOW;
    qint64 datetime = 0;
};


#endif //CHIVE_ALERTDATA_H
