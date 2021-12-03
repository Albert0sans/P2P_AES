#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <vector>
using namespace std;

#ifdef WIN32
  #include <winsock.h>         // For socket(), connect(), send(), and recv()
  typedef int socklen_t;
  typedef char raw_type;       // Type used for raw data on this platform
#else
  #include <sys/types.h>       // For data types
  #include <sys/socket.h>      // For socket(), connect(), send(), and recv()
  #include <netdb.h>           // For gethostbyname()
  #include <arpa/inet.h>       // For inet_addr()
  #include <unistd.h>          // For close()
  #include <netinet/in.h>      // For sockaddr_in
  typedef void raw_type;       // Type used for raw data on this platform
#endif

struct node {

    int fd;
    int port;
    string ip;
};

void deserialize(char* serial_data,node &data);
string serialize(vector <node> lista_nodos);
void  add_node(vector<node> &lista_nodos, int fd,int port,string ip) ;
void  del_node(vector<node>& lista_nodos, int port);
void view_nodes(vector < node > lista_nodos);
int makesock(int &sock,struct sockaddr_in &sock_dir, int c,const char * ip,in_port_t port);
int new_connection(int sock,struct sockaddr_in &new_addr);
void handle_select(fd_set &active_fd_set, int sock,vector < node > lista );//funcion que hacer set de los clientes y borra los que tengan fd=-1;
void sendall(vector < node > lista_send,vector < node > lista_data);
char* NameResolution(char* name);
char * getline(void);
void deserialize_all(char* serial_data,vector<node> &data);

