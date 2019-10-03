/************************************************* 
Copyright:leyiweb 
Author: leyiweb
Date:2017-7-6 
Description:实现qt多人聊天室服务器端
**************************************************/  
#include <netinet/in.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
#include <stdio.h>        
#include <stdlib.h>  

#include <string.h>       
#include <unistd.h>
#include <pthread.h>
#include <iostream> 
#include <list>  
#include <map>
#include <string>
#include <algorithm> 
#include <linux/tcp.h> 
using namespace std;

#define HELLO_WORLD_SERVER_PORT    419
#define LENGTH_OF_LISTEN_QUEUE 200
#define BUFFER_SIZE 1024
#define CLIENTNUMBER 100

//list<int> client;
map<string,int> client;
//声明服务器配置参数
struct sockaddr_in server_addr;
int server_socket;
int opt;

/***配置user字符串***/
char * catCharInt(char *b,int n) 
{
	char c[10];
	snprintf(c, sizeof(c), "%d", n);
	char *result = (char*)malloc(7+strlen(c) + strlen(b) + 1);
	strcpy(result, "user");
	strcat(result, c);
	strcat(result, ": ");
	strcat(result, b);

	return result;
}


/************************************************* 
Function:       initServiceSocket() 
Description:    初始化socket通信 
Calls:          // 被本函数调用的函数清单 
Table Accessed: 无 
Table Updated:  无 
Input:          无
Output:         无 
Return:         无
Others:         用于定义socket通信服务器相关的配置
                进行绑定端口和设置最大的socket连接数 
*************************************************/  
void initServiceSocket() 
{
	/*  快速清除结构体中成员的值为0 */
	bzero(&server_addr, sizeof(server_addr));

	/* 定义server_addr相关配置 */
	server_addr.sin_family = AF_INET;            //协议族决定了socket的地址类型，在通信中必须采用对应的地址，如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);//所有网卡
	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

	/*创建服务器上的socket*/
	server_socket = socket(PF_INET, SOCK_STREAM, 0);  //0 选择第二个参数类型对应的默认协议。
	if (server_socket < 0) 
	{
		printf("Create Socket Failed!");
		exit(1);
	}

	/* 设置socket等待时间，以至于不会直接断开 */
	//（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	/*  绑定服务器socket端口 */
	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))) 
	{
		printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT);
		exit(1);
	}

	/*  监听服务器socket端口，设置最大监听数 */
	/*  成功返回0，失败返回1 */
	if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE)) 
	{
		printf("Server Listen Failed!");
		exit(1);
	}

}

