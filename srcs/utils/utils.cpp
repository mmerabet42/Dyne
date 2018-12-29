#include "utils.hpp"
#include <sstream>

std::vector<std::string> dn::split(const std::string &p_str, const char &p_delimiter, const bool &p_keepEmpty)
{
	std::vector<std::string> sp;
	std::istringstream str_stream(p_str);
	std::string tk;

	while (std::getline(str_stream, tk, p_delimiter))
		if (p_keepEmpty || !tk.empty())
			sp.push_back(tk);
	return (sp);
}
