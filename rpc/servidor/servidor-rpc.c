/*
 * Este archivo fue generado por rpcgen y fue modificado para adaptarlo a la
 * aplicacion.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "claves_rpc.h"
 #include "claves.h" 

bool_t
destroy_rpc_1_svc(int *result, struct svc_req *rqstp)
{
	

	#ifdef DEBUG
		printf("Servidor: Ha recibido la llamada a destroy()\n");
	#endif
	// destruimos la tupla
	//y se guarda el resultado en result

	* result=destroy();

	// retornamos verdadero porque se ha ejecutado correctamente
	return TRUE;
}

bool_t
set_value_rpc_1_svc(struct arg_send_values a1, int *result,  struct svc_req *rqstp)
{
	#ifdef DEBUG
		printf("Servidor: Ha recibido la llamada a set_value()\n");
	#endif

	// definimos variables auxiliares
	double V_value2[33];

	//verificamos limite del vector
	if (a1.N_value2 < 1 || a1.N_value2 > 32){
		*result=-1;
		// no puede ser falso porque si no, no envia respuesta al cliente que ha fallado
		return TRUE;
	}

	// Guardamos los resultados del vector recibido por el rpc 
	// a la variable local

	for (int i=0; i < a1.N_value2; i++){
		V_value2[i]=a1.V_value2.V_value2_val[i];
	}
	// convertir la estructura de coordenadas
	struct Coord local_coord;
	local_coord.x = a1.value3.x;	
	local_coord.y = a1.value3.y; 


	* result = set_value(a1.key, a1.value1, a1.N_value2, V_value2, local_coord);
	// retornamos verdadero porque se ha ejecutado correctamente
	return TRUE;


}

bool_t
get_value_rpc_1_svc(int key, struct ret_get_value *result,  struct svc_req *rqstp)
{

	#ifdef DEBUG
		printf("Servidor: Ha recibido la llamada a get_value()\n");
	#endif
	
	//definimos variables auxiliares
	//inicializamos todos sus valores a 0
	// tenemos 257 posiciones para la cadena de caracteres
	// 255 son caracteres + 1 para el byte 0 + 1 para el byte guardian
	char value1[257] = {0}; //inicializarla en 0
	int N_value2 = 0;
	double V_value2[33]={0};
	struct Coord value3 = {0 , 0};
	int status;//estado de la operacion get value

	//Como la funcion get_value retorna una estructura
	//definimos el resultado como una estructura
	memset(result, 0, sizeof(struct ret_get_value));


	//
	struct Coord local_coord;

	//llamamos a la funcion get_value
	status = get_value(key, value1, &N_value2, V_value2, &local_coord);

	//guardamos el resultado en la estructura
	result->status = status;

	//si la operacion es exitosa
	if (status == 0){
		result->value1=strdup(value1);
		if (result->value1 == NULL) {
			// Manejo de error al duplicar la cadena
			result->status = -1; // Error
			// no puede ser falso porque si no no envia respuesta al cliente que ha fallado
			return TRUE;
		}

		//guardar tamaño del vector
		result->N_value2 = N_value2;

		//asignar memoria dinamica al vector
		result-> V_value2.V_value2_len = N_value2;
		result->V_value2.V_value2_val = ( double *) malloc(N_value2 * sizeof(double));

		//verificamos que se ha guardado correctamente
		if (result->V_value2.V_value2_val == NULL) {
			// Manejo de error al asignar memoria
			free(result->value1); // Liberar la cadena duplicada
			result->status = -1; // Error
			// no puede ser falso porque si no no envia respuesta al cliente que ha fallado
			return TRUE;
		}

		//guardamos el vector en la estructura
		for (int i = 0; i < N_value2; i++){
			result->V_value2.V_value2_val[i] = V_value2[i];
		}
		//guardamos la coordenada en la estructura
		result->value3.x = local_coord.x;
		result->value3.y = local_coord.y;

	}
	// la operacion no fue exitosa status != 0
	else{
		result->value1 = strdup(""); // Cadena vacía pero válida
        result->N_value2 = 0;
        result->V_value2.V_value2_val = NULL;
        result->V_value2.V_value2_len = 0;

		
	}

	return TRUE;

}

bool_t
modify_value_rpc_1_svc(struct arg_send_values a2, int *result,  struct svc_req *rqstp)
{
	#ifdef DEBUG
		printf("Servidor: Ha recibido la llamada a modify_value()\n");
	#endif

	double V_value2[33];
	//verificamos limite del vector
	if (a2.N_value2 < 1 || a2.N_value2 > 32){
		*result=-1;
		// no puede ser falso porque si no, no envia respuesta al cliente que ha fallado
		return TRUE;
	}

	// Guardamos los resultados del vector recibido por el rpc
	// a la variable local
	for (int i=0; i < a2.N_value2; i++){
		V_value2[i]=a2.V_value2.V_value2_val[i];
	}

	struct Coord local_coord;
	local_coord.x = a2.value3.x;
	local_coord.y = a2.value3.y;
	//llamamos a la funcion modify_value
	* result = modify_value(a2.key, a2.value1, a2.N_value2, V_value2, local_coord);

	return TRUE;
}

bool_t
delete_key_rpc_1_svc(int key, int *result,  struct svc_req *rqstp)
{
	#ifdef DEBUG
		printf("Servidor: Ha recibido la llamada a delete_key()\n");
	#endif
	//llamamos a la funcion delete_key

	* result = delete_key(key);

	return TRUE;
}

bool_t
exist_rpc_1_svc(int key, int *result,  struct svc_req *rqstp)
{

	#ifdef DEBUG
		printf("Servidor: Ha recibido la llamada a exist()\n");
	#endif

	//llamamos a la funcion exist
	* result = exist(key);

	return TRUE;
}

int
clavesrpc_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
