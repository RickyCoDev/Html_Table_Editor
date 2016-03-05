#pragma once
#ifndef Common_H // prevent multiple declarations
#define Common_H

#include "Msg.h"

extern Cmsg::Msg* msg;

const std::string LineCellTag = "|c|";

//replace all substring with a desired one
std::string Replace(const std::string& input, const std::string& StringToReplace, const std::string& Replacer);

//replace only the fist element
void ReplaceFirst(std::string& target, const std::string& StringToReplace, const std::string& Replacer);

//edit the string passed by reference
void InsertCustomTags(std::string& target);

#endif // !Common_H

