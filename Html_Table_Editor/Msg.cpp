/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include "Msg.h"

Cmsg::Msg::Msg() {};

void Cmsg::Msg::OutStream::ColoredOutput(std::string Message, Color col)
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


Cmsg::Msg::OutStream::OutStream(Color col)
{
	_col = col;
	switch (col)
	{
	case Cmsg::Msg::red:
		prefix = "**Error** ";
		break;
	case Cmsg::Msg::yellow:
		prefix = "**Warning** ";
		break;
	case Cmsg::Msg::default:
		prefix = "**Log** ";
		break;
	default:
		break;
	}
}

Cmsg::Msg::OutStream& Cmsg::Msg::OutStream::operator<< (const std::string& _msg)
{
	if (_col != Color::default)
		ColoredOutput(prefix+_msg+"\n", _col);
	else
		std::cout << prefix<< _msg <<"\n";
	return *this;
}


