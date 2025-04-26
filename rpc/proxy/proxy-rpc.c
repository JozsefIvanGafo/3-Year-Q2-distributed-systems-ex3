/*
 * Este archivo no fue generado por rpcgen,
 * Hemos creado el poxy para usar rpc y actuar como proxy al cliente
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <rpc/rpc.h>
 #include "claves_rpc.h"
 #include "claves.h"


// Cliente RPC global
static CLIENT *clnt;

/**						 Inicializa el cliente RPC.
 * 
 * @return 0 si la inicialización fue exitosa, -1 en caso de error.
 * 
 * @note Esta función debe ser llamada antes de usar cualquier otra función RPC.
 *      
*/
static int init_rpc_client(){
	//si ya esta inicializado no lo inicializamos de nuevo
	if (clnt != NULL) {
		return 0;
	}
	//obtenemos la ip del servidor
	//usando las variables de entorno
	char *server_ip = getenv("IP_TUPLAS");


	if (server_ip == NULL) {
		#ifdef DEBUG
			fprintf(stderr, "Error: IP_TUPLAS no está definida\n");
		#endif
		return -1;
	}
	
	// creamos el cliente rpc y usando el protocolo tcp
	clnt = clnt_create(server_ip,CLAVESRPC,CLAVESRPC_VERSION,"tcp");

	// verificamos si se ha creado correctamente
	if (clnt == NULL) {
		#ifdef DEBUG
			fprintf(stderr, "Error: No se pudo crear el cliente RPC\n");
		#endif
		clnt_pcreateerror(server_ip);
		return -1;
	}

	return 0;

}

/*
 * Implementacion de la funcion destroy de claves.h
*/
int destroy(void) {
	int result;
	// Inicializamos el cliente RPC
	if (init_rpc_client() != 0) {
		return -1;
	}

	// Llamamos a la función destroy_rpc_1
	if (destroy_rpc_1(&result, clnt) != RPC_SUCCESS) {
		clnt_perror(clnt, "Error en destroy_rpc_1");
		return -1;
	}
	return result;

}
/*
 * Implementacion de la funcion set_value de claves.h
*/
int set_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {

	//declaramos las variables locales
	int result;
	struct arg_send_values args;

	// Validamos los aprametros
	if (key < 0 || N_value2 < 1 || N_value2 > 32 || strlen(value1) > 255) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: Clave o tamaño de vector inválido\n");
		#endif
		return -1; 
	}
	if ( value1== NULL || V_value2 == NULL) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: Punteros nulos\n");
		#endif
		return -1; 
	}

	// Inicializamos el cliente RPC
	if (init_rpc_client() != 0) {
		return -1;
	}


	//Preparamos los argumentos para la llamada RPC
	args.key = key;
	args.value1 = strdup(value1);
	args.N_value2 = N_value2;

	//asignamos memoria para el vector y copiarlo
	args.V_value2.V_value2_val = (double *)malloc(N_value2 * sizeof(double));
	if (args.V_value2.V_value2_val == NULL) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: No se pudo asignar memoria para el vector\n");
		#endif
		free(args.value1);
		return -1;
	}
	args.V_value2.V_value2_len = N_value2;
	// copiamos el vector a la estructura
	memcpy(args.V_value2.V_value2_val, V_value2, N_value2 * sizeof(double));

	//copiamos la estructura de coordenadas
	args.value3.x = value3.x;
	args.value3.y = value3.y;

	//lamamos a la funcion rpc
	if (set_value_rpc_1(args, &result, clnt) != RPC_SUCCESS) {
		clnt_perror(clnt, "Error en set_value_rpc_1");
		free(args.value1);
		free(args.V_value2.V_value2_val);
		return -1;
	}

	//liberamos la memoria
	free(args.value1);
	free(args.V_value2.V_value2_val);

	return result;
}

/*
 * Implementación de la función get_value de claves.h
 */
