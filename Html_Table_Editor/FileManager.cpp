/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/
#include "FileManager.h"



FileManager::FileManager(File ft)
{
	switch (ft)
	{
	case FileManager::cleandata:
		break;
	case FileManager::output:
		break;
	}
}


FileManager::~FileManager()
{
	delete fstream;
}
