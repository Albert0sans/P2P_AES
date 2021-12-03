#include "AES.h"
#include "utils.h"
#include "random_l.h"

#include "sha256.h"
#include <cstring>
#include<ifaddrs.h>

string localip(){

  FILE *f;
    char line[100] , *p , *c;
    
    f = fopen("/proc/net/route" , "r");
    
    while(fgets(line , 100 , f))
    {
		p = strtok(line , " \t");
		c = strtok(NULL , " \t");
		
		if(p!=NULL && c!=NULL)
		{
			if(strcmp(c , "00000000") == 0)
			{
				printf("Default interface is : %s \n" , p);
				break;
			}
		}
	}
    
    //which family do we require , AF_INET or AF_INET6
    int fm = AF_INET;
    struct ifaddrs *ifaddr, *ifa;
	int family , s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) 
	{
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	//Walk through linked list, maintaining head pointer so we can free list later
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
	{
		if (ifa->ifa_addr == NULL)
		{
			continue;
		}

		family = ifa->ifa_addr->sa_family;

		if(strcmp( ifa->ifa_name , p) == 0)
		{
			if (family == fm) 
			{
				s = getnameinfo( ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6) , host , NI_MAXHOST , NULL , 0 , NI_NUMERICHOST);
				
				if (s != 0) 
				{
					printf("getnameinfo() failed: %s\n", gai_strerror(s));
					exit(EXIT_FAILURE);
				}
				
				
			}
			printf("\n");
		}
	}

	freeifaddrs(ifaddr);
	
	return host;

}

int main(int argc, char *argv[]) {

 
        mpz_class a=SECURE_TRAND(512),g,p,res;
   cout<<"Su clave generada es: "<<endl<<a<<endl;
  
   
   g=2;
   p="0x678471b27a9cf44ee91a49c5147db1a9aaf244f05a434d6486931d2d14271b9e35030b71fd73da179069b32e2935630e1c2062354d0da20a6c416e50be794ca4";

   
   mpz_powm(res.get_mpz_t(),g.get_mpz_t(),a.get_mpz_t(),p.get_mpz_t());
   
   
   char res_char[res.get_str().length()];
   strcpy( res_char,res.get_str().c_str());
  char key[65];
   cout<<"enviaremos="<< res.get_str();
   int cliente_servidor;

vector < node > lista_select,this_peer;
fd_set active_fd_set;
char* ip=(argv[1]); 

in_port_t port = 5000;


node peer;
int servidor_p2p,peer_p2p;

struct sockaddr_in peer_p2p_dir;
struct sockaddr_in cliente_servidor_dir,servidor_p2p_addr;
servidor_p2p_addr.sin_family = AF_INET;
makesock(cliente_servidor,cliente_servidor_dir,1,ip,port);
makesock(servidor_p2p,servidor_p2p_addr,0,"0.0.0.0",0);

const char *ip3=localip().c_str();
	

  

cout<< "Peer con Puerto: " << ip3<<":"<< htons(servidor_p2p_addr.sin_port)<<endl ;

		
add_node(this_peer,0,htons(servidor_p2p_addr.sin_port),ip3);
	
/*Falta hacer un bucle en el que se sea hasta que ya no haya m'as datos para recibir*/

char data[1024];

recv(cliente_servidor, &data, sizeof(data), MSG_DONTWAIT);

if(!strlen(data))
	cout << "Lista vacia: ";
	
else
{

        vector <node> peers;
	deserialize_all(data,peers);
       

    	/*Recibimos los peers conectados*/
	
	 for (auto i : peers)
    	{
    		char *ip_char= new char[(i.ip).length()+1];
    		strcpy(ip_char,(i.ip).c_str());
    	
        	cout << "Conexion con el peer " << i.fd << " Con direccion " << ip_char << ":" << i.port <<endl<<endl;
        	
		peer_p2p= makesock(i.fd,peer_p2p_dir,1,ip_char,i.port);
		send(peer_p2p, res_char,strlen( res_char)+1,0);
		
		add_node(lista_select, peer_p2p,ntohs(peer_p2p_dir.sin_port ),inet_ntoa(peer_p2p_dir.sin_addr)) ;
		
		delete [] ip_char;

    	}
    	
}

	
	
	send(cliente_servidor, (const_cast<char*>(serialize(this_peer).c_str())), sizeof(serialize(this_peer)), MSG_DONTWAIT);
	

int once=1;
 	  AES256_ctx ctx;

    string cipher;
    string  decipher;
 while (1) 
	{ 
	
		handle_select(active_fd_set,servidor_p2p,lista_select);
	  	FD_SET(0, &active_fd_set);
		
		
     		if(select (FD_SETSIZE, &active_fd_set, NULL, NULL, NULL)<0 ){
     		perror("select error");
     		exit(0);
     		}
      		
		for (int i = 0; i < FD_SETSIZE; i++)
        		if (FD_ISSET (i, &active_fd_set))
         		 {
         		 
           			 if (FD_ISSET(servidor_p2p,&active_fd_set))
             			 {
             			 
             			 	struct sockaddr_in client_addr;	
				       int cliente = new_connection(servidor_p2p,client_addr); 
				       add_node(lista_select,cliente,ntohs(client_addr.sin_port ),inet_ntoa(client_addr.sin_addr)) ;
					send(cliente, res_char,strlen( res_char)+1,0);
					once=1;
             			 }
           			 if (FD_ISSET(0, &active_fd_set))
              			 {
              			
    					char *msg_char;
    					
    	 				msg_char=getline();
    					
   					
   					
    
    					cipher = cipher_data(ctx, msg_char, 16);
    					
    
    
    
      					 for (auto i : lista_select)
    					 
    						send(i.fd,cipher.c_str(),cipher.length()+1,0);
    					
              				
              				
              			}
              			else
              			{
              			
              			
              				char *msg= new char[1024];
              				char ip[1024]={"0"};
              				int aux=recv(i, &ip, 1024, 0);
              				
              				if(aux==0)
              				{
              					cout<<"cliente eliminado";
              					del_node(lista_select,i);
              					close(i);
              				}
              				
              				if(aux>0)
              				{
              				
              					if(once){
              					
              					
              					mpz_class u,Secret;
              					u=ip;
              					Secret=GetSharedKey(p, a,u);
              					strcpy(key,sha256(Secret.get_str()).c_str());
              					unsigned char key_u[32];
   					 	from_hex(key_u, 32, key);
    						AES256_init(&ctx, key_u);
    
              					cout<<"Clave Secreta="<< key<<endl;
              					
              					once=0;
              					}
              				else{
              					cout<<"Mensaje recibido : "<<endl;
              					decipher= decipher_data(ctx, ip, 16);
              					
              					cout<<decipher<<endl;
              					}
              				
              				}
              				delete [] msg;
              			
              			}
         		 }
         		
          
         } 
        
        
    
 

 }
 
 
