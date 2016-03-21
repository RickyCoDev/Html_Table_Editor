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
	//msg->clog << "Tag replace result is:\n" + _input;
	try 
	{
		_input = Reduce(_input, TableOpenTag, TableCloseTag); 
		msg->clog << "Table reduce result is:\n" + _input;
		PopulateRows(_input);
	}
	catch (const std::exception& e)
	{
		msg->cerr << "E0006 - Sorry, something went wrong preparing table rows.";
		msg->cerr << "Details: " + (std::string)e.what();
	}

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
		_input = Replace(_input, "</td", CellCloseTag);
	}
	catch (const std::exception& e)
	{
		msg->cerr << "E0005 - Sorry, this is not a Html table. Please check your input.";
		msg->cerr << "Details: " + (std::string)e.what();
		throw e; // prevent the program to continue without an acceptable input
	}
}

void Table::PopulateRows(const std::string& input)
{
	std::vector<std::string> StringLines = SplitAt(input, RowCloseTag); // split lines

	for (int i = 0; i < StringLines.size(); i++)
	{
		Row r = Row{ StringLines[i],i };
		Rows.push_back(r);
	}
}