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
        server/IdsServer.cpp
        server/IdsServer.h
        server/ServerView.cpp
        server/ServerView.h
        agent/ClientAgent.cpp
        agent/ClientAgent.h
        agent/AgentView.cpp
        agent/AgentView.h
        protocol/Message.cpp
        protocol/Message.h
        protocol/MessageBuffer.cpp
        protocol/MessageBuffer.h
        structures/linkedlist/ClientList.cpp
        structures/linkedlist/ClientList.h
        structures/linkedlist/ClientNode.cpp
        structures/linkedlist/ClientNode.h
        structures/linkedlist/NodeData.cpp
        structures/linkedlist/NodeData.h
        structures/queue/PacketNode.cpp
        structures/queue/PacketNode.h
        structures/queue/PacketQueue.cpp
        structures/queue/PacketQueue.h
        structures/queue/PacketData.cpp
        structures/queue/PacketData.h
)

target_include_directories(chive PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(chive PRIVATE
        Qt6::Core
        Qt6::Network
        ftxui::ftxui
)
