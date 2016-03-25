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
	Console::Msg* msg = new Console::Msg{};
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
		msg->cerr << "An empty cell will be created!";
		content = "";
	}

	msg->clog << "Cell " + std::to_string(cellNumber+1) + ":\n" + content;
	delete msg;
}


Cell::~Cell()
{
}

std::string Cell::GetContentForOutPut(OutputKind kind, bool isLayout)
{
	std::string OpenTag, CloseTag;
	switch (kind)
	{
	case OutputKind::clean:
		OpenTag = ""; CloseTag = " |";
		break;
	case OutputKind::normal:
		if (isLayout)
		{
			OpenTag = "<th>"; CloseTag = "</th>";
		}
		else
		{
			OpenTag = "<td>"; CloseTag = "</td>";
		}
		break;
	}
	return OpenTag + content + CloseTag;
}