/***
进程服务函数
***/
void* muti(void* args)
{
	int length;
	int clientId = *(int *)args;
	char buffer[BUFFER_SIZE]; 
	char leyi[BUFFER_SIZE];
	string send_name;
	char c[10]; 
	map <string,int>::iterator it;
	while(1){
		bzero(buffer, BUFFER_SIZE);
		length = recv(clientId, buffer, BUFFER_SIZE, 0);
		if (length <= 0) 
		{
			printf("Server Recieve Data Failed!\n");
			break;
		}

		/* 解析用户名+ID绑定 */
 		if(buffer[0] == 'A') 
 		{
 			char * begin = strstr(buffer,"#");
 			begin++;
 			char * next = strstr(begin,"#");
 			memcpy(leyi,begin,next-begin);
 			leyi[next-begin] = '\0';
 			send_name = leyi;
 			client[send_name] = clientId;

 			/* 向其他用户发送新增信息 */
 			char str[100];
 			bzero(str, 100);
 			strcpy(str,"D#+#");
 			strcat(str,leyi);
 			strcat(str,"#1");
 			for(it = client.begin();it != client.end();it++) {
				if(it->second != clientId) {
					send(it->second, str, strlen(str) + 1, 0);
				}
			}
 			
 			/* 向自己客户端发送新增用户信息 */
 			/*int count = 0;
 			char num[20];
			bzero(str, 100);
			bzero(num, 100);
			strcpy(str,"D#+#");
			for(it = client.begin();it != client.end();it++) {
				if(it->second != clientId) {
					strcat(str,(it->first).c_str());
					strcat(str,"#");
					count++;
				}
			}
			//itoa(count,num,10);
			snprintf(num, sizeof(num), "%d", count);  
			strcat(str,num);
			send(clientId, str, strlen(str) + 1, 0);*/
 		}
 		else if(buffer[0] == 'B') 
 		{
 			char rece[20];
 			char * data;
 			char * begin = strstr(buffer,"#");
 			begin++;
 			char * next = strstr(begin,"#");
 			memcpy(leyi,begin,next-begin);
 			leyi[next-begin] = '\0'; 

 			begin = next;
			begin++;
			next = strstr(begin,"#");
			memcpy(rece,begin,next-begin);
			rece[next-begin] = '\0';
			
			begin = next;
			begin++;
			data = begin;

			char str[1000];
			str[0] = 'E';
			str[1] = '#';
			memcpy(str+2,leyi,strlen(leyi));
			str[2+strlen(leyi)] = '#';
			memcpy(str+3+strlen(leyi),data,strlen(data));
			str[3+strlen(leyi)+strlen(data)] = '\0';

			for(it = client.begin();it != client.end();it++) {
				if(it->second != clientId) {
					send(it->second, str, strlen(str) + 1, 0);
				}
			}
			//printf("%s ",str);
 		}
 		else if(buffer[0] == 'C') 
 		{
 			char rece[20];
 			char * data;
 			char * begin = strstr(buffer,"#");
 			begin++;
 			char * next = strstr(begin,"#");
 			memcpy(leyi,begin,next-begin);
 			leyi[next-begin] = '\0'; 

 			begin = next;
			begin++;
			next = strstr(begin,"#");
			memcpy(rece,begin,next-begin);
			rece[next-begin] = '\0';
			string reces = rece;
			
			begin = next;
			begin++;
			data = begin;

			char str[1000];
			str[0] = 'E';
			str[1] = '#';
			memcpy(str+2,leyi,strlen(leyi));
			str[2+strlen(leyi)] = '#';
			memcpy(str+3+strlen(leyi),data,strlen(data));
			str[3+strlen(leyi)+strlen(data)] = '\0';

			it = client.find(reces);
			send(it->second, str, strlen(str) + 1, 0);
			printf("%s\n",str);
 		}

		printf("%s\n",buffer);
	/*	strcpy(buffer,catCharInt(buffer,clientId));
		for (list<int>::iterator iter = client.begin(); iter != client.end(); ++iter) {
			if (*iter != clientId) {
				send(*iter, buffer, strlen(buffer) + 1, 0);
			}
		}*/
	}
	it = client.find(send_name);
	client.erase(it);
}

int main(int argc, char **argv)
{
	/* 对client的变量的声明及初始化 */
	int Ret;
	char buffer[BUFFER_SIZE];
	pthread_t id;
	int ret;
	char c[10];

	initServiceSocket();

	while(1){
		struct sockaddr_in client_addr;
     	int client_socket;  //一个socket连接的id号，标识符
    	socklen_t length;
	    length = sizeof(client_addr);
		
		/* 进入阻塞状态，等待新的socket连接 */
		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);
		printf("新加入的socket id为：%d\n", client_socket);

		/*  如有新的socket连接，判断连接是否正常 */
		if (client_socket < 0) {
			printf("Server Accept Failed!\n");
			break;
		}else {
           // client.push_back(client_socket);//将socket标识符放入容器
            ret = pthread_create(&id, NULL, muti, &client_socket);  //创建子进程
           /* snprintf(c, sizeof(c), "%d", client.size());
            strcpy(buffer,c);
            for (list<int>::iterator iter = client.begin(); iter != client.end(); ++iter) {	
					send(*iter, buffer, strlen(buffer) + 1, 0); //更新用户总数
			}*/
		}
		strcpy(buffer,"connect success!\n");
		Ret = send(client_socket, buffer, strlen(buffer) + 1, 0);
		if (Ret == -1) {
			printf("Send Info Error::\n");
		    printf("%d\n", length);
		    break;
		}
	}
	return 0;
}