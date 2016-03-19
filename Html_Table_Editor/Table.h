#pragma once
#include<iostream>
#include<string>
#include "Common.h"
#include "CustomExceptions.h"

class Table
{
private:
	//replace all html tags with custom defined tags
	void ReplaceKnownHtmlFormattingTags();
	std::string _input;
public:
	Table(const std::string& input);
	~Table();
};

