/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/
#include "Row.h"

Row::Row(const std::string& input, const int rowNumber) : RowNumber(rowNumber)
{
	std::string _input = input;
	//input = Reduce(input, ">",""); // remove the open tag part
	msg->clog << "Row " + std::to_string(RowNumber) + ":\n ";
	try 
	{
		PopulateCells(_input);
	}
	catch (const std::exception& e)
	{
		msg->cerr << "E0007 - Sorry, something went wrong reading table rows.";
		msg->cerr << "Details: " + (std::string)e.what();
	}
}

Row::~Row()
{
}

void Row::PopulateCells(std::string input)
{
	std::vector<std::string> Parts;
	if (CheckForPresence(input, CellCloseTag)) // normal line
	{
		Parts = SplitAt(input, CellCloseTag);
	}
	else
	{
		//layout line
		Parts = SplitAt(input, HCellCloseTag);
		if(RowNumber == 0)
		isLayout = true;
		else
		{
			throw CustomExceptions::ReadError("E0009 - Table layout can't be declared in row that is not the 1st.");
		}
	}
	for (int i = 0; i < Parts.size(); i++)
	{
		Cell c = Cell{ Parts[i],i };
		Cells.push_back(c);
	}
}
