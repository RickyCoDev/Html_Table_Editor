#include"Common.h";
Cmsg::Msg* msg = new Cmsg::Msg{};

std::string Replace(const std::string& input, const std::string& StringToReplace, const std::string& Replacer)
{
	std::string result = input;
	//replace all matches
	for (std::size_t i = result.find(StringToReplace, 0); i != std::string::npos;)
	{
		result.replace(i, StringToReplace.length(), Replacer);
		i = result.find(StringToReplace, i + 1);
	}
	return result;
}

void ReplaceFirst(std::string& target, const std::string& StringToReplace, const std::string& Replacer)
{
	target.replace(target.find(StringToReplace, 0), StringToReplace.length(), Replacer);
}
void InsertCustomTags(std::string& target)
{
	target = Replace(target, "<td", LineCellTag);
	target = Replace(target, "</td"," "+LineCellTag);
}

