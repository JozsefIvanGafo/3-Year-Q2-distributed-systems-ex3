struct rpc_Coord {
   int x ;
   int y ;
} ;

struct ret_get_value{
   int status;
   string value1<256>;
    int N_value2;
   double V_value2<32>;
   struct rpc_Coord value3;
};
struct arg_send_values{
   int key;
   string value1<256>;
    int N_value2;
   double V_value2<32>;
   struct rpc_Coord value3;
};

program CLAVESRPC{

   version CLAVESRPC_VERSION{

      int destroy_rpc()=1;

      int set_value_rpc(struct arg_send_values a1)=2;

      struct ret_get_value get_value_rpc( int key )=3;

      int modify_value_rpc(struct arg_send_values a2)=4;

      int delete_key_rpc(int key)=5;

      int exist_rpc(int key)=6;

   }=1;

}=100456709;