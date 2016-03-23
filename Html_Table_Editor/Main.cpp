/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include<iostream>
#include"Msg.h"
#include "Common.h"
#include "Table.h"
#include "FileManager.h"
//Cmsg::Msg* msg = new Cmsg::Msg{};

int main()
{
	Console::Msg* msg = new Console::Msg{};
	msg->WelcomeMessage();
	try 
	{
		FileManager* fm = new FileManager();
		std::string target = fm->ReadFromFile("htmlExampleTable.txt");
		Table* table = new Table{ target };
	}
	catch (const std::exception& e)
	{
		std::string m;
		std::cin >> m;
		return 1;
	}

	std::string m;
	std::vector<std::string> args;
	//Commands* cmds = new Commands{};
	while (m != "quit")
	{
		std::cin >> m;
		//seach for command
		try 
		{
			cmds->RunCommand(m,args); // not able to handle parameter for the moment
		}
		catch (const std::exception& e)
		{
			msg->cerr<<e.what();
		}
	}
	delete msg;
	return 0;
}