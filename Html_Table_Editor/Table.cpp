/*
Html_Table_Editor
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 Ricky Corte

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include "Table.h"

Table::Table(const std::string& input)
{
	GetTable(input);
	//print table properties
	std::string layout = (HasLayout()) ? "True" : "False"; //make the output more readable
	Console::Msg::LogSucc("\nThe table in input has this properties:");
	Console::Msg::LogSucc("has a layout: " + layout);
	Console::Msg::LogSucc("has " + std::to_string(GetRowNumber()) + " rows and " + std::to_string(GetColumnNumber()) + " columns");
	Console::Msg::LogSucc("with a total of: " + std::to_string(GetCellNumber()) + " of cells.");
	std::cout << "\nOk now its time to work, check the GitHub wiki to get full commands reference:\n";

	_input = ""; //clear usless values to free some ram

	//register all console commands and set their handlers
	cmds->RegisterCommand("WriteRaw", std::bind(&Table::CMD_WriteRawData, this, std::placeholders::_1));
	cmds->RegisterCommand("output", std::bind(&Table::CMD_WriteOutput, this, std::placeholders::_1));
	cmds->RegisterCommand("add", std::bind(&Table::CMD_Add, this, std::placeholders::_1));
	cmds->RegisterCommand("Tprops", std::bind(&Table::CMD_TableProps, this, std::placeholders::_1));
	cmds->RegisterCommand("rm", std::bind(&Table::CMD_Rm, this, std::placeholders::_1));
	cmds->RegisterCommand("set", std::bind(&Table::CMD_Set, this, std::placeholders::_1));
	cmds->RegisterCommand("edit", std::bind(&Table::CMD_Set, this, std::placeholders::_1));
	cmds->RegisterCommand("join", std::bind(&Table::CMD_Join, this, std::placeholders::_1));
	cmds->RegisterCommand("lineup", std::bind(&Table::CMD_LineUp, this, std::placeholders::_1));
	cmds->RegisterCommand("style", std::bind(&Table::CMD_Style, this, std::placeholders::_1));
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
		Console::Msg::LogError( "E0005 - Sorry, this is not a Html table. Please check your input.");
		Console::Msg::LogError("Details: " + (std::string)e.what());
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
	try
	{
		_input = Reduce(_input, TableOpenTag, TableCloseTag);
		PopulateRows(_input,ignorepos);
	}
	catch (const CustomExceptions::FileError& e)//ignore the line and try to check again the table
	{
		ignorepos++;

		Console::Msg::LogWarn("Ignoring line: " + std::to_string(ignorepos));

		Rows.clear(); // be sure that all row vector is clear
		GetTable(input); // try to read again the table
	}
	catch (const std::exception& e)
	{
		Console::Msg::LogError("E0006 - Sorry, something went wrong preparing table rows.");
		Console::Msg::LogError("Details: " + (std::string)e.what());
	}
}

int Table::GetCellNumber()
{
	int temp=0;
	for (int i = 0; i < Rows.size(); i++)
	{
		temp += Rows[i].GetCellsCount();
	}
	return temp;
}

void Table::ReEnumRows()
{
	for (int i = 0; i < Rows.size(); i++)
	{
		Rows[i].SetRowNumber(i);
	}
}

void Table::CMD_WriteRawData(std::vector<std::string> args)
{
	FileManager* fm = new FileManager{ FileManager::File::cleandata };
	fm->Write("RAW DATA\n\n");
	fm->Write("Extracted form a html table using Html Table Editor by RickyCoDev\n");
	fm->Write(" Copyright (c) 2016 Ricky Corte\n");
	fm->Write(" Licenced under Apache 2.0 Licence\n");
	fm->Write("Please report any issues at: https://github.com/rickycorte/Html_Table_Editor");
	fm->Write("\n\nNote: The watermark above can be removed.\n Giving attribution is not required, but is greatly appreciated!\n\n");
	for (int i = 0; i < Rows.size();i++)
	{
		fm->Write(Rows[i].GetRowContent(OutputKind::clean)+"\n");
	}
	delete fm;

	if (args.size() > 0)
	{
		Console::Msg::LogWarn("This command takes no parameter(s), ignoring the current one(s).");
		args.clear();
	}
	Console::Msg::LogSucc("The raw data has been written on a file next to this executable.");
}

void Table::CMD_WriteOutput(std::vector<std::string> args)
{
	FileManager* fm = new FileManager{ FileManager::File::output };
	fm->Write("<html><body>");
	fm->Write("<h1><center>HTML5 OUTPUT</center></h1>\n\n");
	fm->Write("<p>This tables has been generated with Html Table Editor by RikcyCorte</p>");
	fm->Write("<p> Copyright (c) 2016 RickyCoDev</p>");
	fm->Write("<p> Licenced under Apache 2.0 Licence</p>");
	fm->Write("<p>Please report any issues <a href=https://github.com/rickycorte/Html_Table_Editor>here</a></p>");
	fm->Write("<p>Note: The watermark above can be removed.<br>Giving attribution is not required, but is greatly appreciated!</p><br/><br/>\n\n");
	fm->Write("<table"+style+">");
	for (int i = 0; i < Rows.size(); i++)
	{
		fm->Write(Rows[i].GetRowContent(OutputKind::normal) + "\n");
	}
	fm->Write("</table></body></html>");
	delete fm;
	
	if (args.size() > 0)
	{
		Console::Msg::LogWarn("This command takes no parameter(s), ignoring the current one(s).");
		args.clear();
	}
	Console::Msg::LogSucc("The output has been written on 'output.html' file next to this executable.");
}

void Table::URemoveFirstArg(std::vector<std::string>& args)
{
	args.erase(args.begin());
}

void Table::CMD_Add(std::vector<std::string> args)
{
	if (args.size() < 1) throw CustomExceptions::CmdError("E0017 - Missing parameters for add command");
	
	//call row handler
	if (args[0] == "row" || args[0] == "erow")
	{
		Handler_AddRowCMD(args);
		return;
	}
	//call column handler
	if (args[0] == "col")
	{
		URemoveFirstArg(args);
		Handler_AddColumnCMD(args);
		return;
	}

	//if we get here something is wrong with parametes.
	throw CustomExceptions::CmdError("E0018 - Wrong paramets");
}

void Table::Handler_AddRowCMD(std::vector<std::string>& args)
{
	int InsertPos = Rows.size()+1; //end of table, +1 is required because later this number ios decreased by 1
	if (args.size() > 2)
	{
		Console::Msg::LogWarn("Only one paramter is required, ingoring the other one(s)");
	}

	if (args.size() > 1)
		std::stringstream{ args[1] } >> InsertPos;

	if (InsertPos < 2)
	{
		Console::Msg::LogWarn("You can't put a row before layout! Moving new row to fist available line.");
		InsertPos=2;
	}

	//create row with cells; same number as layout
	if (args[0] == "row")
	{
		Row r = Row{ Rows[0].GetCellsCount() };
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

void Table::Handler_AddColumnCMD(std::vector<std::string>& args)
{
	if(args.size()>1) Console::Msg::LogWarn("Only one paramter is required, ingoring the other one(s)");

	unsigned pos = Rows[0].GetCellsCount();
	if (args.size() > 0)
	{
		std::stringstream{ args[0] } >> pos;
	}
	AddEmptyColumnAtPos(pos);
}


void Table::AddRowAtPos(unsigned pos,Row& r)
{
	if (pos < Rows.size()) // check if the row is inside the table
	{
		Rows.insert(Rows.begin() + pos, r);//unsigned cast should remove out of range
		ReEnumRows();
		Console::Msg::LogSucc("Added row at pos: " + std::to_string(pos+1));
		return;
	}
	// if the row is outside or on last pos

	Rows.push_back(r);
	ReEnumRows();
	Console::Msg::LogSucc("Added row at the end of table");
}

void Table::AddEmptyColumnAtPos(unsigned pos)
{
	if (pos > Rows[0].GetCellsCount()) pos = Rows[0].GetCellsCount()+1;

	for (int i = 0; i < Rows.size(); i++)
	{
		Rows[i].AddEmptyCell(pos-1);
	}
	Console::Msg::LogError("Added empty column at: " + std::to_string(pos+1));
}

void Table::CMD_TableProps(std::vector<std::string> args)
{
	std::string layout = (HasLayout()) ? "True" : "False"; //make the output more readable
	Console::Msg::LogSucc("\nThe current table has this properties:");
	Console::Msg::LogSucc("has a layout: " + layout);
	Console::Msg::LogSucc("has " + std::to_string(GetRowNumber()) + " rows and " + std::to_string(GetColumnNumber()) + " columns");
	Console::Msg::LogSucc("with a total of: " + std::to_string(GetCellNumber()) + " of cells.");
}

void Table::CMD_Rm(std::vector<std::string> args)
{
	if(args.size() < 1)  throw CustomExceptions::CmdError("E0017 - Missing parameters for rm command");

	if (args[0] == "row")
	{
		URemoveFirstArg(args);
		Handler_RemoveRowCMD(args);
		return;
	}
	if (args[0] == "col")
	{
		URemoveFirstArg(args);
		Handler_RemoveColumnCMD(args);
		return;
	}

	//if we get here something is wrong with parametes.
	throw CustomExceptions::CmdError("E0018 - Wrong paramets");
}

void Table::Handler_RemoveRowCMD(std::vector<std::string>& args)
{
	unsigned RmPos = Rows.size();
	if (args.size() > 1) Console::Msg::LogWarn("Only one paramter is required, ingoring the other one(s)");
	if (args.size() > 0)
		std::stringstream{ args[0] } >> RmPos;
	RemoveRow(RmPos-1); // remove 1 to translate to machine position
}

void Table::RemoveRow(unsigned pos)
{
	if (Rows.size() == 1) throw CustomExceptions::CmdError("E0019 - You can't delete all the table");
	if (pos > Rows.size()) pos = Rows.size()-1;
	Rows.erase(Rows.begin() + pos);
	ReEnumRows();
	Console::Msg::LogSucc("Removed row at: " + std::to_string(pos+1));
}

void Table::Handler_RemoveColumnCMD(std::vector<std::string>& args)
{
	unsigned RmPos = Rows[0].GetCellsCount();
	if (args.size() > 1) Console::Msg::LogWarn("Only one paramter is required, ingoring the other one(s)");
	if (args.size() > 0)
		std::stringstream{ args[0] } >> RmPos;
	RemoveColumn(RmPos - 1); // remove 1 to translate to machine position
}

void Table::RemoveColumn(unsigned pos)
{
	if(Rows[0].GetCellsCount() == 1) throw CustomExceptions::CmdError("E0019 - You can't delete all the table");
	if (pos > Rows[0].GetCellsCount()) pos = Rows[0].GetCellsCount() - 1;
	for (int i = 0; i < Rows.size(); i++)
	{
		Rows[i].RemoveCell(pos);
	}
	Console::Msg::LogSucc("Removed column at: " + std::to_string(pos + 1));
}

std::string Table::UGetAllArgsInString(std::vector<std::string>& args)
{
	std::string temp;
	for (int i = 0; i < args.size(); i++)
	{
		if (i == 0)
			temp += args[i];
		else
		{
			temp += " " + args[i];
		}
	}
	return temp;
}

void Table::CMD_Set(std::vector<std::string> args)
{
	//these 2 commands need less parameter
	if (args.size() < 2) throw CustomExceptions::CmdError("E0017 - Missing parameters for set command");

	if (args[0] == "all")
	{
		URemoveFirstArg(args);
		Handler_SetAllContentCMD(args);
		return;
	}

	if (args.size() < 3) throw CustomExceptions::CmdError("E0017 - Missing parameters for set command");

	if (args[0] == "row")
	{
		URemoveFirstArg(args);
		Handler_SetRowContentCMD(args);
		return;
	}
	if (args[0] == "col")
	{
		URemoveFirstArg(args);
		Handler_SetColumnContentCMD(args);
		return;
	}

	if (args.size() < 4) throw CustomExceptions::CmdError("E0017 - Missing parameters for set command");

	if (args[0] == "cell")
	{
		URemoveFirstArg(args);
		Handler_SetCellContentCMD(args);
		return;
	}
	//if we get here something is wrong with parametes.
	throw CustomExceptions::CmdError("E0018 - Wrong paramets");
}

void Table::Handler_SetRowContentCMD(std::vector<std::string>& args)
{
	int Pos = -1; // -1 = fail status
	std::stringstream{ args[0] } >> Pos;
	Pos -= 1; // translate to machine pos
	if (Pos <0 || Pos >= Rows.size()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");

	URemoveFirstArg(args); // remove the number
	std::string newContent = UGetAllArgsInString(args);
	if (Rows[Pos].IsEmpty())
		Rows[Pos].FillWithEmptyCells(Rows[0].GetCellsCount());
	Rows[Pos].SetAllCellsContent(newContent);

	Console::Msg::LogSucc("The content of row " + std::to_string(Pos + 1) + " is set to: `" + newContent + "`");
}

void Table::Handler_SetColumnContentCMD(std::vector<std::string>& args)
{
	int pos = -1;
	std::stringstream{ args[0] } >> pos;
	pos -= 1;
	if(pos<0 || pos>= Rows[0].GetCellsCount()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");

	URemoveFirstArg(args); // remove the number
	std::string newContent = UGetAllArgsInString(args);
	for (int i = 0; i < Rows.size(); i++)
	{
		if(!Rows[i].IsEmpty()) // ignore empty lines
		   Rows[i].SetCellContent(pos, newContent);
	}
	Console::Msg::LogSucc("The content of column " + std::to_string(pos + 1) +" is set to: `" + newContent + "`");
}

void Table::Handler_SetAllContentCMD(std::vector<std::string>& args)
{
	std::string newContent = UGetAllArgsInString(args);
	for (int i = 0; i < Rows.size(); i++)
	{
		if (Rows[i].IsEmpty()) Rows[i].FillWithEmptyCells(Rows[0].GetCellsCount());
		Rows[i].SetAllCellsContent(newContent);
	}
	Console::Msg::LogSucc("The content of all the cells is set to: `" + newContent + "`");
}

void Table::Handler_SetCellContentCMD(std::vector<std::string>& args)
{
	int Rpos=-1, Cpos=-1;

	std::stringstream{ args[0] } >> Rpos; // read row pos
	Rpos -= 1;
	URemoveFirstArg(args); // remove the row number
	std::stringstream{ args[0] } >> Cpos; // read col pos;
	Cpos -= 1;
	URemoveFirstArg(args);

	//check for invalid position
	if (Rpos<0 || Rpos>= Rows.size()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");
	if (Cpos<0 || Cpos>= Rows[0].GetCellsCount()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");

	std::string newContent = UGetAllArgsInString(args);
	Rows[Rpos].SetCellContent(Cpos, newContent);

	Console::Msg::LogSucc("The content of the cell (" + std::to_string(Rpos + 1) + ";" + std::to_string(Cpos + 1) + ") is set to: `" + newContent + "`");
}

void Table::CMD_Join(std::vector<std::string> args)
{
	if (args.size() < 4) throw CustomExceptions::CmdError("E0017 - Missing parameters for set command");
	if (args[0] == "rows")
	{
		URemoveFirstArg(args);
		//call handler
		Handler_JoinRows(args);
		return;
	}
	if (args[0] == "cols")
	{
		URemoveFirstArg(args);
		//call handler
		Handler_JoinColumns(args);
		return;
	}

	//if we get here something is wrong with parametes.
	throw CustomExceptions::CmdError("E0018 - Wrong paramets");
}

void Table::Handler_JoinRows(std::vector<std::string>& args)
{
	int row1 = -1, row2 = -1;
	std::stringstream{ args[0] } >> row1;
	row1 -= 1;
	URemoveFirstArg(args);
	std::stringstream{ args[0] } >> row2;
	row2 -= 1;
	URemoveFirstArg(args);

	if(row1<0 || row1 >= Rows.size()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");
	if (row2<0 || row2 >= Rows.size()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");
	if (row1 == row2) throw CustomExceptions::CmdError("E0021 - You can't join the same element!");

	std::string content = UGetAllArgsInString(args);
	JoinRows(row1, row2, content);

	RemoveRow(row2); // remove the second row. Comment this line if want to keep the second one
	Console::Msg::LogSucc("Row " + std::to_string(row2 + 1) + " has been added to row " + std::to_string(row1 + 1) + " with this pattern: '" + content+"'");
}

void Table::Handler_JoinColumns(std::vector<std::string>& args)
{
	int col1 = -1, col2 = -1;
	std::stringstream{ args[0] } >> col1;
	col1 -= 1;
	URemoveFirstArg(args);
	std::stringstream{ args[0] } >> col2;
	col2 -= 1;
	URemoveFirstArg(args);

	if (col1<0 || col1 >= Rows.size()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");
	if (col2<0 || col2 >= Rows.size()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");
	if (col1 == col2) throw CustomExceptions::CmdError("E0021 - You can't join the same element!");

	std::string content = UGetAllArgsInString(args);
	JoinColumns(col1, col2, content);
	RemoveColumn(col2);
	Console::Msg::LogSucc("Column " + std::to_string(col2 + 1) + " has been added to column " + std::to_string(col1 + 1) + " with this pattern: '" + content + "'");
}

void Table::JoinRows(unsigned row1, unsigned row2, std::string newContent)
{
	for (int i = 0; i < Rows[row1].GetCellsCount(); i++)
	{
		Rows[row1].JoinCellContent(i, newContent, Rows[row2].GetCellContent(i));
	}
}

void Table::JoinColumns(unsigned col1, unsigned col2, std::string newContent)
{
	for (int i = 0; i < Rows.size(); i++)
	{
		Rows[i].JoinCellContent(col1, newContent, Rows[i].GetCellContent(col2));
	}
}

void Table::CMD_LineUp(std::vector<std::string> args)
{
	if (args.size() > 0) Console::Msg::LogWarn("No paramter is required, ingoring the other one(s)");
	int LayoutCellCount = Rows[0].GetCellsCount();
	for (int i = 0; i < Rows.size(); i++)
	{
		if (Rows[i].GetCellsCount() != LayoutCellCount )
		{
			//add empty cells
			if (Rows[i].GetCellsCount() < LayoutCellCount)
			{
				Console::Msg::Log("Filling row: " + std::to_string(i + 1));
				Rows[i].FillWithEmptyCells(LayoutCellCount - Rows[i].GetCellsCount());
			}
			//remove cels
			if (Rows[i].GetCellsCount() > LayoutCellCount)
			{
				Console::Msg::Log("Removing elements from row: " + std::to_string(i + 1));
				while (Rows[i].GetCellsCount() != LayoutCellCount)
				{
					Rows[i].RemoveCell(Rows[i].GetCellsCount() - 1);
				}
			}
		}
	}
	Console::Msg::LogSucc("The table has been lined up.");
}

void Table::CMD_Style(std::vector<std::string> args)
{
	if (args.size() < 2) throw CustomExceptions::CmdError("E0017 - Missing parameters for set command");

	if (args[0] == "table")
	{
		URemoveFirstArg(args);
		//call handler
		Handler_SetTableStyle(args);
		return;
	}
	if (args[0] == "allrows")
	{
		URemoveFirstArg(args);
		//call handler
		Handler_SetAllRowsStyle(args);
		return;
	}
	if (args[0] == "allcells")
	{
		URemoveFirstArg(args);
		//call handler
		Handler_SetAllCellsStyle(args);
		return;
	}

	if (args.size() < 3) throw CustomExceptions::CmdError("E0017 - Missing parameters for set command");
	if (args[0] == "row")
	{
		URemoveFirstArg(args);
		//call handler
		Handler_SetRowStyle(args);
		return;
	}
	if (args[0] == "col")
	{
		URemoveFirstArg(args);
		//call handler
		Handler_SetColStyle(args);
		return;
	}
	if (args[0] == "cells")
	{
		URemoveFirstArg(args);
		//call handler
		Handler_SetCellsStyle(args);
		return;
	}

	//if we get here something is wrong with parametes.
	throw CustomExceptions::CmdError("E0018 - Wrong paramets");
}

void Table::Handler_SetTableStyle(std::vector<std::string>& args)
{
	std::string newStyle = UGetAllArgsInString(args);
	SetStyle(newStyle);
	Console::Msg::LogSucc("Updated table style to: " + newStyle);
}

void Table::Handler_SetAllRowsStyle(std::vector<std::string>& args)
{
	std::string newStyle = UGetAllArgsInString(args);
	for (int i = 0; i < Rows.size(); i++)
	{
		Rows[i].SetStyle(newStyle);
	}
	Console::Msg::LogSucc("Updated style of all the rows to: " + newStyle);
}

void Table::Handler_SetAllCellsStyle(std::vector<std::string>& args)
{
	std::string newStyle = UGetAllArgsInString(args);
	for (int i = 0; i < Rows.size(); i++)
	{
		Rows[i].SetCellsStyle(newStyle);
	}
	Console::Msg::LogSucc("Updated style of all the cells to: " + newStyle);
}

void Table::Handler_SetRowStyle(std::vector<std::string>& args)
{
	int pos = -1;
	std::stringstream{ args[0] } >> pos;
	pos -= 1;
	URemoveFirstArg(args);

	if (pos<0 || pos >= Rows.size()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");

	std::string newStyle = UGetAllArgsInString(args);
	Rows[pos].SetStyle(newStyle);
	Console::Msg::LogSucc("Updated style of the row "+std::to_string(pos+1)+": " + newStyle);
}

void Table::Handler_SetCellsStyle(std::vector<std::string>& args)
{
	int pos = -1;
	std::stringstream{ args[0] } >> pos;
	pos -= 1;
	URemoveFirstArg(args);

	if (pos<0 || pos >= Rows.size()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");

	std::string newStyle = UGetAllArgsInString(args);
	Rows[pos].SetCellsStyle(newStyle);
	Console::Msg::LogSucc("Updated style of the row " + std::to_string(pos + 1) + " cells: " + newStyle);
}

void Table::Handler_SetColStyle(std::vector<std::string>& args)
{
	int pos = -1;
	std::stringstream{ args[0] } >> pos;
	pos -= 1;
	URemoveFirstArg(args);

	if (pos<0 || pos >= Rows[0].GetCellsCount()) throw CustomExceptions::CmdError("E0020 - Wrong position: the specified position is not in the table!");

	std::string newStyle = UGetAllArgsInString(args);
	for (int i = 0; i < Rows.size(); i++)
	{
		Rows[i].SetCellStyle(pos, newStyle);
	}

	Console::Msg::LogSucc("Updated style of the col " + std::to_string(pos + 1) + " cells: " + newStyle);
}