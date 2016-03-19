#pragma once
#ifndef Common_H // prevent multiple declarations
#define Common_H

#include "Msg.h"
#include "CustomExceptions.h"

extern Cmsg::Msg* msg;

const std::string TableOpenTag = "|t|";
const std::string TableCloseTag = "|!t|";

const std::string HCellOpenTag = "|h|";
const std::string HCellCloseTag = "|!h|";

const std::string RowOpenTag = "|r|";
const std::string RowCloseTag = "|!r|";

const std::string CellOpenTag = "|el|";
const std::string CellCloseTag = "|!el|";

//replace all substring with a desired one
std::string Replace(const std::string& input, const std::string& StringToReplace, const std::string& Replacer);

//replace only the fist element
std::string ReplaceFirst(const std::string& target, const std::string& StringToReplace, const std::string& Replacer);

//returns the string between an the first open/close separators
std::string Reduce(const std::string& input, const std::string& BeginPoint, const std::string& EndPoint);

bool CheckForPresence(const std::string& input, const std::string& item);

#endif // !Common_H

