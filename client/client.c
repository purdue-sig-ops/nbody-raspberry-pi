#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculation.h"

#define MAX_PLANETS 100
Planet * curr_frame[MAX_PLANETS];

void receiveJob(int sockfd);

main(int argc, char **argv)
{
	//const char* server_ip = "50.116.49.217";
	//const char* server_ip = "128.10.25.209";
	const char* server_ip = "127.0.0.1";	
	//const char* server_ip = "128.10.2.16"; // lore
	const int port_num = 8887;
		
	struct sockaddr_in socketAddress;


	// Clear sockaddr structure
  	memset((char *)&socketAddress,0,sizeof(socketAddress));

  	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = inet_addr(server_ip);
	socketAddress.sin_port = htons((u_short)port_num);

  	// Get TCP transport protocol entry
  	struct  protoent *ptrp = getprotobyname("tcp");
  	if ( ptrp == NULL ) 
	{
    		fprintf(stderr, "cannot map \"tcp\" to protocol number");
    		perror("getprotobyname");
    		exit(1);
  	}

	int sockfd = socket(AF_INET,SOCK_STREAM, ptrp->p_proto);
	if (sockfd < 0)
	{
		fprintf(stderr, "Cannot create socket\n");
		exit(1);
	}
	
	int ret = connect(sockfd, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
	if (ret < 0)
	{
		fprintf(stderr, "Cannot connect\n");
		exit(1);
	}
	
	printf("Successful Connection.\n");
	// Tell server client is ready
	char* msg = "READY\r\n";
	write(sockfd, msg, strlen(msg));

	receiveJob(sockfd);

	// ----------------------------------------------------------------
	// Basic Test
	//-----------------------------------------------------------------
	/*Planet planetList[2];
	
	planetList[0].id = 0;
	planetList[1].id = 1;
	planetList[0].mass = 10000000000;
	planetList[1].mass = 20000000000;
	Vector* pos1 = (Vector*)malloc(sizeof(Vector));
	Vector* vel1 = (Vector*)malloc(sizeof(Vector));
	Vector* pos2 = (Vector*)malloc(sizeof(Vector));
	Vector* vel2 = (Vector*)malloc(sizeof(Vector)); 
	
	planetList[0].pos = pos1;
	planetList[0].pos->x = 1;
	planetList[0].pos->y = 2;
	planetList[0].pos->z = -1;
	planetList[0].pos->mag = 2.449489743;

	planetList[0].velocity = vel1;
	planetList[0].velocity->x = 2;
	planetList[0].velocity->y = 3;
	planetList[0].velocity->z = 4;
	planetList[0].velocity->mag = 5.385164807;

	planetList[1].pos = pos2;
	planetList[1].pos->x = 5;
	planetList[1].pos->y = 4;
	planetList[1].pos->z = 7;
	planetList[1].pos->mag = 9.486832981;

	planetList[1].velocity = vel2;
	planetList[1].velocity->x = 1;
	planetList[1].velocity->y = 2;
	planetList[1].velocity->z = -1;	
	planetList[1].velocity->mag = 2.449489743;
	
	printf("Before Update\n");
	printf("p0.xpos: %lf\n", planetList[0].pos->x);
	printf("p0.ypos: %lf\n", planetList[0].pos->y);
	printf("p0.zpos: %lf\n\n", planetList[0].pos->z);	
	printf("p0.xvel: %lf\n", planetList[0].velocity->x);
	printf("p0.yvel: %lf\n", planetList[0].velocity->y);
	printf("p0.zvel: %lf\n\n", planetList[0].velocity->z);
	printf("p1.xpos: %lf\n", planetList[1].pos->x);
	printf("p1.ypos: %lf\n", planetList[1].pos->y);
	printf("p1.zpos: %lf\n\n", planetList[1].pos->z);	
	printf("p1.xvel: %lf\n", planetList[1].velocity->x);
	printf("p1.yvel: %lf\n", planetList[1].velocity->y);
	printf("p1.zvel: %lf\n", planetList[1].velocity->z);

	update_planet(&planetList[0], &planetList[0], 2);

	printf("\nAfter Update\n");
	printf("p0.xpos: %lf\n", planetList[0].pos->x);
	printf("p0.ypos: %lf\n", planetList[0].pos->y);
	printf("p0.zpos: %lf\n\n", planetList[0].pos->z);	
	printf("p0.xvel: %lf\n", planetList[0].velocity->x);
	printf("p0.yvel: %lf\n", planetList[0].velocity->y);
	printf("p0.zvel: %lf\n\n", planetList[0].velocity->z);
	printf("p1.xpos: %lf\n", planetList[1].pos->x);
	printf("p1.ypos: %lf\n", planetList[1].pos->y);
	printf("p1.zpos: %lf\n\n", planetList[1].pos->z);	
	printf("p1.xvel: %lf\n", planetList[1].velocity->x);
	printf("p1.yvel: %lf\n", planetList[1].velocity->y);
	printf("p1.zvel: %lf\n", planetList[1].velocity->z);
	*/
	// -----------------------------------------------------------------
	// End Test 
	// -----------------------------------------------------------------
}

void receiveJob(int sockfd)
{
	int i;
	for (i = 0; i < MAX_PLANETS; i++)
	{
		curr_frame[i] = (Planet *) malloc(sizeof(Planet));
		curr_frame[i]->pos = (Vector *)malloc(sizeof(Vector));
		curr_frame[i]->velocity = (Vector *)malloc(sizeof(Vector));
	}

	// TODO: Read data from server
	// Receive job id
	int job_id;
	read(sockfd, &job_id, sizeof(job_id));
	printf("job_id: %d\n", job_id);

	// Receive planet to be worked on id
	int planet_id;
	read(sockfd, &planet_id, sizeof(planet_id));
	printf("planet_id: %d\n", planet_id);

	// Receive positions: p_id, <x,y,z> \r\n
	i = 0;
	char buf[2];
	while (i<MAX_PLANETS)
	{
		read(sockfd, &(curr_frame[i]->id), sizeof(int));
		printf("id: %d\n", curr_frame[i]->id);
		read(sockfd, curr_frame[i]->pos, sizeof(Vector));
		printf("Pos: %lf, %lf, %lf\n", curr_frame[i]->pos->x, curr_frame[i]->pos->y, curr_frame[i]->pos->z);
		read(sockfd, &buf[0], sizeof(char)*2); 
		i++;
	}

	buf[0] = 0;
	buf[1] = 0;
	// Receive velocities: p_id, <x,y,z> \r\n
	i = 0;
	while (i<MAX_PLANETS)
	{
		read(sockfd, &(curr_frame[i]->id), sizeof(int));
		printf("id: %d\n", curr_frame[i]->id);
		read(sockfd, curr_frame[i]->velocity, sizeof(Vector));
		printf("Vel: %lf, %lf, %lf\n", curr_frame[i]->velocity->x, curr_frame[i]->velocity->y, curr_frame[i]->velocity->z);
		read(sockfd, &buf[0], sizeof(char)*2); 
		i++;
	}
}


