#ifndef DN_LOGGER_INL
# define DN_LOGGER_INL

#include "Logger.hpp"
#include <iostream>

template <typename Arg>
void dn::log(const Arg &p_arg)
{
	std::cout << p_arg;
}

template <typename Arg, typename ... Args>
void dn::log(const Arg &p_arg, Args ... p_args)
{
	std::cout << p_arg;
	dn::log(p_args ...);
}

#endif // DN_LOGGER_INL
