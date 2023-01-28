/*************************************************************************
        > File Name: MY_TCP.h
      > Author: tanfenyuan
      > Mail: tanfenyuan@outlook.com 
      > Created Time: Fri 27 Jan 2023 08:14:34 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

//多线程
#include <pthread.h>
#include <fstream>
#include "tinyxml2.h"
using namespace std;
namespace MY_TCP
{

//服务端
class Server
{
private:
	int listen_d;
	struct sockaddr_in serv_addr;



	int client_d;
	int sock_len = sizeof(struct sockaddr_in);
	struct sockaddr_in client_addr;
	
	char* buffer;
	int buffer_size;
public:
	Server(unsigned int size = 1024);
	~Server();

	bool InitServer(const unsigned int port);
	bool Accept();

	void CloseListen();
	void dispose(const char* XML);

	const char* GetIP()const 
	{
		return inet_ntoa(client_addr.sin_addr);
	}
	const char* Get_buffer()const 
	{
		return this->buffer;
	}
	bool Write(string connent);
	bool Read();
	
};
//客户端
class Client
{
private:
	int sock;
	struct sockaddr_in serv_addr;
	struct hostent* h ;
	char* buffer;
	int buffer_size;
public:
	Client(unsigned int size = 1024);
	~Client();

	bool ConnectToSever(const char* addr,unsigned int port);
	void dispose(const char* XML);

	
 	bool Write(string connent);
	bool Read();

	const char* Get_buffer()const
	{
		return this->buffer;
	}
/*
	bool Write(Message& str);
	Message Read();
*/
};
//文件读写
class LogFile
{
private:
	std::fstream file;
	bool file_status;
	
public:
	LogFile()
	{
		this->file_status = true;
	}
	~LogFile()
	{
		if(file_status)
		{
			file.close();
		}
	}
	bool Open(const char* file_path,const char* connect);
	
};


//全局的接受/发送函数
//size_t recv(int sockfd,void *buf , size_t len , int flags);
//bool Read(int sock, const char* buffer)
bool Read(int sock,std::string& str);
//send(int sockfd,const void* buf ,size_t len ,int flags)
//bool send(int sock,char* buffer);
bool Write(int sock, std::string& str);
class Global
{
private:
	char* buffer;
public:
	Global(unsigned int size=1024);
	~Global();
	const char* Get_buffer()const
	{
		return this->buffer;
	}

	bool Read(int sock);
	bool Write(int sock,string str);
};
}//end MY_TCP


