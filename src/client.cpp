/*************************************************************************
        > File Name: client.cpp
      > Author: tanfenyuan
      > Mail: tanfenyuan@outlook.com 
      > Created Time: Fri 27 Jan 2023 07:58:37 PM CST
 ************************************************************************/
#include "../include/MY_TCP.h"
#include <vector>
int main()
{
	MY_TCP::Client  client;
	std::vector<std::string> v_str;
	v_str.push_back("I Love You");
	v_str.push_back("I Love You 2");
	v_str.push_back("I Love You 3");
	v_str.push_back("I Love You 4");
	v_str.push_back("I Love You 5");
	v_str.push_back("I Love You 6");

	if(client.ConnectToSever("101.43.61.183",5000))
	{
		for(int i=0;i<4;i++)
		{
			if(!client.Write("I love you"))
			{
				break;
			}
			sleep(1);
			if(!client.Read())
			{
				break;
			}
			cout<<"Buffer: "<<client.Get_buffer()<<endl;
		}
	}
    cout<<endl<<endl<<"DONE"<<endl;
	return 0;
}
