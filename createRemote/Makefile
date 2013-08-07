# CSC353 Final Project
# Yang Li & Janet 
#
# Makefile for createRemote
#
# adapted from Simple Client Server by Rob Tougher
# http://tldp.org/LDP/LG/issue74/tougher.html

server_objects = ServerSocket.o Socket.o server_main.o
client_objects = ClientSocket.o Socket.o client_main.o include/Create.o  


all : create_remote_server create_remote_client

create_remote_server: $(server_objects)
	g++ -o createRemoteServer $(server_objects)


create_remote_client: $(client_objects)
	g++ -I include -L lib -lserial -o createRemoteClient $(client_objects) 


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
server_main: server_main.cpp
client_main: client_main.cpp


clean:
	rm -f *.o createRemoteServer createRemoteClient
