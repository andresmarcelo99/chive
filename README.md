# cHive

Un IDS (sistema de detección de intrusos) para la terminal. Es un solo programa con dos modos:

- **Servidor**: un dashboard estilo k9s que muestra los agentes conectados, alertas y tráfico.
- **Agente**: corre en cada máquina y le manda telemetría al servidor.

Hecho en C++20 con Qt6 (Core, Network) y FTXUI.

## Requisitos

- CMake
- Un compilador con soporte para C++20
- Qt6: en macOS, `brew install qt`
- FTXUI se descarga solo al compilar (FetchContent)

## Compilar

```bash
cmake -S . -B build
cmake --build build
```

O abrir la carpeta en CLion y darle a Build.

## Ejecutar

```bash
./build/chive --server   # o -S, modo servidor
./build/chive --agent    # o -A, modo agente
./build/chive            # sin flags: te pregunta el modo
./build/chive --help
```

`q` para salir.

## Estructura

```
main.cpp                lee los flags y arranca el modo elegido
server/                 IdsServer (lógica) + ServerView (pantalla)
agent/                  ClientAgent (lógica) + AgentView (pantalla)
protocol/               Message (parser y serializer) + MessageBuffer (corta el stream TCP en líneas)
structures/linkedlist/  ClientList: lista enlazada de clientes conectados
structures/queue/       PacketQueue: cola FIFO de tramas recibidas
structures/stack/       AlertStack: pila LIFO de alertas
docs/protocol.md        formato de las tramas, checksum y validación
```

Cada modo tiene una clase de lógica (sin FTXUI) y una clase de vista que solo dibuja y lee teclas.

Las estructuras están hechas a mano con punteros (sin `std::` ni contenedores de Qt). Cada una separa los datos (`NodeData`, `PacketData`, `AlertData`) del nodo que los enlaza.

## Estado

- Listo: protocolo de tramas, ClientList, PacketQueue.
- En progreso: AlertStack.
- Pendiente: TelemetryMatrix, servidor TCP con hilos, agente, heartbeat y el resto de issues.

Por ahora el dashboard del servidor usa datos de prueba.

## Clases planeadas

IdsServer, ClientList, PacketQueue, AlertStack, TelemetryMatrix, Message, MessageBuffer, Cipher, Logger, ClientAgent, SocketWorker
