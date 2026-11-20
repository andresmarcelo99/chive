#include <iostream>

#include "agente/agente.h"
#include "servidor/servidor.h"

int main() {
    agente a;
    a.data = "agente";

    servidor s;
    s.data = "servidor";

    std::cout << a.data << std::endl;
    std::cout << s.data << std::endl;
    return 0;
}
