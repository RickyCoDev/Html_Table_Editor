#include "Msg.h"

void Msg::ColoredOutput(std::string Message, Color col)
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
	case Color::blue:
		SetConsoleTextAttribute(h, 9);
		break;
	}
	std::cout << Message;
	//reset default message color
	SetConsoleTextAttribute(h, 7);
#else
	switch (col)
	{
	case Color::red:
		printf(RED  "%s"  DEFAULT, Message.c_str());
		break;
	case Color::yellow:
		printf(YELLOW  "%s"  DEFAULT, Message.c_str());
		break;
	case Color::green:
		printf(GREEN  "%s"  DEFAULT, Message.c_str());
		break;
	case Color::blue:
		printf(BLUE  "%s"  DEFAULT, Message.c_str());
		break;
	}
#endif	
}

void Msg::log(std::string Message)
{
	std::cout <<"**LOG** "<< Message;
}

void Msg::warn(std::string Message)
{
	Message = "**WARNING** " + Message;
	ColoredOutput(Message, Color::yellow);
}

void Msg::err(std::string Message)
{
	Message = "**ERROR**" + Message;
	ColoredOutput(Message, Color::red);
}

void Msg::succ(std::string Message)
{
	ColoredOutput(Message, Color::green);
}
