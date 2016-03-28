/*
Html_Table_Editor
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

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

	void PopulateCells(std::string input);
public:
	Row(const std::string& input, const int rowNumber);
	//create a row with number of empty cells
	Row(int cells);
	~Row();

	void SetRowNumber(int rowNumber) { RowNumber = rowNumber; }
	int GetRowNumber() { return RowNumber; }
	int GetCells() { return Cells.size(); }
	bool RowIsLayout() { return isLayout; }
	//Cell GetCell(const int& index) { return Cells[index]; }; //TODO: add error handlig for out of range
	std::string GetRowContent(OutputKind kind);


};

