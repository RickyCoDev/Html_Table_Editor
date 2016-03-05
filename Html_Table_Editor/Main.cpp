#include<iostream>
#include"Msg.h"
#include"Common.h"
#include "Cell.h"
//Cmsg::Msg* msg = new Cmsg::Msg{};

int main()
{
	std::cout << "Normal Message\n";
	std::string Example = "<td class='blabla' ><center>Ciao sono matio</center></td>";
	msg->clog << "Example string: " + Example;
	Cell* cell = new Cell{};
	InsertCustomTags(Example);
	msg->clog << Example;
	*cell >> Example;

	msg->csucc << cell->GetContent();

	std::string m;
	std::cin >> m;
	return 0;
}