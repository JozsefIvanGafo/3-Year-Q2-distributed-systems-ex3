/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "claves_rpc.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
destroy_1(int *clnt_res, CLIENT *clnt)
{
	 return (clnt_call (clnt, destroy, (xdrproc_t) xdr_void, (caddr_t) NULL,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));

}

enum clnt_stat 
create_1(int *clnt_res, CLIENT *clnt)
{
	 return (clnt_call (clnt, create, (xdrproc_t) xdr_void, (caddr_t) NULL,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));

}

enum clnt_stat 
set_value_1(struct arg_send_values a1, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, set_value,
		(xdrproc_t) xdr_arg_send_values, (caddr_t) &a1,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
get_value_1(int key, struct ret_get_value *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, get_value,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_ret_get_value, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
modify_value_1(struct arg_send_values a2, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, modify_value,
		(xdrproc_t) xdr_arg_send_values, (caddr_t) &a2,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
delete_key_1(int key, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, delete_key,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
exist_1(int key, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, exist,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}
