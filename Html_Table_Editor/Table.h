/*
Html_Table_Editor
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
#include <sstream>

class Table
{
private:
	std::string _input;
	std::vector<Row> Rows;
	Console::Msg* msg;
	int ignorepos = 0;
	//replace all html tags with custom defined tags
	void ReplaceKnownHtmlFormattingTags();
	//generate the rows
	void PopulateRows(const std::string& input, int startPos);
	//get table content
	void GetTable(const std::string& input);
	//set new row numbers
	void ReEnumRows();

	void AddRowAtPos(unsigned pos,Row& r);
	void AddEmptyColumnAtPos(unsigned pos);

	void RemoveRow(unsigned pos);
	void RemoveColumn(unsigned pos);

	//handlers
	//Remove the fist item of the vector that is gaven as input
	void URemoveFirstArg(std::vector<std::string>& args);
	//put all args in a string
	std::string UGetAllArgsInString(std::vector<std::string>& args);

	//handle add row cmds
	void Handler_AddRowCMD(std::vector<std::string>& args);
	//handle add coll cmds
	void Handler_AddColumnCMD(std::vector<std::string>& args);

	//handle rm row
	void Handler_RemoveRowCMD(std::vector<std::string>& args);
	//handle rm coll
	void Handler_RemoveColumnCMD(std::vector<std::string>& args);

	//hanlde set row cmd; set the content of all the cells of one row
	void Handler_SetRowContentCMD(std::vector<std::string>& args);
	//hanlde set row cmd; set the content of all the cells of one column
	void Handler_SetColumnContentCMD(std::vector<std::string>& args);
	//hanlde set all cmd; set the content of all the cells of the table
	void Handler_SetAllContentCMD(std::vector<std::string>& args);



public:
	Table(const std::string& input);
	~Table();

	int GetRowNumber() { return Rows.size(); }
	int GetColumnNumber() { return Rows[0].GetCells(); }
	int GetCellNumber();
	bool HasLayout() { return Rows[0].IsLayout(); }

	//handle all add cmds
	void CMD_Add(std::vector<std::string> args); //chose the correct handler based on 1st parameter

	void CMD_Rm(std::vector<std::string> args); //chose the correct handler based on 1st parameter

	void CMD_Set(std::vector<std::string> args); //chose the correct handler based on 1st parameter

	void CMD_TableProps(std::vector<std::string> args); //Print table properties

	void CMD_WriteRawData(std::vector<std::string> args); //paste the raw data on a file
	void CMD_WriteOutput(std::vector<std::string> args); //creates the new table

};

