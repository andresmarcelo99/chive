//
// Created by Marcelo Garcia on 11/20/26.
//

#ifndef CHIVE_AGENTVIEW_H
#define CHIVE_AGENTVIEW_H

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/ftxui.hpp>

#include "ClientAgent.h"

class AgentView {
public:
    explicit AgentView(ClientAgent &client);
    int runAgentClient();
private:
    void displayAgentClient();
    ftxui::Element header();
    ftxui::Element table();
    // auto inputBox(ftxui::App screen );
    int sel_ = 0;
    ClientAgent& agent_;
};


#endif //CHIVE_AGENTVIEW_H
