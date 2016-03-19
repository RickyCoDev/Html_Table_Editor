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


