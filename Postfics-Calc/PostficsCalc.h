#pragma once
#include <sstream>
#include <string>
#include "List.h"

class PostficsCalc
{
private:
	char isOperator(char symbol);

	void err_incorrect_postfix_istring();
	void err_empty_istring();
public:
	int stringCheck(const std::string inputString);

public:
	int fromPostfics(const std::string& inputString);

	std::string toPostfics(const std::string& inputString);
};

