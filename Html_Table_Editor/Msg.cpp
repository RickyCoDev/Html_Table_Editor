/*
Html_Table_Editor
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 Ricky Corte

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include "Msg.h"

Console::Msg::Msg() {};

void Console::Msg::out(const std::ostringstream& ss, Color col)
{
	//platform dependent compilation to grant cross platform colors
#if _WIN32
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	//set color based on requested
	switch (col)
	{
	case Color::red:
		SetConsoleTextAttribute(h, 4);
		break;
	case Color::yellow:
		SetConsoleTextAttribute(h, 14);
		break;
	case Color::green:
		SetConsoleTextAttribute(h, 10);
		break;
	}
	std::cout<<ss.str();
	//reset default message color
	SetConsoleTextAttribute(h, 7);
#else
	switch (col)
	{
	case Color::red:
		printf(RED  "%s"  DEFAULT, ss.str());
		break;
	case Color::yellow:
		printf(YELLOW  "%s"  DEFAULT, ss.str());
		break;
	case Color::green:
		printf(GREEN  "%s"  DEFAULT, ss.str());
		break;
	}
#endif	
}


void Console::Msg::WelcomeMessage()
{
	LogSucc("Html Table Editor\n");
	LogSucc("https://github.com/rickycorte/Html_Table_Editor");
	LogSucc("Copyright (c) 2016 Ricky Corte");
	LogSucc("Licenced under Apache 2.0 Licence\n");
}

