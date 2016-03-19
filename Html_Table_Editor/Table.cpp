/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include "Table.h"

Table::Table(const std::string& input)
{
	_input = input;
	ReplaceKnownHtmlFormattingTags();

	msg->clog <<"The result is:\n"+ _input;
}


Table::~Table()
{
}

void Table::ReplaceKnownHtmlFormattingTags()
{
	try
	{
		_input = Replace(_input, "<table", TableOpenTag);
		_input = Replace(_input, "</table", TableCloseTag);

		_input = Replace(_input, "<th", HCellOpenTag);
		_input = Replace(_input, "</th", HCellCloseTag);

		_input = Replace(_input, "<tr", RowOpenTag);
		_input = Replace(_input, "</tr", RowCloseTag);

		_input = Replace(_input, "<td", CellOpenTag);
		_input = Replace(_input, "</td", CellOpenTag);
	}
	catch (const std::exception& e)
	{
		msg->cerr << "Sorry, this is not a Html table. Please check your input.";
		msg->cerr << "Details: " + (std::string)e.what();
		throw e; // prevent the program to continue without an acceptable input
	}
}