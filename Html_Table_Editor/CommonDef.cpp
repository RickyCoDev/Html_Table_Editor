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

std::string Reduce(const std::string& input, const std::string& BeginPoint, const std::string& EndPoint)
{
	if(!CheckForPresence(input,BeginPoint))
		throw CustomExceptions::ReadError("Can't find begin point: " + BeginPoint);
	if (!CheckForPresence(input, EndPoint))
		throw CustomExceptions::ReadError("Can't find end point: " + EndPoint);

	//if we get here, there must be open and close items
	size_t begin = input.find(BeginPoint) + BeginPoint.length(); // not include the open token
	size_t end = input.find(EndPoint);

	return input.substr(begin, end - begin); // return the string between the two markers
}

bool CheckForPresence(const std::string& input, const std::string& item)
{
	if (input.find(item) != std::string::npos)
		return true;
	else
		return false;
}

std::vector<std::string> SplitAt(const std::string& input, const std::string token)
{
	std::vector<std::string> Parts;
	for (std::size_t i = input.find(token, 0), j=0; i != std::string::npos; )
	{
		i += token.length(); // include the token in substring
		Parts.push_back(input.substr(j, i - j)); // j is the last pos of i, this allows to not split the string from begining
		j = i; // j must be updated with the last pos of i
		i = input.find(token, i);
	}
	return Parts;
}


