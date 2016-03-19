#include<iostream>
#include"Msg.h"
#include "Common.h"
#include "Table.h"
//Cmsg::Msg* msg = new Cmsg::Msg{};

int main()
{
	std::cout << "Normal Message\n";
	std::string Example = "<td class='blabla' ><center>Ciao sono matio</center>";
	std::string Example2 = "<table><tr><th>1a<br></th><th>1b<br></th><th>1c<br></th><th>1d</th><th>1e<br></th></tr><tr><td>2a</td><td>2b<br></td><td>2c<br></td><td>2d</td><td>2e<br></td></tr></table>";

	std::string target = Example2; // change this line to change test input
	msg->clog << "Example string: " + target+"\n";
	try 
	{
		Table* table = new Table{ target };
	}
	catch (const std::exception& e)
	{
		std::string m;
		std::cin >> m;
		return 1;
	}


	std::string m;
	std::cin >> m;
	return 0;
}