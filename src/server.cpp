/*************************************************************************
        > File Name: server.cpp
      > Author: tanfenyuan
      > Mail: tanfenyuan@outlook.com 
      > Created Time: Fri 27 Jan 2023 09:09:17 PM CST
 ************************************************************************/

#include "../include/MY_TCP.h"
int main()
{
	MY_TCP::Server server;
	server.InitServer(5000);
	if(!server.Accept())
	{
		cerr<<"Accept failed"<<endl;
	}
		
	while(1)
	{
		if(!server.Write("收到"))
		{
			cerr<<"server.write"<<endl;
			break;
		}
		sleep(1);
		if(!server.Read())
		{
			break;
		}
		cout<<"已接收到: "<<server.Get_buffer()<<endl;
	}
	cout<<"DONE"<<endl;
	return 0;

}





