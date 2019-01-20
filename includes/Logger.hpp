#ifndef LOGGER_HPP
# define LOGGER_HPP

namespace dn
{
	static const char endl = '\n';

	template <typename Arg>
	void log(const Arg &p_arg);

	template <typename Arg, typename ... Args>
	void log(const Arg &p_arg, Args ... p_args);
}

# include "Logger.inl"

#endif // LOGGER_HPP
