/*
Html_Table_Builder
https://github.com/RickyCoDev/Html_Table_Editor

Copyright (c) 2016 RickyCoDev

Licenced under Apache 2.0 Licence
http://www.apache.org/licenses/LICENSE-2.0
*/

#include"Common.h";
Cmsg::Msg* msg = new Cmsg::Msg{};

std::string Replace(const std::string& input, const std::string& StringToReplace, const std::string& Replacer)
{
	if (!CheckForPresence(input, StringToReplace))
		throw CustomExceptions::ReadError("Can't find: "+StringToReplace) ;

	std::string result = input;
	//replace all matches
	for (std::size_t i = result.find(StringToReplace, 0); i != std::string::npos;)
	{
		result.replace(i, StringToReplace.length(), Replacer);
		i = result.find(StringToReplace, i + 1);
	}
	return result;
}

std::string ReplaceFirst(const std::string& input, const std::string& StringToReplace, const std::string& Replacer)
{
	if (!CheckForPresence(input, StringToReplace))
		throw CustomExceptions::ReadError("Can't find: " + StringToReplace);

	std::string result = input;
	result.replace(result.find(StringToReplace, 0), StringToReplace.length(), Replacer);
	return result;
}

bool CheckForPresence(const std::string& input, const std::string& item)
{
	if (input.find(item) != std::string::npos)
		return true;
	else
		return false;
}


