#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <ftxui/ftxui.hpp>

#include "agent/AgentView.h"
#include "agent/ClientAgent.h"
#include "server/ServerView.h"

#include <QByteArray>
#include <QDebug>

#include "protocol/Message.h"


std::string chooseMode();

int ui(int argc, char* argsv[]);

int main(int argc, char* argsv[]) {

    const char *chunks[] = { "WX|lima|2", "2|183\nWX|cusco|8|1", "60\n" };

    Message m(Message::MsgType::TEL, "agente_01", 45,62,12,"-");
    QString s = m.serialize();
    qDebug() << "serializando:" << s;

    Message back;
    QString err;

    bool ok = Message::parse(s.chopped(1), back, err);
    qDebug() << "parse ok?" << ok << err;
    qDebug() << back.getIdNode() << back.getCpu() << back.getRam()
             << back.getLatency() << back.getPayload();
    return 0;
}

// Pantalla inicial: elegir Servidor o Agente con las flechas y Enter
std::string chooseMode() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    std::vector<std::string> options = {"Servidor", "Agente"};
    int selected = 0;
    bool chosen = false;

    ftxui::MenuOption opt;
    opt.on_enter = [&] {
        chosen = true;
        screen.Exit();
    };
    auto menu = ftxui::Menu(&options, &selected, opt);

    auto view = ftxui::Renderer(menu, [&] {
        return ftxui::vbox({
            ftxui::text("cHive: elige un modo") | ftxui::bold,
            ftxui::separator(),
            menu->Render(),
            ftxui::separator(),
            ftxui::text("↑↓ mover   Enter elegir   q salir") | ftxui::dim,
        }) | ftxui::border | ftxui::center;
    });

    view |= ftxui::CatchEvent([&](ftxui::Event e) {
        if (e == ftxui::Event::Character('q') || e == ftxui::Event::Escape) {
            screen.Exit();
            return true;
        }
        return false;
    });

    screen.Loop(view);
    return chosen ? options[selected] : "";
}

int ui(int argc, char *argsv[]) {
    QCoreApplication app(argc, argsv);

    QCoreApplication::setApplicationName("cHive");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Cli de  Telemetria");
    parser.addHelpOption();      // -h, --help
    parser.addVersionOption();   // -v, --version

    QCommandLineOption serverOpt({"S", "server"}, "Abre vista de servidor");
    QCommandLineOption agentOpt({"A", "agent"}, "Abre vista de agente");
    parser.addOption(serverOpt);
    parser.addOption(agentOpt);
    parser.process(app);

    if (parser.isSet(serverOpt) && parser.isSet(agentOpt)) {
        std::cerr << "Elige solo uno: --server o --agent\n";
        return 1;
    }

    bool sfl = parser.isSet(serverOpt);
    bool afl = parser.isSet(agentOpt);
    std::string mode;
    if (afl) {
        mode = "Agente";
    }else if (sfl) {
        mode = "Servidor";
    } else {
        // Sin argumentos: preguntar el modo con FTXUI
        mode = chooseMode();
        if (mode.empty()) return 0;   // el usuario salió sin elegir
    }

    if (mode == "Servidor"){
        IdsServer ids;
        ServerView view(ids);
        return view.runServer();
    }else if (mode == "Agente") {
        ClientAgent ca;
        AgentView view(ca);
        return view.runAgentClient();
    }
}

