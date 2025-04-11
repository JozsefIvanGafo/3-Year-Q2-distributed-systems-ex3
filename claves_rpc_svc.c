/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "claves_rpc.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

int
_destroy_1 (void  *argp, void *result, struct svc_req *rqstp)
{
	return (destroy_1_svc(result, rqstp));
}

int
_set_value_1 (struct arg_send_values  *argp, void *result, struct svc_req *rqstp)
{
	return (set_value_1_svc(*argp, result, rqstp));
}

int
_get_value_1 (int  *argp, void *result, struct svc_req *rqstp)
{
	return (get_value_1_svc(*argp, result, rqstp));
}

int
_modify_value_1 (struct arg_send_values  *argp, void *result, struct svc_req *rqstp)
{
	return (modify_value_1_svc(*argp, result, rqstp));
}

int
_delete_key_1 (int  *argp, void *result, struct svc_req *rqstp)
{
	return (delete_key_1_svc(*argp, result, rqstp));
}

int
_exist_1 (int  *argp, void *result, struct svc_req *rqstp)
{
	return (exist_1_svc(*argp, result, rqstp));
}

static void
clavesrpc_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		struct arg_send_values set_value_1_arg;
		int get_value_1_arg;
		struct arg_send_values modify_value_1_arg;
		int delete_key_1_arg;
		int exist_1_arg;
	} argument;
	union {
		int destroy_1_res;
		int set_value_1_res;
		struct ret_get_value get_value_1_res;
		int modify_value_1_res;
		int delete_key_1_res;
		int exist_1_res;
	} result;
	bool_t retval;
	xdrproc_t _xdr_argument, _xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case destroy:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_destroy_1;
		break;

	case set_value:
		_xdr_argument = (xdrproc_t) xdr_arg_send_values;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_set_value_1;
		break;

	case get_value:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_ret_get_value;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_get_value_1;
		break;

	case modify_value:
		_xdr_argument = (xdrproc_t) xdr_arg_send_values;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_modify_value_1;
		break;

	case delete_key:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_delete_key_1;
		break;

	case exist:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_exist_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	retval = (bool_t) (*local)((char *)&argument, (void *)&result, rqstp);
	if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)&result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	if (!clavesrpc_1_freeresult (transp, _xdr_result, (caddr_t) &result))
		fprintf (stderr, "%s", "unable to free results");

	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (CLAVESRPC, CLAVESRPC);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, CLAVESRPC, CLAVESRPC, clavesrpc_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (CLAVESRPC, CLAVESRPC, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, CLAVESRPC, CLAVESRPC, clavesrpc_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (CLAVESRPC, CLAVESRPC, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
