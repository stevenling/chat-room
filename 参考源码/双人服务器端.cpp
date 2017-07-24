#include <netinet/in.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
#include <stdio.h>        
#include <stdlib.h>  

#include <string.h>       
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <iostream>  
#include <list>  
#include <algorithm> 
#include <linux/tcp.h> 
using namespace std;
#define HELLO_WORLD_SERVER_PORT    4000
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define CLIENTNUMBER 100
list<int> client;		//存放client Id。
int clientId[CLIENTNUMBER];
char sentBuff[1024];
int Ret = 0;
//pthread_t roomId[CLIENTNUMBER];
struct sockaddr_in server_addr;			
int server_socket;
int opt = 1;
int isConnected = 1;

/**********************************
*在存放client的id链表里，删除某个client的Id
*/
int cutByvalue(list<int> &l, int value) {
	for (list<int>::iterator iter = l.begin(); iter != l.end(); ++iter)
	{
		if (*iter == value) {
			l.erase(iter);
			return 1;
		}
		//    printf("%d \n", *iter);
	}
	return 0;
}

/**********************
*判断新连接的client端的id,是否是已连接的clinet。
*/
int isFind(list<int> &l, int value) {
	for (list<int>::iterator iter = l.begin(); iter != l.end(); ++iter)
	{
		if (*iter == value) {
			return 1;
		}
		//    printf("%d \n", *iter);
	}
	return 0;
}

/******************************************
*每次有两个用户连接，相对创建了一个房间
*/
typedef struct Room
{
	int boy;
	int girl;
}Room;

/*******************************
*初始化服务器端的socket
*/
void initServiceSocket() {
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;            //协议族决定了socket的地址类型，在通信中必须采用对应的地址，如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);//所有网卡
	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

	/* create a socket */
	server_socket = socket(PF_INET, SOCK_STREAM, 0);  //0 选择第二个参数类型对应的默认协议。
	if (server_socket < 0)
	{
		printf("Create Socket Failed!");
		exit(1);
	}

	/* bind socket to a specified address*/
	//（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT);
		exit(1);
	}

	/* listen a socket */
	if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE))
	{
		printf("Server Listen Failed!");
		exit(1);
	}

}


/*********************************************
*连接数字和整形，返回char*
* */
char *catCharInt(int n,char *b){
	char c[10];
	//itoa(n, c, 10);
	snprintf(c, sizeof(c), "%d", n);
	char *result = (char*)malloc(7+strlen(c) + strlen(b) + 1);
	strcpy(result, "user");
	strcat(result, c);
	strcat(result, ": ");
	strcat(result, b);
//	printf("%s", result);
	return result;
}

/*************************
*用来监听user1并发送数据给user2
*参数 room的结构体
*/
void* user(void* args) {
	char buffer[BUFFER_SIZE];           //存放接收的数据和发送的数据
	char sendBuff[BUFFER_SIZE];
	int client1, client2;
	client1 = ((Room*)args)->boy;
	client2 = ((Room*)args)->girl;
	int length;
	while (1) {
		bzero(buffer, BUFFER_SIZE);
		length = recv(client1, buffer, BUFFER_SIZE, 0);
		printf("%d\n", strlen(buffer));
		if (length <= 0)
		{
			printf("Server Recieve Data Failed!\n");
			break;
		}
		
		/* send data to user2 */
		strcpy(buffer,catCharInt(client2,buffer));
		Ret = send(client2, buffer, strlen(buffer) + 1, 0);
		//Ret = send(client_socket, "ok", strlen('ok'), 0);
		if (Ret == -1)
		{
			printf("Send Info Error::\n");
			printf("%d\n", length);
			break;
		}


		printf("%s\n", buffer);
	}
	printf("user1 gg");
	close(client1);
	strcpy(buffer, "%&@(");
	send(client2, buffer, strlen(buffer) + 1, 0);
	cutByvalue(client, client1);
	free(args);
}

/*************************************************
*通过传入的Room结构体，创建一个房间用来两个用户数据的交互
*/
void* setRoom(void* args) {
	Room *room;
	room = (Room*)malloc(sizeof(Room));
	room->boy = ((Room*)args)->girl;
	room->girl = ((Room*)args)->boy;
	pthread_t id;
	pthread_t id2;
	int i, ret, ret2;
	ret = pthread_create(&id, NULL, user, args);
	ret2 = pthread_create(&id2, NULL, user, room);
}



int main(int argc, char **argv)
{
	pthread_t roomId;
	memset(clientId, -1, sizeof(clientId));
	Room *room;

	initServiceSocket();

	/* run server */
	while (1)
	{
		struct sockaddr_in client_addr;
		int client_socket;
		socklen_t length;
		char buffer[BUFFER_SIZE];
		/* accept socket from client */
		length = sizeof(client_addr);
		printf("client1=%d\n", clientId[0]);
		printf("client2=%d\n", clientId[1]);
		if (clientId[0] == -1)
		{
			/* code */
			clientId[0] = accept(server_socket, (struct sockaddr*)&client_addr, &length);
			if (clientId[0]  < 0)
			{
				printf("Server Accept Failed!\n");
				break;
			}
		}
		else if (isFind(client, clientId[0]) == 0)
		{
			strcpy(sentBuff, "~12oLH>");        //给client端发送等待的指令
			Ret = send(clientId[0], sentBuff, strlen(sentBuff) + 1, 0);
			clientId[1] = accept(server_socket, (struct sockaddr*)&client_addr, &length);
			if (clientId[1]  < 0)
			{
				printf("Server Accept Failed!\n");
				break;
			}
			else {
				strcpy(sentBuff, "#3206*");			//给client端发送连接成功的指令
				Ret = send(clientId[0], sentBuff, strlen(sentBuff) + 1, 0);
				printf("%d\n", Ret);
				if (Ret == -1) {
					printf("fail to send 1111");
					clientId[0] = clientId[1];
					strcpy(sentBuff, "~12oLH>");			//给client端发送等待的指令
					Ret = send(clientId[0], sentBuff, strlen(sentBuff) + 1, 0);
				}
				else {
					strcpy(sentBuff, "#3206*");     //给client端发送连接成功的指令
					printf("room");
					Ret = send(clientId[1], sentBuff, strlen(sentBuff) + 1, 0);
					room = (Room*)malloc(sizeof(Room));
					room->boy = clientId[0];
					room->girl = clientId[1];
					client.push_back(clientId[0]);
					client.push_back(clientId[1]);
					pthread_create(&roomId, NULL, setRoom, room);
					clientId[0] = -1;
					clientId[1] = -1;
				}

			}
		}

	}

	close(server_socket);
	return 0;
}
