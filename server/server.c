#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include "server.h"

//#include <mba/hashmap.h>

#define MAX_QUEUE 10
#define MAX_PLANETS 100
#define MAX_CLIENTS 100

Planet ** curr_frame;
Planet ** next_frame;
ClientInfo ctab[MAX_CLIENTS];

struct hashmap * pending;

int frame_num;

/*
 * Arguments: filename
 */

// Processes time request
void processRequest( int socket );
void processRequestThread(int*);
void sendJob(int sockt, Job* j);
void controlThread(void);
void generateRandom (void);
Planet * readData();

int masterSocket = 0;

// DEFAULT PORT
int port = 8887;

int mainReady = 0;

Planet * data;
ClientInfo * clients;
int dataSize = 100;
int clientSize = 1024;

int timeFrame = 0;

int main(int argc, char ** argv){

	// Print usage if not enough arguments

	curr_frame = (Planet **)malloc(MAX_PLANETS * sizeof(Planet *));
	next_frame = (Planet **)malloc(MAX_PLANETS * sizeof(Planet *));

	//hashmap_init(pending, 0, NULL, NULL, NULL, NULL);

	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress;
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);

	// Allocate a socket
	masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1;
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR,
		(char *) &optval, sizeof( int ) );

	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
		(struct sockaddr *)&serverIPAddress,
		sizeof(serverIPAddress) );

	if ( error ) {
		perror("bind");
		exit( -1 );
	}


	// Put socket in listening mode and set the
	// size of the queue of unprocessed connections
	error = listen( masterSocket, MAX_QUEUE);

	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	printf("Server created.\nPort: %d\n", port);


	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init( &attr );
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

	pthread_create(&tid, &attr, (void* (*)(void*))controlThread, NULL);



	while(!mainReady){
		//waiting for main thread to initialize
	}
	printf("Control thread started\n");
	while(1){
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,(struct sockaddr *)&clientIPAddress,(socklen_t*)&alen);

		//initialize pthread attributes
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init( &attr );
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

		pthread_create(&tid, &attr, (void * (*)(void*))processRequestThread, (void *)&slaveSocket);
	}
}

void processRequestThread(int* socket){
	processRequest(*socket);
	close(*socket);
}

void processRequest(int fd)
{
	printf("%d\n", fd);
	int n = 0;
	int length = 0;
	int readyCount = 0;

	char * msg = (char*) malloc(1024*sizeof(char));
	char c = '\0';

	while((n = read(fd, &c, sizeof(c))) > 0){
		msg[length] = c;
		length++;

		printf("%c\n", c);

		if(length > 1){
			if(msg[length-2] == '\r' && msg[length-1] == '\n'){
				msg[length] = '\0';

				if(strcmp("READY\r\n", msg) == 0){
					generateRandom();
					sendJob(fd, NULL); // Fix this
				}
			}
		}
	}
}

void sendJob(int sockt, Job* j){

	printf("Sending job.\n");

	// Dummy job
	j = (Job*)malloc(sizeof(Job));
	j->id = 2;
	j->planet_id = 5;

	// Send job id
	write(sockt, &(j->id), sizeof(int));

	// Send planet to be worked on id
	write(sockt, &(j->planet_id), sizeof(int));

	// Send positions: p_id, <x,y,z> \r\n
	int i = 0;
	while (i<MAX_PLANETS)
	{
		write(sockt, &(curr_frame[i]->id), sizeof(int));
		write(sockt, (curr_frame[i]->pos), sizeof(Vector));
		write(sockt, "\r\n", sizeof(char)*2); 
		i++;
	}

	i = 0;
	// Send velocities: p_id, <x,y,z> \r\n	
	while (i<MAX_PLANETS)
	{
		write(sockt, &(curr_frame[i]->id), sizeof(int));
		write(sockt, &(curr_frame[i]->velocity), sizeof(Vector));
		write(sockt, "\r\n", sizeof(char)*2);
		i++;
	}

	printf("Job Sent.\n");	
}

void controlThread()
{
	//data = readData();

	clients = (ClientInfo *) malloc(clientSize*sizeof(ClientInfo));

	mainReady = 1;
}

//TODO: EVERYTHING
Planet * readData()
{

}

void generateRandom ()
{
	int i;

	for (i = 0; i < MAX_PLANETS; i++)
	{
		curr_frame[i] = (Planet *) malloc(sizeof(Planet));

		curr_frame[i]->id = i;
		curr_frame[i]->mass = i;
		curr_frame[i]->pos = (Vector *)malloc(sizeof(Vector));
		curr_frame[i]->pos->x = i;
		curr_frame[i]->pos->y = i;
		curr_frame[i]->pos->z = i;
		curr_frame[i]->velocity = (Vector *)malloc(sizeof(Vector));
		memset(curr_frame[i]->velocity, 0, sizeof(Vector));
	}
}

void swapFrames ()
{
	int i;
	Planet ** swap_frame = curr_frame;

	curr_frame = next_frame;
	next_frame = swap_frame;
}

void addToNext(Planet * p)
{
	int id = p->id;
	next_frame[id] = (Planet *)malloc(sizeof(Planet));
	next_frame[id]->mass = p->mass;
	next_frame[id]->pos = p->pos;
	next_frame[id]->velocity = p->velocity;
}

