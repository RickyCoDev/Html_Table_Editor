#include<iostream>
#include"Msg.h"
#include"Common.h"

//Cmsg::Msg* msg = new Cmsg::Msg{};

int main()
{
	std::cout << "Normal Message\n";
	msg->clog << "Pig";
	msg->cwarn << "hello";
	msg->cerr << "D'ho";
	msg->csucc << "This is the end!";
	std::string m;
	std::cin >> m;
	return 0;
}