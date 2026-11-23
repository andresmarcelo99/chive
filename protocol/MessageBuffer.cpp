//
// Created by Marcelo Garcia on 11/21/26.
//

#include "MessageBuffer.h"

bool MessageBuffer::append(const QByteArray &data) {
    msgBufferArr_.append(data);

    if (msgBufferArr_.size() > MAX_LINE && !msgBufferArr_.contains('\n')) {
        msgBufferArr_.clear();
        return false;
    }
    return true;
}

bool MessageBuffer::nextLine(QString &line) {
    int firstEscp = msgBufferArr_.indexOf('\n');
    if (firstEscp == -1 ) {
        return false;
    }
    line = QString::fromUtf8(msgBufferArr_.left(firstEscp));
    msgBufferArr_.remove(0, firstEscp + 1);
    return true;
}