int get_value(int key, char *value1, int *N_value2, double *V_value2, struct Coord *value3) {

	//declaramos las variables locales
	struct ret_get_value  result;

	// Validamos los aprametros
	if (value1 == NULL || N_value2 == NULL ||V_value2 == NULL ||value3 == NULL ||key < 0) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: Clave o punteros inválidos\n");
		#endif
		return -1; 
	}

	// Inicializamos el cliente RPC
	if (init_rpc_client() != 0) {
		return -1;
	}

	//inicializar la estructura de resultado
	memset(&result, 0, sizeof(struct ret_get_value));
	//llamamos a la funcion rpc
	if (get_value_rpc_1(key, &result, clnt) != RPC_SUCCESS) {
		clnt_perror(clnt, "Error en get_value_rpc_1");
		return -1;
	}

	//verificamos el status
	if (result.status != 0) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: No se pudo obtener el valor\n");
		#endif
		// Liberar memoria asignada por el cliente RPC
		//por si a caso no se llega a guardar algo
        if (result.value1) free(result.value1);
        if (result.V_value2.V_value2_val) free(result.V_value2.V_value2_val);
		
		return -1;
	}

	//copiar los resultados en el buffer del cliente
	if (result.value1){
		strncpy(value1, result.value1, 255);
		value1[255] = '\0'; // Asegurar terminación de la cadena
		free(result.value1);
	}else{
		value1[0] = '\0';
	}

	//actualizar N_value2 con el valor devuelto
	*N_value2 = result.N_value2;
	//copiar el vector de dobles
	if (result.V_value2.V_value2_val && result.N_value2 > 0) {
		//lo copiamos al buffer del cliente
        for (int i = 0; i < result.N_value2 && i < 32; i++) {
            V_value2[i] = result.V_value2.V_value2_val[i];
        }
        free(result.V_value2.V_value2_val);
    }
	value3->x = result.value3.x;
	value3->y = result.value3.y;
	

	return 0;

}


/*
 * Implementación de la función modify_value de claves.h
 */
int modify_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {

	//declaramos las variables locales
	int result;
	struct arg_send_values args;

	if ( value1== NULL || V_value2 == NULL) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: Punteros nulos\n");
		#endif
		return -1; 
	}
	// Validamos los aprametros
	if (key < 0 || N_value2 < 1 || N_value2 > 32 || strlen(value1) > 255) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: Clave o tamaño de vector inválido\n");
		#endif
		return -1; 
	}

	// Inicializamos el cliente RPC
	if (init_rpc_client() != 0) {
		return -1;
	}

	//preparamos los argumentos para la llamada RPC
	args.key = key;
	args.value1 = strdup(value1);
	args.N_value2 = N_value2;

	//asignamos memoria para el vector y copiarlo
	args.V_value2.V_value2_val = (double *)malloc(N_value2 * sizeof(double));
	if (args.V_value2.V_value2_val == NULL) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: No se pudo asignar memoria para el vector\n");
		#endif
		free(args.value1);
		return -1;
	}
	args.V_value2.V_value2_len = N_value2;
	// copiamos el vector a la estructura
	memcpy(args.V_value2.V_value2_val, V_value2, N_value2 * sizeof(double));
	//copiamos la estructura de coordenadas
	args.value3.x = value3.x;
	args.value3.y = value3.y;
	//lamamos a la funcion rpc
	if (modify_value_rpc_1(args, &result, clnt) != RPC_SUCCESS) {
		clnt_perror(clnt, "Error en modify_value_rpc_1");
		free(args.value1);
		free(args.V_value2.V_value2_val);
		return -1;
	}
	//liberamos la memoria
	free(args.value1);
	free(args.V_value2.V_value2_val);
	return result;
}

/*
 * Implementación de la función delete_key de claves.h
 */
int delete_key(int key) {
	//declaramos las variables locales
	int result;

	// Validamos los aprametros
	if (key < 0) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: Clave inválida\n");
		#endif
		return -1; 
	}

	// Inicializamos el cliente RPC
	if (init_rpc_client() != 0) {
		return -1;
	}

	//lamamos a la funcion rpc
	if (delete_key_rpc_1(key, &result, clnt) != RPC_SUCCESS) {
		clnt_perror(clnt, "Error en delete_key_rpc_1");
		return -1;
	}
	return result;
}
/*
 * Implementación de la función exist de claves.h
 */
int exist(int key) {
	//declaramos las variables locales
	int result;

	// Validamos los aprametros
	if (key < 0) {
		#ifdef DEBUG
			fprintf(stderr, "[Error]: Clave inválida\n");
		#endif
		return -1; 
	}

	// Inicializamos el cliente RPC
	if (init_rpc_client() != 0) {
		return -1;
	}

	//lamamos a la funcion rpc
	if (exist_rpc_1(key, &result, clnt) != RPC_SUCCESS) {
		clnt_perror(clnt, "Error en exist_rpc_1");
		return -1;
	}
	return result;
}
