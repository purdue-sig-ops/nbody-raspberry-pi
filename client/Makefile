client: client.o calculation.o
	gcc -o client client.o calculation.o -lnsl -lm 

calculation.o: calculation.c calculation.h
	gcc -o calculation.o -c calculation.c -lnsl -lm -lsocket

client.o: client.c
	gcc -o client.o -c client.c -lnsl -lsocket

clean:
	rm -f client *.o
