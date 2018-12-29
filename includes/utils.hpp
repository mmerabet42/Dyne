#ifndef UTILS_HPP
# define UTILS_HPP

# include <vector>
# include <string>

namespace dn
{
	std::vector<std::string> split(const std::string &p_str, const char &p_delimiter, const bool &p_keepEmpty = false);
}

#endif // UTILS_HPP
