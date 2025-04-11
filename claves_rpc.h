/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CLAVES_RPC_H_RPCGEN
#define _CLAVES_RPC_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct Coord {
	int x;
	int y;
};
typedef struct Coord Coord;

struct ret_get_value {
	int status;
	char *value1;
	int N_value2;
	struct {
		u_int V_value2_len;
		double *V_value2_val;
	} V_value2;
	struct Coord value3;
};
typedef struct ret_get_value ret_get_value;

struct arg_send_values {
	int key;
	char *value1;
	int N_value2;
	struct {
		u_int V_value2_len;
		double *V_value2_val;
	} V_value2;
	struct Coord value3;
};
typedef struct arg_send_values arg_send_values;

#define CLAVESRPC 100456709
#define CLAVESRPC 1

#if defined(__STDC__) || defined(__cplusplus)
#define destroy 1
extern  enum clnt_stat destroy_1(int *, CLIENT *);
extern  bool_t destroy_1_svc(int *, struct svc_req *);
#define create 0
extern  enum clnt_stat create_1(int *, CLIENT *);
extern  bool_t create_1_svc(int *, struct svc_req *);
#define set_value 2
extern  enum clnt_stat set_value_1(struct arg_send_values , int *, CLIENT *);
extern  bool_t set_value_1_svc(struct arg_send_values , int *, struct svc_req *);
#define get_value 3
extern  enum clnt_stat get_value_1(int , struct ret_get_value *, CLIENT *);
extern  bool_t get_value_1_svc(int , struct ret_get_value *, struct svc_req *);
#define modify_value 4
extern  enum clnt_stat modify_value_1(struct arg_send_values , int *, CLIENT *);
extern  bool_t modify_value_1_svc(struct arg_send_values , int *, struct svc_req *);
#define delete_key 5
extern  enum clnt_stat delete_key_1(int , int *, CLIENT *);
extern  bool_t delete_key_1_svc(int , int *, struct svc_req *);
#define exist 6
extern  enum clnt_stat exist_1(int , int *, CLIENT *);
extern  bool_t exist_1_svc(int , int *, struct svc_req *);
extern int clavesrpc_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define destroy 1
extern  enum clnt_stat destroy_1();
extern  bool_t destroy_1_svc();
#define create 0
extern  enum clnt_stat create_1();
extern  bool_t create_1_svc();
#define set_value 2
extern  enum clnt_stat set_value_1();
extern  bool_t set_value_1_svc();
#define get_value 3
extern  enum clnt_stat get_value_1();
extern  bool_t get_value_1_svc();
#define modify_value 4
extern  enum clnt_stat modify_value_1();
extern  bool_t modify_value_1_svc();
#define delete_key 5
extern  enum clnt_stat delete_key_1();
extern  bool_t delete_key_1_svc();
#define exist 6
extern  enum clnt_stat exist_1();
extern  bool_t exist_1_svc();
extern int clavesrpc_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_Coord (XDR *, Coord*);
extern  bool_t xdr_ret_get_value (XDR *, ret_get_value*);
extern  bool_t xdr_arg_send_values (XDR *, arg_send_values*);

#else /* K&R C */
extern bool_t xdr_Coord ();
extern bool_t xdr_ret_get_value ();
extern bool_t xdr_arg_send_values ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CLAVES_RPC_H_RPCGEN */
