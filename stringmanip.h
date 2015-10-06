#ifndef __STRINGMANIP_H_INCLUDED__
#define __STRINGMANIP_H_INCLUDED__

#include <string>
#include <sstream>
using namespace std;

//trim whitespace at the end of a string
inline string trim_right_copy(const string &s, const string &delimiters = " \f\n\r\t\v")
{
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

//trim whitespace at the beginning of a string
inline string trim_left_copy(const string &s, const string &delimiters = " \f\n\r\t\v")
{
	return s.substr(s.find_first_not_of(delimiters));
}

//trim whitespace from beginning and end of a string
inline string trim_copy(const string &s, const string &delimiters = " \f\n\r\t\v")
{
	return trim_left_copy(trim_right_copy(s, delimiters), delimiters);
}

//use a stream to convert a variable to a string
template<typename T> string to_string(const T &x)
{
	ostringstream stream;
	stream << x;
	return stream.str();
}

#endif
