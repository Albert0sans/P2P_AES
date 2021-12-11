import socket
import sys


# A ->   con server
#B ->  con server
#server -> envia a A la ip publica y privada de B
#server -> inicia conexion con B con la ip publica y privada de A
#A      -> envia paquetes UDP a la direccion publica y privada A
#B      -> envia pquetes UDP a la direccion publica y privada de A


host='34.71.234.19'
port=9999

def msg_to_addr(data):
    ip, port = data.decode('utf-8').strip().split(':')
    return (ip, int(port))

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.sendto(b'0', (host, port))
data, addr = sock.recvfrom(1024)     
addr = msg_to_addr(data)
message = sys.stdin.readline()  
sock.sendto(message.encode(), addr)
data, addr = sock.recvfrom(1024)
print('client received: {} {}'.format(addr, data))


