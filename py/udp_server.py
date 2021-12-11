
import socket
import sys

addresses = []
host="0.0.0.0"
port=9999

def addr_to_msg(addr):
    return '{}:{}'.format(addr[0], str(addr[1])).encode('utf-8')

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) # UDP
sock.bind((host, port))
while True:
        data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
        print(data)
        addresses.append(addr)
        if len(addresses) >= 2:
            
            sock.sendto(addr_to_msg(addresses[1]), addresses[0])
            sock.sendto(addr_to_msg(addresses[0]), addresses[1])
            addresses.pop(1)
            addresses.pop(0)



