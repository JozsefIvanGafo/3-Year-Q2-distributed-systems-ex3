# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -D_GNU_SOURCE
#CFLAGS = -Wall -Wextra -std=c11 -O2 -D_GNU_SOURCE -DDEBUG
# Add TI-RPC flags
CFLAGS += -g -I/usr/include/tirpc
#Library flags
LDFLAGS = -pthread
LDLIBS += -lnsl -lpthread -ldl -ltirpc

# Archivos fuente RPC
# Remove claves.c from proxy sources to avoid duplicate symbols
SRCS_PROXY = rpc/proxy/proxy-rpc.c rpc/claves_rpc_clnt.c rpc/claves_rpc_xdr.c
SRCS_SERVER = rpc/servidor/servidor-rpc.c claves/claves.c rpc/claves_rpc_svc.c rpc/claves_rpc_xdr.c
# Archivos fuente del cliente
CLIENT_SRCS = $(wildcard app-cliente/*.c)
CLIENT_EXECS = $(patsubst app-cliente/%.c, %, $(CLIENT_SRCS))

# Objetos generados
LIBRARY = libclaves.so
SERVER = servidor-rpc

all: $(LIBRARY) $(SERVER) $(CLIENT_EXECS)

# Compilar la biblioteca compartida con proxy-rpc.c
$(LIBRARY): $(SRCS_PROXY)
	$(CC) $(CFLAGS) -fPIC -shared -o $(LIBRARY) $(SRCS_PROXY) -I./include -I./rpc -I./claves -Wl,--export-dynamic $(LDFLAGS) $(LDLIBS)

# Compilar el servidor con claves.c
$(SERVER): $(SRCS_SERVER)
	$(CC) $(CFLAGS) -o $(SERVER) $(SRCS_SERVER) -I./include -I./rpc -I./claves -I./servidor/include $(LDFLAGS) $(LDLIBS)

# Regla para compilar cada cliente individualmente
%: app-cliente/%.c $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $< -L. -lclaves -I./include -I./rpc -I./claves -Wl,-rpath,. $(LDLIBS)

# Limpiar archivos compilados
clean:
	rm -f $(LIBRARY) $(SERVER) $(CLIENT_EXECS)