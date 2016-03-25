/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Common.h"
#include "CustomExceptions.h"
#include "Row.h";

class Table
{
private:
	std::string _input;
	std::vector<Row> Rows;
	int ignorepos = 0;
	//replace all html tags with custom defined tags
	void ReplaceKnownHtmlFormattingTags();
	//generate the rows
	void PopulateRows(const std::string& input, int startPos);
	//get table content
	void GetTable(const std::string& input);
public:
	Table(const std::string& input);
	~Table();

	int GetRowNumber() { return Rows.size(); }
	int GetColumnNumber() { return Rows[0].GetCells(); }
	int GetCellNumber();
	bool HasLayout() { return Rows[0].RowIsLayout(); }

	void WriteRawData(std::vector<std::string> args); //paste the raw data on a file
	void WriteOutput(); //creates the new table

};

