#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <ftxui/ftxui.hpp>
#include "agente/agente.h"
#include "servidor/servidor.h"

void pantalla(const std::string &modo);
std::string elegirModo();

int main(int argc, char* argsv[]) {
    QCoreApplication app(argc, argsv);

    QCoreApplication::setApplicationName("cHive");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Cli de  Telemetria");
    parser.addHelpOption();      // -h, --help
    parser.addVersionOption();   // -v, --version

    QCommandLineOption servidor({"S", "server"}, "Abre vista de servidor");
    QCommandLineOption agente({"A", "agent"}, "Abre vista de agente");
    parser.addOption(servidor);
    parser.addOption(agente);
    parser.process(app);

    if (parser.isSet(servidor) && parser.isSet(agente)) {
        std::cerr << "Elige solo uno: --server o --agent\n";
        return 1;
    }

    bool sfl = parser.isSet(servidor);
    bool afl = parser.isSet(agente);
    std::string modo;
    if (afl) {
        modo = "Agente";
    }else if (sfl) {
        modo = "Servidor";
    } else {
        // Sin argumentos: preguntar el modo con FTXUI
        modo = elegirModo();
        if (modo.empty()) return 0;   // el usuario salió sin elegir
    }

    pantalla(modo);

    return 0;
}

// Pantalla inicial: elegir Servidor o Agente con las flechas y Enter
std::string elegirModo() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    std::vector<std::string> opciones = {"Servidor", "Agente"};
    int seleccion = 0;
    bool elegido = false;

    ftxui::MenuOption opt;
    opt.on_enter = [&] {
        elegido = true;
        screen.Exit();
    };
    auto menu = ftxui::Menu(&opciones, &seleccion, opt);

    auto vista = ftxui::Renderer(menu, [&] {
        return ftxui::vbox({
            ftxui::text("cHive: elige un modo") | ftxui::bold,
            ftxui::separator(),
            menu->Render(),
            ftxui::separator(),
            ftxui::text("↑↓ mover   Enter elegir   q salir") | ftxui::dim,
        }) | ftxui::border | ftxui::center;
    });

    vista |= ftxui::CatchEvent([&](ftxui::Event e) {
        if (e == ftxui::Event::Character('q') || e == ftxui::Event::Escape) {
            screen.Exit();
            return true;
        }
        return false;
    });

    screen.Loop(vista);
    return elegido ? opciones[seleccion] : "";
}

std::string mockAgenteNombre(int i) {
    return "agente " + std::to_string(i);
}
std::string mockAgenteEstado(int i) {
    return "estado " + std::to_string(i);
}

void pantalla(const std::string &modo) {
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    int mockAgentsSize = 3;

    // Header de la vista
    auto header = [&] {
        return ftxui::hbox({
                   ftxui::vbox({
                       ftxui::text("Servidor: 0.0.0.0:8080"),
                       ftxui::text("Agentes:  " + std::to_string(mockAgentsSize)),
                   }),
                   ftxui::filler(),
                   ftxui::vbox({
                       ftxui::text("<:> comando   </> filtrar") | ftxui::dim,
                       ftxui::text("<j/k> mover   <d> borrar   <q> salir") | ftxui::dim,
                   }),
               }) | ftxui::border;
    };

    // Contenedor principal de informacion
    int sel = 0;

    auto tabla = ftxui::Renderer([&] {
        ftxui::Elements filas;
        filas.push_back(ftxui::hbox({
                            ftxui::text("NOMBRE") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 14),
                            ftxui::text("ESTADO") | ftxui::flex,
                        }) | ftxui::bold | ftxui::color(ftxui::Color::Cyan));

        for (int i = 0; i < mockAgentsSize; ++i) {
            auto fila = ftxui::hbox({
                ftxui::text(mockAgenteNombre(i)) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 14),
                ftxui::text(mockAgenteEstado(i)) | ftxui::flex,
            });
            if (i == sel) fila = fila | ftxui::inverted | ftxui::focus;
            filas.push_back(fila);
        }
        return vbox(filas) | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex;
    });

    //Caja de input para comandos y navegacion
    std::string comando, filtro;
    bool modo_cmd = false, modo_filtro = false;

    ftxui::InputOption opt;
    opt.multiline = false;
    opt.on_enter = [&] {
        if (comando == "q") screen.Exit();
        // if (comando == "alertas") vista = 1;
        comando.clear();
        modo_cmd = false;
    };
    auto input_cmd = Input(&comando, "agentes | alertas | q", opt);
    

    auto vista = ftxui::Renderer([&] {
        return ftxui::vbox({
            header() ,
            ftxui::hbox({
            ftxui::vbox({
                window(ftxui::text(" Mapa de nodos "), tabla->Render()) | ftxui::flex,
                ftxui::window(ftxui::text(" Tráfico "), ftxui::text("TODO")),
            }) | ftxui::flex,
            ftxui::window(ftxui::text(" Alertas críticas "), ftxui::text("TODO")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30),
        }) | ftxui::flex,
        ftxui::window(ftxui::text(" Consola de tramas "), ftxui::text("TODO")) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 8),
        ftxui::text(" ↑↓ navegar   b bloquear   c limpiar   ? ayuda   q salir") | ftxui::dim,
        }) | ftxui::border;
    });

    vista |= ftxui::CatchEvent([&](ftxui::Event e) {
        if (e == ftxui::Event::Character('q')) {
            screen.Exit();
            return true;
        }
        return false;
    });
    screen.Loop(vista);
}