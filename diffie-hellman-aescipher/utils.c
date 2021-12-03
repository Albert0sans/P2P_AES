#include "utils.h"



int makesock(int &sock,struct sockaddr_in &sock_dir, int c,const char * ip,in_port_t port){


sock =  socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);


memset(&sock_dir, 0, sizeof(sock_dir)); 
sock_dir.sin_family = AF_INET;

	if(c==1)
	{
		
		//printf("Nos conectamos a %s:%d",ip,port);
		inet_pton(AF_INET, ip, &sock_dir.sin_addr.s_addr);
 		sock_dir.sin_port = htons(port); 
 

		int g = connect(sock, (struct sockaddr *) &sock_dir, sizeof(sock_dir));
		if (g==-1)
		{
		printf("Error de conexion");
		exit(0);
		}
		
		
	}
	else
	{	


	
		sock_dir.sin_addr.s_addr = htonl(INADDR_ANY); 
		sock_dir.sin_port = htons(port);

		bind(sock, (struct sockaddr *)&sock_dir, sizeof(sock_dir));
		
		listen(sock, 1) ;
		 socklen_t len = sizeof(sock);
	getsockname(sock, (struct sockaddr *) &sock_dir, &len);
	


}
return sock;
}

int new_connection(int sock,struct sockaddr_in &new_addr)
{

      
socklen_t len = sizeof(struct sockaddr);
int new_sock = accept(sock, (struct sockaddr *) &new_addr, &len);
char ip[INET_ADDRSTRLEN]; 
inet_ntop(AF_INET, &new_addr.sin_addr.s_addr, ip,sizeof(ip));
printf("Nueva conexion de %s/%d\n", ip, ntohs(new_addr.sin_port));

return new_sock;
}
char * getline(void) {
    char * line = (char*)malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = (char*)realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}
void handle_select(fd_set &active_fd_set, int sock,vector < node > lista )//funcion que hacer set de los clientes y borra los que tengan fd=-1;

{
FD_ZERO(&active_fd_set);
	
FD_SET(sock,&active_fd_set);

for (auto i : lista)
    {
        
	FD_SET(i.fd,&active_fd_set);

    }

}

/////////////////////////////////////////////////////////////

string serialize(vector <node> lista_nodos)
{
string aux;
for (size_t i = 0; i < lista_nodos.size(); ++i)
{
	aux.append((to_string(lista_nodos[i].fd)));
	aux.push_back('&');
	aux.append((to_string(lista_nodos[i].port)));
	aux.push_back('&');
	aux.append(lista_nodos[i].ip);
	aux.push_back('&');
	}

return aux;


}
void  del_node(vector<node>& lista_nodos, int port) {
    for (size_t i = 0; i < lista_nodos.size(); ++i)
        if (lista_nodos[i].port == port)
            cout << "Eliminamos el nodo " << i << endl;

    lista_nodos.erase(
        std::remove_if(lista_nodos.begin(), lista_nodos.end(), [&](node const& nodo) {
            
            
            return nodo.fd == port;
            }),
        lista_nodos.end());

    
}

void view_nodes(vector < node > lista_nodos)
{


	cout<<"Mostrando lista: Hay "<<lista_nodos.size()<<" Nodos"<<endl;
    for (auto i : lista_nodos)
    {
        cout << "nodo " << i.fd << " Con direccion " << i.ip << ":" << i.port <<endl;


    }
   
}
void  add_node(vector<node> &lista_nodos, int fd,int port,string ip) {
    lista_nodos.push_back(node());
    lista_nodos[lista_nodos.size()-1].fd = fd;
    lista_nodos[lista_nodos.size()-1].port = port;
    lista_nodos[lista_nodos.size() - 1].ip = ip;

    
} 
void deserialize_all(char* serial_data,vector<node> &data)
{

int fd=0;
int port=0;
string ip;
string aux;

int j=0;
int fin_conv=0;
for(size_t i=0;i<strlen(serial_data);i++)
	{
	
	if(serial_data[i]=='&'){
	
		switch (j)
			{
			case 0:
				{
				fd=stoi(aux);
				
				fin_conv=0;
				break;
				}
			case 1:
				{
				port=stoi(aux);
				
				fin_conv=0;
				break;
				}

			case 2:
				{

				ip=aux;
				
				fin_conv=1;
				break;
				}



			}

		aux.clear();
		if(j<2){
			j++;
			fin_conv=0;
			}
		else{
			j=0;
			fin_conv=1;
			}
	}
	
	else
		aux.push_back(serial_data[i]);
		
	if(fin_conv){
	add_node(data,fd,port,ip);
	fin_conv=0;
		
		
		}
		


	}




}
void deserialize(char* serial_data,node &data)
{

string aux;

int j=0;

for(size_t i=0;i<strlen(serial_data);i++)
	{
	if(serial_data[i]=='&'){
	
		switch (j)
			{
			case 0:
				{
				data.fd=stoi(aux);
				break;
				}
			case 1:
				{
				data.port=stoi(aux);
				break;
				}

			case 2:
				{

				data.ip=aux;
				break;
				}



			}

		aux.clear();
		if(j<3)
			j++;
		else
			j=0;
	
	}
	
	else
		aux.push_back(serial_data[i]);



	}

}

