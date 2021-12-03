#include "utils.h"
#include "public-ip.h"

int main(int argc,char *argv[]) {

	if(argc>3)
	{
	cout<<"Parametros incorrectos"<<endl;
	exit(0);
	}
cout<<"Servidor Ejecutandose en= "<<GetIp()<<":"<<atoi(argv[1])<<endl;
	in_port_t port = atoi(argv[1]); 

        
	
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	vector < node > lista_nodos;
	vector < node > lista_select;
    	node nodo;
    	
    

	struct sockaddr_in sock_dir;	
		
	memset(&sock_dir, 0, sizeof(sock_dir));       
	sock_dir.sin_family = AF_INET;
	sock_dir.sin_addr.s_addr = htonl(INADDR_ANY); 
	sock_dir.sin_port = htons(port);

	
	if(bind(sock, (struct sockaddr*) &sock_dir, sizeof(sock_dir)) <0)
	{
	printf("error de bind");
                exit(0);
	}
		
	
	listen (sock, 1);
	   
	fd_set active_fd_set;
	
	int i;
	int cliente=sock;
                       
               
        	
	
                        
	while (1) 
	{ 
	
		handle_select(active_fd_set,sock,lista_select);
	  	
		
		
     		if(select (FD_SETSIZE, &active_fd_set, NULL, NULL, NULL)<0 ){
     		perror("select error");
     		exit(0);
     		}
      		
		for (i = 0; i < FD_SETSIZE; ++i)
        		if (FD_ISSET (i, &active_fd_set))
         		 { 
         		 
           			 if (i == sock)
             			 {
             			 
               			
        				struct sockaddr_in client_addr;	
					cliente = new_connection(sock,client_addr); 
					
	
					
					add_node(lista_select,cliente,ntohs(client_addr.sin_port ),inet_ntoa(client_addr.sin_addr)) ;
					
 					string aux;
              			
					aux=serialize(lista_nodos);
						char * cadena =(const_cast<char*>(aux.c_str()));
						if(aux.size()==0)
							send(cliente, "Vacia", 6, 0);
						
						else
              						send(cliente, cadena, aux.length()+1, 0);

               			
    					
                     			FD_SET (cliente, &active_fd_set);
             			 }
           			 else
              			{
              			
              			char ip[1024]={"0"};;
              			
              			
              			
              			
              			if(recv(i, &ip, 1024, MSG_DONTWAIT)==0)
              				{
              					del_node(lista_select,i);
              				del_node(lista_nodos,i);
              				cout<<"Nodo desconectado"<<endl;
              				FD_CLR(i,&active_fd_set);
              				close(i);
              				}
              				
              				else
              				{
              				if(strlen(ip)>8)
              				{
              				
              				cout<<"Añadimos nodo"<<ip<<endl;
              				deserialize(ip,nodo);
              				nodo.fd=i;
              				lista_nodos.push_back(nodo);
              				
					string aux;
              				aux=serialize(lista_nodos);
					
              				send(i, (const_cast<char*>(aux.c_str())), sizeof(aux), MSG_DONTWAIT);
				
              			
              				FD_CLR(i,&active_fd_set);
              				}
              				}
              		
              			}
         		 }
         		
          
         } 
        
        }
    
 
    
   
