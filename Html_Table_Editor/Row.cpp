/*
Html_Table_Editor
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/
#include "Row.h"

Row::Row(const std::string& input, const int rowNumber) : RowNumber(rowNumber)
{
	std::string _input = input;
	Console::Msg* msg = new Console::Msg{};
	//input = Reduce(input, ">",""); // remove the open tag part
	msg->clog << "Row " + std::to_string(RowNumber+1) + ":\n ";
	try 
	{
		PopulateCells(_input);
	}
	catch (const CustomExceptions::FileError& e)
	{
		msg->cerr << "E0014 - Sorry, wrong row formatting.";
		msg->cerr << "Details: " + (std::string)e.what();
		delete msg;
		throw e;
	}
	catch (const std::exception& e)
	{
		msg->cerr << "E0007 - Sorry, something went wrong reading table row.";
		msg->cerr << "Details: " + (std::string)e.what();
	}
	delete msg;
}

Row::Row(int cells)
{
	for (int i=0; i < cells;i++)
	{
		Cell c = Cell{};
		Cells.push_back(c);
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

	if (CheckForPresence(input, HCellCloseTag)) // layout line
	{
		//layout line
		Parts = SplitAt(input, HCellCloseTag);
		if (RowNumber == 0)
			isLayout = true;
		else
		{
			throw CustomExceptions::ReadError("E0009 - Table layout can't be declared in row that is not the 1st.");
		}
	  }

	if (!CheckForPresence(input, HCellCloseTag) && !CheckForPresence(input, CellCloseTag)) // this is a empty row
	{
		if (RowNumber == 0)
			throw CustomExceptions::FileError("E00013 - First line can't be empty!"); // different error solution
		throw CustomExceptions::ReadError("E0012 - This row is empty!");

	}
	//TODO: create a empty line

	for (int i = 0; i < Parts.size(); i++)
	{
		Cell c = Cell{ Parts[i],i };
		Cells.push_back(c);
	}
}

std::string Row::GetRowContent(OutputKind kind)
{
	std::string OpenTag,CloseTag,temp;
	switch (kind)
	{
	case OutputKind::clean:
		OpenTag = "Row "+std::to_string(RowNumber+1)+": |"; CloseTag = "";
		break;
	case OutputKind::normal: //TODO: add style string for rows
		OpenTag = "<tr>";  CloseTag = "</tr>";
		break;
	}
	temp += OpenTag;
	for (int i = 0; i < Cells.size(); i++)
	{
		temp += Cells[i].GetContentForOutPut(kind, isLayout);
	}
	temp += CloseTag;
	return temp;

}

void Row::AddEmptyCell(unsigned pos)
{
	if (Cells.size() == 0) return; //don't add cells to empty rows
	Cell c = Cell{};

	if (pos > Cells.size()) // check for out of table
		pos = Cells.size();

	Cells.insert(Cells.begin() + pos, c);
	ReEnumCells();
}

void Row::ReEnumCells()
{
	for (int i = 0; i < Cells.size(); i++)
	{
		Cells[i].SetCellNumber(i);
	}
}

void Row::RemoveCell(unsigned pos)
{
	if (pos < Cells.size())
	Cells.erase(Cells.begin() + pos);
	ReEnumCells();
}

void Row::SetCellContent(unsigned Cpos, std::string newContent)
{
	if (Cpos+1 > Cells.size())
	{
		Console::Msg* msg = new Console::Msg{};
		msg->cwarn << "The row "+std::to_string(RowNumber+1)+" has a null cell at: "+std::to_string(Cpos+1)+", filling row with empty cells";
		delete msg;
		FillWithEmptyCells(Cpos + 1 - Cells.size());
	}

	Cells[Cpos].SetContent(newContent);
}

void Row::SetAllCellsContent(std::string newContent)
{
	for (int i = 0; i < Cells.size(); i++)
	{
		Cells[i].SetContent(newContent);
	}
}

void Row::FillWithEmptyCells(unsigned cellNumber)
{
	for (int i = 0; i < cellNumber; i++)
	{
		Cell c = Cell{};
		Cells.push_back(c);
	}
}