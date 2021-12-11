import sys
from socket import *
import time
import select

host = '0.0.0.0'
port = 5000

#CREACION DEL SOCKET UDP

server = socket(AF_INET, SOCK_DGRAM)
#ASIGNACION DE LA IP Y EL PUERTO A EL SOCKET
server.bind((host, port))


lista=[]
direcciones=[]
w=0

peers=0;
while True:

    message, address = server.recvfrom(port)
    direcciones.append(address)
    print(message.decode('ascii'))
    print(address[0])
    envio=message.decode()+' '+str(address[0])
    lista.append(envio)
    
    
    if len(direcciones) >= 2:
           
     for i in direcciones:
     
      server.sendto(envio[w].encode(), i)
      w=w+1    
    
    
    
     
    


