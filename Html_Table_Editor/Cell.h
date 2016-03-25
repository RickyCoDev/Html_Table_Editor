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
#include"Common.h"
#include "FileManager.h"

class Cell
{
private:
	std::string content;
	int CellNumber;


public:
	Cell(const std::string& input, const int cellNumber);
	~Cell();
	std::string GetContent() { return content; }
	int GetCellNumber() { return CellNumber; }
	//get the content with a open and close tag
	std::string GetContentForOutPut(OutputKind kind, bool isLayout);

};

