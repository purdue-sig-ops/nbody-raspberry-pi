server: server.o
	gcc -o server server.o -lnsl -lpthread

server.o: server.c server.h
	gcc -o server.o -c server.c -lnsl -lsocket -lpthread

clean:
	rm -f server *.o

