all: server client

server: 
	g++-4.8 -std=c++11 -o server server.cc -lzmq

client:
	g++-4.8 -std=c++11 -o client client.cc -lzmq

clean:
	rm -f server client

