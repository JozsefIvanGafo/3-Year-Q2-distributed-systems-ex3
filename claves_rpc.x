struct Coord {
   int x ;
   int y ;
} ;

struct ret_get_value{
   int status;
   string value1<256>;
    int N_value2;
   double V_value2<32>;
   struct Coord value3;
}
struct arg_send_values{
   
   string value1<256>;
    int N_value2;
   double V_value2<32>;
   struct Coord value3;
}

program CLAVESRPC{

   version CLAVESRPC{
      int destroy(void)=1;
      // si es una string se pone string var<tamaño>, si no se sabe entonces se pone var<>
      //double *V_value2 ->  double V_value2[32] (es un array), pero mejor poner <> significando que 
      //es un array de tamaño variable ahsta un maximo de 32 elementos
      //mirar los tipos de datos en el rpcgen en las transparencias
      int create(void)=0;

      int set_value(int key,struct arg_send_values a1)=2;

      //se modifica por eso usamos un *, y no tiene sentido enviar direccion, es decir no se puede pasar parametros 
      //por referencia, solo se puede pasar por valor
      struct ret_get_value get_value( int key )=3;

      int modify_value(int key, struct arg_send_values a2)=4;

      int delete_key(int key)=5;

      int exist(int key)=6;
   }=1;
}=100456709;