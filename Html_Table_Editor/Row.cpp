/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/
#include "Row.h"



Row::Row(std::string input,int rowNumber) : RowNumber(rowNumber)
{
	msg->clog << "Row " + std::to_string(RowNumber) + ":\n " + input;
}


Row::~Row()
{
}
