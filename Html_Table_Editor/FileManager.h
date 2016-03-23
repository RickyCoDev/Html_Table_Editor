/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/
#pragma once
#include <iostream>
#include "Common.h"
#include <fstream>
#include <string>
#include "CustomException.h"
class FileManager
{
private:
	const std::string CleanData = "cleandata.txt";
	const std::string OutPut = "output.txt";
	std::string ReadFile(const std::string& filename);
	std::fstream* fstream;
	
public:
	enum File {cleandata,output };
	FileManager(File ft);
	~FileManager();
};

