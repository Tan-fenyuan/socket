/*************************************************************************
        > File Name: MY_TCP.cpp
      > Author: tanfenyuan
      > Mail: tanfenyuan@outlook.com 
      > Created Time: Fri 27 Jan 2023 02:14:51 PM CST
 ************************************************************************/

#include "../include/MY_TCP.h"
namespace MY_TCP
{


//////////////////////////////////////////////////////////////////
//
//							server
//
//////////////////////////////////////////////////////////////////
/*
 *
 * 构造函数 
 *  unsigned int size
 *
 * */
Server::Server(unsigned int size)
{
	this->listen_d = -1;
	this->buffer_size = size;
	this->buffer = new char[size];
}
Server::~Server()
{
	delete[] buffer;
	close(listen_d);
	close(client_d);
}


bool Server::InitServer(const unsigned int port)
{
	if(port<0||port>65535)
	{
		return false;
	}
	this->listen_d = socket(AF_INET,SOCK_STREAM,0);
	if(this->listen_d == -1)
	{
		cerr<<"server socket failed"<<endl;
		return false;
	}
	memset(&serv_addr , 0 ,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);
	if(bind(listen_d,(struct sockaddr*)&serv_addr,sizeof(serv_addr))!=0)
	{
		cerr<<"server bind failed"<<endl;
		close(listen_d);
		return false;
	}
	if(listen(listen_d,5)!=0)
	{
		cerr<<"server listen failed"<<endl;
		close(listen_d);
		return false;
	}
	return true;
}
bool Server::Accept()
{
	client_d = accept(listen_d,(struct sockaddr*)&client_addr,(socklen_t*)&sock_len);
	if(client_d == -1)
	{
		cerr<<"server failed"<<endl;
		close(listen_d );
		return false;
	}
	return true;
}
void Server::CloseListen()
{
	close(listen_d);
}
void Server::dispose(const char* XML)
{
	tinyxml2::XMLDocument doc;
	doc.Parse(XML);
	tinyxml2::XMLElement*name = doc.FirstChildElement("name");
	cout<<"name: "<<name->GetText()<<endl;
	name = name->FirstChildElement("message");
	tinyxml2::XMLText *text = name->FirstChild()->ToText();
	cout<<"message: "<<text->Value()<<endl;
}


bool Server::Write(string connent)
{
	if(send(client_d,connent.c_str(),connent.size(),0)<=0)
	{
		cerr<<"send failed"<<endl;
		return false;
	}
	return true;
}




bool Server::Read()
{
	memset(buffer, 0,buffer_size);
	if(recv(client_d,buffer,buffer_size,0)<=0)
	{
		return false;
	}
		
	return true;
}



//////////////////////////////////////////////////////////////////
//
//							client
//
//////////////////////////////////////////////////////////////////

Client::Client(unsigned int size)
{
	this->sock = -1;
	this->buffer_size = size;
	this->buffer = new char[size+1];
	memset(this->buffer,0,sizeof(this->buffer));
}


Client::~Client()
{
	delete[] buffer;
	close(sock);
}


//向connectToSever()方法传入值
// addr - 目标服务端的IP地址
// port - 目标服务端的已开放端口号
bool Client::ConnectToSever(const char*addr ,unsigned int port)
{
	this->sock = socket(AF_INET,SOCK_STREAM,0);
	if(this->sock == -1)
	{
		cerr<<"socket failed"<<endl;
		return false;
	}
	if((h = gethostbyname(addr)) == 0)
	{
		cerr<<"gethostbyname failed"<<endl;
		close(sock);
		return false;
	}
	if(port < 0|| port >65535)
	{
		return false;
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	

	memcpy(&serv_addr.sin_addr.s_addr ,h->h_addr,h->h_length);
	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))!=0)
	{
		cerr<<"connect failed"<<endl;
		close(sock);
		return false;

	}
	return true;
}

void Client::dispose(const char* XML)
{
	tinyxml2::XMLDocument doc;
	doc.Parse(XML);
	tinyxml2::XMLElement* name = doc.FirstChildElement("name");
	cout<<"name: "<<name->GetText()<<endl;
	name = name->FirstChildElement("message");
	tinyxml2::XMLText *text = name->FirstChild()->ToText();
	cout<<"message: "<<text->Value()<<endl;

}
bool Client::Write(string str)
{
	//send
	if(send(sock,str.c_str(),str.size(),0) <=0)
	{
		cerr<<"send failed"<<endl;
		return false;
	}
	return true;
	
}
bool Client::Read()
{
	memset(buffer,0,buffer_size);
	if(recv(sock,this->buffer,buffer_size,0)<=0)
	{
		cerr<<"recv failed"<<endl;
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////
//
//							LogFile
//
//////////////////////////////////////////////////////////////////
//file_path 是一个绝对路径
//connect是要往文件里记录的内容
bool LogFile::Open(const char* file_path,const char* connent)
{
	/*
	 *	将文件以追加模式打开,
	 *
	 *	注意: 
	 *		这个函数日后会更改,
	 *		更改思路:
	 *			1>会再增加一个函数参数,用来让用户自己定义文件打开的方式
	 * */
	this->file.open(file_path,std::ios::app);
	if(!file.is_open())
	{	
		//如果文件打开失败
		//则直接关闭连接,并且输出错误语句;
		file.close();
		return false;
	}
	std::string str(connent);
	file >> str;
	file.close();
	this->file_status = false;	
	return true;
}
/* 这是不需要的代码，但是我懒得改
bool Read(int sock)
{
	memset(buffer,0,sizeof(buffer));
	if(recv(sock,buffer,strlen(buffer),0)<=0)
	{
		return false;
	}
	return true;
}
bool Write(int sock,string& buffer)
{

	if(send(sock,buffer.c_str(),buffer.size(),0)<=0)
	{
		cerr<<"send() failed"<<endl;
		return false;
	}
	return true;
}
*/
Global::Global(unsigned int size)
{
	this->buffer = new char[size];
	memset(this->buffer,0,sizeof(this->buffer));
}
Global::~Global()
{
	delete[] buffer;
}
bool Global::Read(int sock)
{
	memset(this->buffer,0,sizeof(this->buffer));
	if(recv(sock,this->buffer,strlen(this->buffer),0)<=0)
	{
		return false;
	}
	return true;
}
bool Global::Write(int sock,string str)
{
	if(send(sock,str.c_str(),str.size(),0)<=0)
	{
		return false;
	}
	return true;
}
}//end MY_TCP
