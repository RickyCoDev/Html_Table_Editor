#pragma once
#include<string>
#include<iostream>
#include<sstream>
#include"Common.h"
class Cell
{
private:
	std::string content;
	bool isLayout = false;

	std::string CustomCloseTag = "|cq|";


public:
	Cell();
	~Cell();

	Cell& operator>> (std::string& val);
	std::string GetContent() { return content; }

};

