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
#include<sstream>
#include"Common.h"
class Cell
{
private:
	std::string content;

public:
	Cell();
	~Cell();
	std::string GetContent() { return content; }

};

