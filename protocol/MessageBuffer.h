//
// Created by Marcelo Garcia on 11/21/26.
//

#ifndef CHIVE_MESSAGEBUFFER_H
#define CHIVE_MESSAGEBUFFER_H
#include <QByteArray>
#include <QString>


class MessageBuffer {
public:
    static constexpr int MAX_LINE = 512;
    bool append(const QByteArray &data);
    bool nextLine(QString &line);

private:
    QByteArray msgBufferArr_;
};


#endif //CHIVE_MESSAGEBUFFER_H
