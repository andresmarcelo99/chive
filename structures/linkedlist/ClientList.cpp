//
// Created by Marcelo Garcia on 11/23/26.
//

#include "ClientList.h"


ClientList::~ClientList() {
    ClientNode* curr = head_;
    while (curr != nullptr) {
        ClientNode* tmp = curr->next;
        delete curr;
        curr = tmp;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

bool ClientList::insert(const NodeData &data) {
    if (findById(data.id) != nullptr) {
        return false;
    }

    ClientNode* newNode = new ClientNode(data);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    }else {
        tail_->next = newNode;
        tail_ = newNode;
    }
    return true;
}

ClientNode* ClientList::findById(const QString &id) {
    ClientNode* curr = head_;
    while (curr != nullptr) {
        if (id == curr->data.id) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

ClientNode* ClientList::findBySocket(qintptr socketDesc) {
    ClientNode* curr = head_;
    while (curr != nullptr) {
        if (socketDesc == curr->data.socketDesc) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool ClientList::remove(const QString &id) {
    ClientNode* prev = head_;
    if (prev == nullptr) {
        return false;
    }

    if (prev->data.id == id) {
        head_ = head_->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        }
        delete prev;
        return true;
    }

    ClientNode* curr = head_->next;
    while (curr != nullptr) {
        if (curr->data.id == id) {
            if (curr == tail_) {
                tail_ = prev;
            }
            prev->next = curr->next;
            delete curr;
            curr = nullptr;
            return true;
        }
        prev = prev->next;
        curr = curr->next;
    }

    return false;
}

int ClientList::count() const {
    int counter = 0;
    ClientNode* curr = head_;

    while (curr != nullptr) {
        counter++;
        curr = curr->next;
    }

    return counter;
}

const ClientNode* ClientList::head() const {
    return head_;
}
