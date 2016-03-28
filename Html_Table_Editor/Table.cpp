/*
Html_Table_Editor
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include "Table.h"

Table::Table(const std::string& input)
{
	msg = new Console::Msg{};
	GetTable(input);
	std::string layout = (HasLayout()) ? "True" : "False"; //make the output more readable
	msg->csucc << "\nThe table in input has this properties:"
		<< "has a layout: " + layout
	    << "has "+std::to_string(GetRowNumber()) + " rows and "+std::to_string(GetColumnNumber()) + " columns"
		<< "with a total of: " + std::to_string(GetCellNumber()) + " of cells.";
	std::cout << "\nOk now its time to work, check the GitHub wiki to get full commands reference:\n";

	cmds->RegisterCommand("WriteRaw", std::bind(&Table::CMD_WriteRawData, this, std::placeholders::_1));
	cmds->RegisterCommand("add", std::bind(&Table::CMD_Add, this, std::placeholders::_1));
	cmds->RegisterCommand("Tprops", std::bind(&Table::CMD_TableProps, this, std::placeholders::_1));
}


Table::~Table()
{
	delete msg;
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

		msg->cwarn << "Ignoring line: " + std::to_string(ignorepos);

		Rows.clear(); // be sure that all row vector is clear
		GetTable(input); // try to read again the table
	}
	catch (const std::exception& e)
	{
		msg->cerr << "E0006 - Sorry, something went wrong preparing table rows.";
		msg->cerr << "Details: " + (std::string)e.what();
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

void Table::ReEnumRows()
{
	for (int i = 0; i < Rows.size(); i++)
		Rows[i].SetRowNumber(i);
}

void Table::CMD_WriteRawData(std::vector<std::string> args)
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

	if (args.size() > 0)
	{
		msg->cwarn << "This command takes no parameter(s), ignoring the current one(s).";
		args.clear();
	}
	msg->csucc << "The raw data has been written on a file next to this executable.";
}

void Table::CMD_Add(std::vector<std::string> args)
{
	if (args.size() < 1) throw CustomExceptions::CmdError("E0017 - Missing parameters for add command");
	if (args[0] == "row" || args[0] == "erow")
	{
		Handler_AddRowCMD(args);
		return;
	}

	//if we get here something is wrong with parametes.
	throw CustomExceptions::CmdError("E0018 - Wrong paramets");
}

void Table::Handler_AddRowCMD(std::vector<std::string>& args)
{
	int InsertPos = Rows.size(); //end of table
	if (args.size() > 2)
	{
		msg->cwarn<<"Only two paramters are required, ingoring the other one(s)";
	}

	if (args.size() > 1)
		std::stringstream{ args[1] } >> InsertPos;

	//create row with cells; same number as layout
	if (args[0] == "row")
	{
		Row r = Row{ Rows[0].GetCells() };
		AddRowAtPos(InsertPos-1, r); //-1 allows the use to not start from row 0
		return;
	}
	if (args[0] == "erow")
	{
		Row r = Row{0}; // create a row without cells
		AddRowAtPos(InsertPos-1, r);
		return;
	}
}

void Table::AddRowAtPos(unsigned pos,Row& r)
{
	if (pos < Rows.size()) // check if the row is inside the table
	{
		Rows.insert(Rows.begin() + pos, r);//unsigned cast should remove out of range
		ReEnumRows();
		msg->csucc << "Added row at pos: " + std::to_string(pos+1);
		return;
	}
	// if the row is outside or on last pos

	Rows.push_back(r);
	ReEnumRows();
	msg->csucc << "Added row at the end of table";
}

void Table::CMD_TableProps(std::vector<std::string> args)
{
	std::string layout = (HasLayout()) ? "True" : "False"; //make the output more readable
	msg->csucc << "\nThe current table has this properties:"
		<< "has a layout: " + layout
		<< "has " + std::to_string(GetRowNumber()) + " rows and " + std::to_string(GetColumnNumber()) + " columns"
		<< "with a total of: " + std::to_string(GetCellNumber()) + " of cells.";
}
