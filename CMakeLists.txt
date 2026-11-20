cmake_minimum_required(VERSION 4.3)
project(chive LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 (Homebrew). qt_standard_project_setup() activa CMAKE_AUTOMOC.
list(APPEND CMAKE_PREFIX_PATH /opt/homebrew/opt/qt)
find_package(Qt6 REQUIRED COMPONENTS Core Network)
qt_standard_project_setup()

# FTXUI
include(FetchContent)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v7.0.3
)
FetchContent_MakeAvailable(ftxui)

# Un solo ejecutable: chive --server | chive --agent
qt_add_executable(chive
        main.cpp
        servidor/servidor.cpp
        servidor/servidor.h
        agente/agente.cpp
        agente/agente.h
        comun/comun.cpp
        comun/comun.h
)

target_include_directories(chive PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(chive PRIVATE
        Qt6::Core
        Qt6::Network
        ftxui::ftxui
)
