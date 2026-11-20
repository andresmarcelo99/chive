cmake_minimum_required(VERSION 4.3)
project(chive)

set(CMAKE_CXX_STANDARD 20)

add_library(comun comun/comun.cpp comun/comun.h)
target_include_directories(comun PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(servidor
        servidor/main.cpp
        servidor/servidor.cpp
        servidor/servidor.h
)
target_link_libraries(servidor PRIVATE comun)

add_executable(agente
        agente/main.cpp
        agente/agente.cpp
        agente/agente.h
)
target_link_libraries(agente PRIVATE comun)

add_executable(chive main.cpp
        servidor/servidor.cpp
        agente/agente.cpp
)
target_link_libraries(chive PRIVATE comun)
