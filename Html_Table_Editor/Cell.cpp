/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include "Cell.h"

Cell::Cell()
{
}


Cell::~Cell()
{
}

Cell& Cell::operator>> (std::string& val)
{
	ReplaceFirst(val, ">", CustomCloseTag+" "); // use a custom close tag for initial part
	std::stringstream ss{ val };
	std::string item;

	bool foundClosetag = false;
	while (ss >> item)
	{	
		if (item.find(CustomCloseTag, 0) != std::string::npos) //this allows to not catch elements inside of < >
			foundClosetag = true; 

		//check that the item is not a open/close tag
		if (item.find(RowOpenTag) == std::string::npos && foundClosetag && item.find(CustomCloseTag) == std::string::npos)
		{
			content += item+" ";
		}
	}
	return *this;
}
