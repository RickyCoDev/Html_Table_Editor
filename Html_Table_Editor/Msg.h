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

static class Msg
{
public:
	//normal message -> gray
	static void log(std::string Message);
	//warning message -> yellow
	static void warn(std::string Message);
	//error message -> red
	static void err(std::string Message);
	//success message -> green
	static void succ(std::string Message);

private:
	//available colors
	static enum Color { red, yellow, green, blue };

	//output string to a desired color
	static void ColoredOutput(std::string Message, Color col);


};

