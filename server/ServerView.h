//
// Created by Marcelo Garcia on 11/20/26.
//

#ifndef CHIVE_SERVERVIEW_H
#define CHIVE_SERVERVIEW_H

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/ftxui.hpp>

#include "IdsServer.h"


class ServerView {
public:
    explicit ServerView(IdsServer &server);
    int runServer();
private:
    void displayServer();
    ftxui::Element header();
    ftxui::Element table();
    // auto inputBox(ftxui::App screen );
    int sel_ = 0;
    IdsServer& server_;
};


#endif //CHIVE_SERVERVIEW_H
