# Protocolo de mensajes de cHive

## Formato

```
TIPO|ID_NODO|CPU|RAM|LATENCIA|PAYLOAD|CHECKSUM\n
```

- Siempre 7 campos separados por `|`, sin espacios. Los que no aplican van en `0` o `-`.
- Cada mensaje termina en `\n` y no puede superar 512 bytes.

## Campos

| Campo | Regla | Ejemplo |
|---|---|---|
| `TIPO` | `AUTH`, `TEL`, `HB`, `PONG`, `ATK`, `CMD` o `MSG` | `TEL` |
| `ID_NODO` | 1–32 caracteres: letras, números y `-` | `agente-01` |
| `CPU` | entero 0–100 (%) | `45` |
| `RAM` | entero 0–100 (%) | `62` |
| `LATENCIA` | entero ≥ 0 (ms) | `12` |
| `PAYLOAD` | texto sin `\|` ni `\n`; `-` si va vacío | `CUARENTENA` |
| `CHECKSUM` | entero 0–255 | `58` |

En los mensajes del servidor, `ID_NODO` es el agente destino.

## Tipos

| Tipo | Dirección | Para qué | PAYLOAD |
|---|---|---|---|
| `AUTH` | agente → servidor | Registro al conectarse | `hostname:clave` |
| `AUTH` | servidor → agente | Respuesta al registro | `OK` o `FAIL` |
| `TEL` | agente → servidor | Telemetría periódica (CPU, RAM, LATENCIA reales) | `-` |
| `HB` | servidor → agente | Heartbeat cada 2 s | marca de tiempo en ms |
| `PONG` | agente → servidor | Respuesta inmediata al `HB` | la misma marca de tiempo |
| `ATK` | agente → servidor | Ataque simulado | `PORTSCAN`, `BRUTEFORCE` o `FLOOD` |
| `CMD` | servidor → agente | Orden remota | `CUARENTENA`, `BLOQUEAR`, `LIMPIAR_ALERTAS` o `LIBERAR` |
| `MSG` | ambos | Texto libre (prueba del cifrado) | el texto |

- **Latencia:** el servidor la calcula al recibir el `PONG` (`ahora - marca`). Como compara con su propio reloj, no hace falta que los relojes de las máquinas estén sincronizados.
- **Desconexión:** si un agente pasa más de 6 s sin responder al `HB`, el servidor lo marca como desconectado.
- **Fuerza bruta:** los `AUTH` fallidos repetidos sirven para detectar fuerza bruta.

## Checksum

Es el XOR de todos los bytes anteriores al último `|`, en decimal.

```
TEL|agente-01|45|62|12|-|58
└──── XOR de esto = 58 ───┘
```

Detecta mensajes mal armados, campos cortados o un descifrado incorrecto. No es seguridad: dos errores en el mismo bit se cancelan.

## Delimitador

El receptor acumula bytes en `MessageBuffer` y corta una línea en cada `\n`. Así resuelve los mensajes partidos y los mensajes pegados de TCP. Si el buffer pasa de 512 bytes sin un `\n`, se descarta para que un cliente malicioso no agote la memoria.

## Validación

`Message::parse()` se detiene en el primer error:

1. La línea no está vacía.
2. Tiene exactamente 7 campos.
3. `TIPO` es conocido.
4. `ID_NODO` es válido.
5. `CPU`, `RAM`, `LATENCIA` y `CHECKSUM` son números en rango.
6. El checksum coincide.

Un mensaje inválido se descarta y se registra en la bitácora, pero la conexión sigue abierta.

## Cifrado (nivel 3)

```
enviar:  serializar → quitar \n → XOR con la clave → Base64 → agregar \n
recibir: cortar en \n → Base64 → XOR con la clave → parse()
```

El Base64 es necesario porque el XOR puede producir un `\n` o un `|`, y eso rompería el formato. Si la clave es incorrecta, el checksum falla.

## Ejemplos

```
AUTH|agente-01|0|0|0|mac-lab3:clave123|29
AUTH|agente-01|0|0|0|OK|112
TEL|agente-01|45|62|12|-|58
HB|agente-01|0|0|0|1732201000123|66
PONG|agente-01|0|0|0|1732201000123|94
ATK|agente-01|0|0|0|PORTSCAN|36
CMD|agente-01|0|0|0|CUARENTENA|38
MSG|agente-01|0|0|0|hola servidor|13
```
