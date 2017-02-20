/*
Html_Table_Editor
https://github.com/rickycorte/Html_Table_Editor

Copyright (c) 2016 Ricky Corte

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Common.h"
#include "CustomExceptions.h"
#include "Row.h"
#include <sstream>

class Table : public Console::IPrintable
{
private:
	std::string _input;
	std::vector<Row> Rows;

	std::string style;

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

	void JoinRows(unsigned row1, unsigned row2, std::string newContent);

	void JoinColumns(unsigned col1, unsigned col2, std::string newContent);

	void SetStyle(std::string newStyle) { style = " " + newStyle; }

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

	//hanlde set/edit row cmd; set the content of all the cells of one row
	void Handler_SetRowContentCMD(std::vector<std::string>& args);
	//hanlde set/edit row cmd; set the content of all the cells of one column
	void Handler_SetColumnContentCMD(std::vector<std::string>& args);
	//hanlde set/edit all cmd; set the content of all the cells of the table
	void Handler_SetAllContentCMD(std::vector<std::string>& args);
	//hanlde set/edit cell cmd; set the content of a cell
	void Handler_SetCellContentCMD(std::vector<std::string>& args);

	//handle join rows cmd; allow to join content of two rows and then delete one
	void Handler_JoinRows(std::vector<std::string>& args);
	//handler join cols cmd; allow to join content of two columns and then delete one
	void Handler_JoinColumns(std::vector<std::string>& args);

	//set the table style
	void Handler_SetTableStyle(std::vector<std::string>& args);
	//set the row style of every row
	void Handler_SetAllRowsStyle(std::vector<std::string>& args);
	//set the style of all the cells
	void Handler_SetAllCellsStyle(std::vector<std::string>& args);
	//set the style of one row
	void Handler_SetRowStyle(std::vector<std::string>& args);
	//set the style of one column
	void Handler_SetColStyle(std::vector<std::string>& args);
	//set the style of all the cells of one row
	void Handler_SetCellsStyle(std::vector<std::string>& args);


public:
	Table(const std::string& input);
	~Table();

	int GetRowNumber() { return Rows.size(); }
	int GetColumnNumber() { return Rows[0].GetCellsCount(); }
	int GetCellNumber();
	bool HasLayout() { return Rows[0].IsLayout(); }

	//handle all add cmds
	void CMD_Add(std::vector<std::string> args); //chose the correct handler based on 1st parameter

	void CMD_Rm(std::vector<std::string> args); //chose the correct handler based on 1st parameter

	void CMD_Set(std::vector<std::string> args); //chose the correct handler based on 1st parameter

	void CMD_TableProps(std::vector<std::string> args); //Print table properties

	void CMD_WriteRawData(std::vector<std::string> args); //paste the raw data on a file
	void CMD_WriteOutput(std::vector<std::string> args); //creates the new table

	void CMD_Join(std::vector<std::string> args); // join 2 rows or columns
	//fill empty elements and erase exceding one
	void CMD_LineUp(std::vector<std::string> args);
	//set style of every element
	void CMD_Style(std::vector<std::string> args);

	std::string ToString() override;
};

