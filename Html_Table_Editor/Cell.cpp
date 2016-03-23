/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include "Cell.h"

Cell::Cell(const std::string& input,const int cellNumber) : CellNumber(cellNumber)
{
	try
	{
		if (CheckForPresence(input,CellOpenTag))
			content = Reduce(input, CellOpenTag + ">", CellCloseTag);
		else
			content = Reduce(input, HCellOpenTag + ">", HCellCloseTag);
	}
	catch (const std::exception& e)
	{
		msg->cerr << "E0008 - Sorry, something went wrong reading cell "+ std::to_string(cellNumber) +".";
		msg->cerr << "Details: " + (std::string)e.what();
	}

	msg->clog << "Cell " + std::to_string(cellNumber) + ":\n" + content;
}


Cell::~Cell()
{
}

