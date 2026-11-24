//
// Created by Marcelo Garcia on 11/23/26.
//

#ifndef CHIVE_CLIENTLIST_H
#define CHIVE_CLIENTLIST_H
#include "ClientNode.h"


class ClientList {
public:
    ClientList();
    ~ClientList();

    ClientList(const ClientList&) = delete;
    ClientList& operator=(const ClientList&) = delete;

    bool insert(const NodeData &data);
    ClientNode* findById(const QString &id);
    ClientNode* findBySocket(qintptr socketDesc);
    bool remove(const QString &id);
    int count() const;
    const ClientNode* head() const;

private:
    ClientNode *head_ = nullptr;
    ClientNode *tail_ = nullptr;
};


#endif //CHIVE_CLIENTLIST_H
