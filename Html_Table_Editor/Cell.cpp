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
	msg->clog << "Cell " + std::to_string(cellNumber) << ":\n" + input;
}


Cell::~Cell()
{
}

