#include <cstdio>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "agente.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"


int agent() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }
    char buffer[128]{};
    read(sock, buffer, sizeof(buffer));
    std::cout << "Received: " << buffer;
    close(sock);

    return 0;
}

