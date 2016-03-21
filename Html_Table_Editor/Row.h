/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/
#pragma once
#include <string>
#include <vector>
#include "Common.h"
class Row
{
private:
	int RowNumber;
public:
	Row(std::string input, int rowNumber);
	~Row();
};

