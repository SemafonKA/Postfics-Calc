#include <iostream>
#include <string>
#include "PostficsCalc.h"

int main() {
	system("chcp 65001"); system("cls");

	PostficsCalc calc;

	std::cout << "> ";

	std::string str;
	std::getline(std::cin, str);
	std::cout << "Exit code: " << calc.stringCheck(str) << std::endl;

	system("pause");
	return 0;
}