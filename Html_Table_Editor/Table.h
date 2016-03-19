/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

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

