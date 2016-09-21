/*
Html_Table_Editor
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) Ricky Corte

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/
#pragma once
#include <string>
#include <vector>
#include "Common.h"
#include "Cell.h"
class Row
{
private:
	bool isLayout;
	int RowNumber;
	std::vector<Cell> Cells;
	std::string style;

	void PopulateCells(std::string input);
	//reset cell numbers
	void ReEnumCells();

public:
	Row(const std::string& input, const int rowNumber);
	//create a row with number of empty cells
	Row(int cells);
	~Row();

	void SetRowNumber(int rowNumber) { RowNumber = rowNumber; if (RowNumber == 0) isLayout = true; }
	int GetRowNumber() { return RowNumber; }
	int GetCellsCount() { return Cells.size(); }
	bool IsLayout() { return isLayout; }
	bool IsEmpty() { return (Cells.size() > 0) ? false : true; }
	//Cell GetCell(const int& index) { return Cells[index]; }; //TODO: add error handlig for out of range
	std::string GetRowContent(OutputKind kind);

	//adds a empty cell
	void AddEmptyCell(unsigned pos);
	void RemoveCell(unsigned pos);

	//set the content for a single cell
	void SetCellContent(unsigned Cpos, std::string newContent);
	//set the contet of all the row
	void SetAllCellsContent(std::string newContent);

	//add to a cell the content of another with a specified pattern
	void JoinCellContent(unsigned cPos, std::string pattern, std::string c2Content);

	void FillWithEmptyCells(unsigned cellNumber);
	//return the content string from an element by its position
	std::string GetCellContent(unsigned pos);

	//set the style of the row tag
	void SetStyle(std::string newStyle) { style = " " + newStyle; }

	void SetCellStyle(unsigned cPos, std::string newStyle);

	void SetCellsStyle(std::string newStyle);
};

