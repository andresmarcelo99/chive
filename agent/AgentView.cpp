//
// Created by Marcelo Garcia on 11/20/26.
//

#include "AgentView.h"

AgentView::AgentView(ClientAgent &client): agent_(client) {}

int AgentView::runAgentClient() {
    displayAgentClient();
    return 0;
}

void AgentView::displayAgentClient() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    auto view = ftxui::Renderer([&] {
    return ftxui::vbox({
        header(),
        ftxui::hbox({
        ftxui::vbox({
            window(ftxui::text(" Mapa de nodos "), table()) | ftxui::flex,
            ftxui::window(ftxui::text(" Tráfico "), ftxui::text("TODO")),
        }) | ftxui::flex,
            ftxui::window(ftxui::text(" Alertas críticas "), ftxui::text("TODO")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30),
        }) | ftxui::flex,
        ftxui::window(ftxui::text(" Consola de tramas "), ftxui::text("TODO")) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 8),
        ftxui::text(" ↑↓ navegar   b bloquear   c limpiar   ? ayuda   q salir") | ftxui::dim,
        }) | ftxui::border;
    });

    view |= ftxui::CatchEvent([&](ftxui::Event e) {
        if (e == ftxui::Event::Character('q')) {
            screen.Exit();
            return true;
        }
        return false;
    });
    screen.Loop(view);
}

ftxui::Element AgentView::header() {
    //TODO agent size
    int agentSize = 3;

    return ftxui::hbox({
        ftxui::vbox({
            ftxui::text("Servidor: 0.0.0.0:8080"),
            ftxui::text("Agentes:  " + std::to_string(agentSize)),
        }),
        ftxui::filler(),
        ftxui::vbox({
            ftxui::text("<:> comando   </> filtrar") | ftxui::dim,
            ftxui::text("<j/k> mover   <d> borrar   <q> salir") | ftxui::dim,
        }),
    }) | ftxui::border;
}

ftxui::Element AgentView::table() {
    //TODO agent size
    int agentSize = 3;

    ftxui::Elements rows;
    rows.push_back(ftxui::hbox({
        ftxui::text("NOMBRE") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 14),
        ftxui::text("ESTADO") | ftxui::flex,
    }) | ftxui::bold | ftxui::color(ftxui::Color::Cyan));

    for (int i = 0; i < agentSize; ++i) {
        auto row = ftxui::hbox({
            ftxui::text("TODO") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 14),
            ftxui::text("TODO") | ftxui::flex,
        });
        if (i == this->sel_) row = row | ftxui::inverted | ftxui::focus;
        rows.push_back(row);
        }
    return vbox(rows) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex;
}