# UDPPingClient.py
import time
import sys
import socket




server="0.0.0.0" #ip publica servidor
port = 5000
	

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
host_name = socket.gethostname()
host_addr = socket.gethostbyname(host_name)
print(host_addr)


client.sendto(host_addr.encode(), (server, port))
message, address = client.recvfrom(port)
print(message)
mss=str(message.decode()).split(' ')
#conecta a ambas IPs
client.sendto(host_addr.encode(), (mss[0], port))
client.sendto(host_addr.encode(), (mss[1], port))


