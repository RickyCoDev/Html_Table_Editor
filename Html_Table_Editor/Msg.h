/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#pragma once
#include<string>
#include<iostream>

//define cross platform colors
#if _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#define RED  "\x1b[31m"
#define GREEN  "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE  "\x1b[34m"
#define DEFAULT  "\x1b[0m"
#endif
namespace Cmsg
{
	class Msg
	{
	private:
		//available colors
		static enum Color { red, yellow, green, blue, default };

		class OutStream
		{
		private:
			std::string prefix;
			Color _col;
			//output string to a desired color
			static void ColoredOutput(std::string Message, Color col);
		public:
			OutStream& operator << (const std::string& _msg);
			OutStream(Color col);
		};

	public:
		Msg();
		OutStream clog{ Color::default }, cwarn{ Color::yellow }, cerr{ Color::red }, csucc{ Color::green };
		void WelcomeMessage();
	};

}

