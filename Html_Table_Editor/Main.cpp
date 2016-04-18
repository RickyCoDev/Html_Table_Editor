/*
Html_Table_Editor
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
#include <sstream>
//Cmsg::Msg* msg = new Cmsg::Msg{};

int main()
{
	bool autoOutput = false;
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
	std::string CurCmd;
	while (m != "quit")
	{
	   std::getline(std::cin, m);// fill the input vector with command and args
	   std::stringstream s{ m };
	   while (s >> m)
	   {
		   //msg->clog << "-" + m + "-";
		   args.push_back(m);
	   }

		//seach for command
		try 
		{
			CurCmd = args[0]; // get the command that is stored in the first pos
			args.erase(args.begin(), args.begin() + 1); // remove 1st element. It's not a arg

			if (CurCmd == "autoput")
			{
				autoOutput = !autoOutput;
				args.clear();
				std::string status = autoOutput ? "active" : "disabled";
				msg->csucc << "AutoOutput is now " +status;
			}
			else
			{
				//msg->clog << "Current cmd: "+CurCmd+" has " + std::to_string(args.size())+" args";
				cmds->RunCommand(CurCmd, args); // not able to handle parameter for the moment

				args.clear(); //remove cmd buffer

				if (autoOutput && CurCmd != "quit" )
				{
					cmds->RunCommand("WriteRaw", args);
					cmds->RunCommand("output", args);
				}
			}


		}
		catch (const std::exception& e)
		{
			msg->cerr<<e.what();
			args.clear(); //remove cmd buffer
		}
	}
	delete msg;
	return 0;
}