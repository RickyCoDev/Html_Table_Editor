/*
 Html_Table_Editor
 https://github.com/RickyCoDev/Html_Table_Editor

 Copyright (c) 2016 RickyCoDev

 Licenced under Apache 2.0 Licence
 http://www.apache.org/licenses/LICENSE-2.0
*/

#pragma once
#ifndef Common_H // prevent multiple declarations
#define Common_H

#include "CustomExceptions.h"
#include <string>
#include <vector>
#include "Commands.h"

//extern Cmsg::Msg* msg;

extern Commands* cmds;

const std::string TableOpenTag = "|t|";
const std::string TableCloseTag = "|!t|";

const std::string HCellOpenTag = "|h|";
const std::string HCellCloseTag = "|!h|";

const std::string RowOpenTag = "|r|";
const std::string RowCloseTag = "|!r|";

const std::string CellOpenTag = "|el|";
const std::string CellCloseTag = "|!el|";
enum OutputKind
{
	clean, normal
};

//replace all substring with a desired one
std::string Replace(const std::string& input, const std::string& StringToReplace, const std::string& Replacer);

//replace only the fist element
std::string ReplaceFirst(const std::string& target, const std::string& StringToReplace, const std::string& Replacer);

//returns the string between an the first open/close separators
std::string Reduce(const std::string& input, const std::string& BeginPoint, const std::string& EndPointbool, const bool CloseTag = true);

//check if a string is present in the input
bool CheckForPresence(const std::string& input, const std::string& item);

//split a string into parts
std::vector<std::string> SplitAt(const std::string& input, const std::string token);

#endif // !Common_H

