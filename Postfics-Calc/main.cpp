#include <iostream>
#include <string>
#include "PostficsCalc.h"

//todo:: (a + b)(c + d) == (a + b) * (c + d)

int main() {
	system("chcp 65001"); system("cls");
	std::cout << "Калькулятор сложных выражений (постфиксный)" << std::endl <<
		"Введите строку-выражение в обычном виде" << std::endl;
	std::cout << "> ";

	PostficsCalc calc;
	std::string str;
	std::getline(std::cin, str);

	std::cout << "Эта строка в постфиксной форме: " << calc.toPostfics(str) << std::endl;
	std::cout << "Результат вычислений: " << calc.fromNormal(str) << std::endl << std::endl;

	/*PostficsCalc calc;
	std::string str;
	std::getline(std::cin, str);

	std::cout << calc.toPostfics(str) << std::endl;
	std::cout << calc.fromNormal(str) << std::endl;*/

	std::cout << "\n...для выхода нажмите ввод";
	std::cin.get();
	return 0;
}