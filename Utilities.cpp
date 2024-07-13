#include <iostream>
#include <string>
#include <cstring>
#include "Utilities.h"

namespace seneca
{
	char Utilities::m_delimiter = {};

	//sets the field width of the current object to the value of parameter newWidth
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	//returns the field width of the current object
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	//extracts a token from string str referred to by the first parameter.
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		if (next_pos >= str.length()) 
			throw std::out_of_range("next_pos is out of the string's range.");

		//reports an exception if a delimiter is found at next_pos
		if (str[next_pos] == m_delimiter)
		{
			more = false;
			throw std::invalid_argument("Delimiter found at the start position.");  
		} 
			

		std::string token;
		size_t end_pos = str.find(m_delimiter, next_pos);
		if (end_pos == std::string::npos) 
		{
			token = str.substr(next_pos);  
			more = false;  
		}
		else 
		{
			token = str.substr(next_pos, end_pos - next_pos);
			next_pos = end_pos + 1;
			more = true;
		}

		token = removeSpace(token);
		if(m_widthField < token.length())
			m_widthField = token.length();

		return token;
	}

	std::string Utilities::removeSpace(const std::string& str)
	{
		if (!str.empty())
		{
			size_t first = str.find_first_not_of(' ');
			if (first == std::string::npos)
				return "";
			size_t last = str.find_last_not_of(' ');
			return str.substr(first, (last - first + 1));
		}
		return "";
	}

	//class function
	//sets the delimiter for this class to the character received
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	// returns the delimiter for this class.
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
;
}
