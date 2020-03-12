#include <iostream>
#include <string>
#include "PostficsCalc.h"
using namespace std;

int main() {
	system("chcp 65001"); system("cls");
	cout << "Калькулятор сложных выражений (постфиксный)" << endl <<
		"Введите строку-выражение в обычном виде" << endl;
	cout << "> ";

	PostficsCalc calc;
	string str;
	getline(cin, str);

	try {
		cout << "Эта строка в постфиксной форме: " << calc.toPostfics(str) << endl;
		cout << "Результат вычислений: " << calc.fromNormal(str) << endl << endl;
	}
	catch (logic_error error) {
		cerr << error.what() << endl;
	}

	cout << "\nДля выхода нажмите ввод";
	cin.get();
	return 0;
}