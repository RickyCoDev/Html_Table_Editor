/*
Html_Table_Editor
https://github.com/rickycorte/Html_Table_Editor

Copyright (c) 2016 Ricky Corte

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#ifndef __MSG__
#define __MSG__



#pragma once
#include<string>
#include<iostream>
#include<sstream>

//define cross platform colors
#if _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#define RED  "\x1b[31m"
#define GREEN  "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define DEFAULT  "\x1b[0m"
#endif
namespace Console
{
	class IPrintable
	{
	public:
		virtual std::string ToString() = 0;

		virtual std::string operator+ (const std::string s)
		{
			return ToString() + s;
		}

		template <typename T> friend std::string operator+ (const std::string s, T& i)
		{
			return s + i.ToString();
		}

		template <typename T> friend std::ostream& operator<<(std::ostream& os, T t)
		{
			os << t.ToString();
			return os;
		}

	};

	class Msg
	{
	private:
		//available colors
		enum Color { red, yellow, green, normal };

		static void out(const std::ostringstream&, Color col= Color::normal);

	public:
		Msg();
		static void WelcomeMessage();

		template<typename T> static void Log(T& m)
		{
			std::ostringstream ss;
			ss << "**Log** " << m << std::endl;
			out(ss);
		}

		template<typename T> static void LogWarn(T& m)
		{
			std::ostringstream ss;
			ss << "**Warning** " << m << std::endl;
			out(ss,Color::yellow);
		}

		template<typename T> static void LogError(const T& m)
		{
			std::ostringstream ss;
			ss << "**Error** " << m << std::endl;
			out(ss, Color::red);
		}
		template<typename T> static void LogSucc(const T& m)
		{
			std::ostringstream ss;
			ss << m << std::endl;
			out(ss, Color::green);
		}
	};

}

#endif // !__MSG__

