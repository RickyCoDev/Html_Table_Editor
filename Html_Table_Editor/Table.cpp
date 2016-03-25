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
	GetTable(input);
	Console::Msg* msg = new Console::Msg{};
	msg->csucc << "The table in input has this properties:"
		<< "has a layout: " + std::to_string(HasLayout())
	    << "has "+std::to_string(GetRowNumber()) + " rows"
		<< "has "+std::to_string(GetColumnNumber()) + " columns"
		<< "with a total of: " + std::to_string(GetCellNumber()) + " of cells.";
	delete msg;
	cmds->RegisterCommand("WriteRawData", std::bind(&Table::WriteRawData, this, std::placeholders::_1));
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
		Console::Msg* msg = new Console::Msg{};
		msg->cerr << "E0005 - Sorry, this is not a Html table. Please check your input.";
		msg->cerr << "Details: " + (std::string)e.what();
		delete msg;
		throw e; // prevent the program to continue without an acceptable input
	}
}

//generate the rows
void Table::PopulateRows(const std::string& input, int startPos)
{
	std::vector<std::string> StringLines = SplitAt(input, RowCloseTag); // split lines
	StringLines.erase(StringLines.begin(), StringLines.begin() + startPos); //remove all the ignored lines
	for (int i = 0; i < StringLines.size(); i++)
	{
		Row r = Row{ StringLines[i],i };
		Rows.push_back(r);
	}
}

//get table data
void Table::GetTable(const std::string& input)
{
	_input = input;
	ReplaceKnownHtmlFormattingTags();
	//msg->clog << "Tag replace result is:\n" + _input;
	try
	{
		_input = Reduce(_input, TableOpenTag, TableCloseTag);
		//msg->clog << "Table reduce result is:\n" + _input;
		PopulateRows(_input,ignorepos);
	}
	catch (const CustomExceptions::FileError& e)//ignore the line and try to check again the table
	{
		ignorepos++;

		Console::Msg* msg = new Console::Msg{};
		msg->cwarn << "Ignoring line: " + std::to_string(ignorepos);
		delete msg;

		Rows.clear(); // be sure that all row vector is clear
		GetTable(input); // try to read again the table
	}
	catch (const std::exception& e)
	{
		Console::Msg* msg = new Console::Msg{};
		msg->cerr << "E0006 - Sorry, something went wrong preparing table rows.";
		msg->cerr << "Details: " + (std::string)e.what();
		delete msg;
	}
}

int Table::GetCellNumber()
{
	int temp=0;
	for (int i = 0; i < Rows.size(); i++)
	{
		temp += Rows[i].GetCells();
	}
	return temp;
}



void Table::WriteRawData(std::vector<std::string> args)
{
	FileManager* fm = new FileManager{ FileManager::File::cleandata };
	fm->Write("RAW DATA\n\n");
	fm->Write("Extracted form a html table using Html Table Editor by RickyCoDev\n");
	fm->Write(" Copyright (c) 2016 RickyCoDev\n");
	fm->Write(" Licenced under Apache 2.0 Licence\n");
	fm->Write("Please report any issues at: https://github.com/RickyCoDev/Html_Table_Editor\n\n");
	for (int i = 0; i < Rows.size();i++)
	{
		fm->Write(Rows[i].GetRowContent(OutputKind::clean)+"\n");
	}
	delete fm;
	Console::Msg* msg = new Console::Msg{};
	if (args.size() > 0)
	{
		msg->cwarn << "This command takes no parameter(s), ignoring the current one(s).";
		args.clear();
	}
	msg->csucc << "The raw data has been written on a file next to this executable.";
	delete msg;
}