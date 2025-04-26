# Sistemas Distribuidos - Ejercicio Evaluable 3: RPC

## Índice
1. [Autores](#autores)
2. [Estructura del Proyecto](#estructura-del-proyecto)
3. [Descripción del Proyecto](#descripción-del-proyecto)
4. [Instrucciones de Uso](#instrucciones-de-uso)

## 1. Autores
- JÓZSEF IVÁN GAFO - 100456709@alumnos.uc3m.es

- PABLO MORENO GONZÁLEZ - 100451061@alumnos.uc3m.es

## 2. Estructura del Proyecto
```
/rpc
    claves_rpc.x: Define la interfaz de servicio RPC
    claves_rpc.h: Archivo generado por rpcgen
    claves_rpc_clnt.c: Cliente RPC generado por rpcgen
    claves_rpc_svc.c: Servidor RPC generado por rpcgen
    claves_rpc_xdr.c: Funciones XDR generadas por rpcgen
    /proxy
        proxy-rpc.c: Implementación del proxy para el cliente usando RPC
    /servidor
        servidor-rpc.c: Implementación del servidor RPC

/claves
    claves.h: API del sistema de almacenamiento
    claves.c: Implementación del almacenamiento usando listas enlazadas

/app-cliente
    app-cliente-1.c: Cliente para pruebas básicas de funcionalidad
    app-cliente-2.c: Cliente para pruebas de límites y casos de error
    app-cliente-3.c: Cliente para pruebas de concurrencia y carga

Archivos Raíz
    Makefile: Script de compilación del proyecto
```

## 3. Descripción del Proyecto
Sistema distribuido basado en RPC (Remote Procedure Call) que permite almacenar y gestionar tuplas clave-valor complejas. Cada tupla contiene:

- Una clave entera
- Una cadena de texto (máx. 256 caracteres)
- Un vector de números double (máx. 32 elementos)
- Una estructura de coordenadas 2D

En este ejercicio se ha implementado el servidor y el cliente usando ONC RPC, donde el cliente invoca procedimientos remotos en el servidor para realizar operaciones sobre las tuplas.

## 4. Instrucciones de Uso

### Compilación
```bash
# Compilación estándar
make
```

### Limpiar archivos
```bash
# Limpiar archivos generados
make clean
```

### Ejecución

#### Iniciar servidor
```bash
# Iniciar el servidor RPC
./servidor-rpc
```

#### Definir variables de entorno
```bash
# Definir la dirección IP del servidor RPC
export IP_TUPLAS=localhost
```

#### Ejecutar cliente
```bash
# Iniciar app-cliente-1
./app-cliente-1

# Iniciar app-cliente-2
./app-cliente-2

# Iniciar app-cliente-3
./app-cliente-3
```

#### Alternativa para ejecutar cliente
```bash
# Ejecutar cliente con variable de entorno
env IP_TUPLAS=localhost ./app-cliente-1
```