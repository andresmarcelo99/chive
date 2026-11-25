//
// Created by Marcelo Garcia on 11/24/26.
//

#include "AlertData.h"


AlertData::AlertData(const QString &id, const QString &ip, const QString &description, AlertType alertType, SeverityType severity,
    qint64 datetime) : nodeId(id), srcIp(ip), description(description), alertType(alertType), severity(severity), datetime(datetime) {
}
