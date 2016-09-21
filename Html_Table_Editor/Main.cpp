/*
Html_Table_Editor
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 Ricky Corte

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include<iostream>
#include"Msg.h"
#include "Common.h"
#include "Table.h"
#include "FileManager.h"
#include <sstream>

int main()
{
	bool autoOutput = false;
	Console::Msg::WelcomeMessage();
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
				Console::Msg::LogSucc( "AutoOutput is now " +status);
			}
			else
			{
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
			Console::Msg::LogError( e.what());
			args.clear(); //remove cmd buffer
		}
	}
	return 0;
}