#include "PostficsCalc.h"
using namespace std;

char PostficsCalc::isOperator(char symbol) {
	switch (symbol) {
	case '+':									// begFallfrow
	case '-':
	case '*':
	case '/':	return symbol;					// endFallthrow
	default:	return 0;
	}
}

char PostficsCalc::isPlusMinus(char symbol) {
	switch (symbol) {
	case '+':						//begFallthrow
	case '-':	return symbol;		//endFallthrow
	default:	return 0;
	}
}

char PostficsCalc::isMultDiv(char symbol) {
	switch (symbol) {
	case '*':						//begFallthrow
	case '/':	return symbol;		//endFallthrow
	default:	return 0;
	}
}

void PostficsCalc::err_incorrect_postfix_istring() {
	cerr << "ERR: incorrect postfics input string!" << endl;
	throw logic_error("ERR: incorrect postfics input string!");
}
void PostficsCalc::err_empty_istring() {
	cerr << "ERR: Empty input string!" << endl;
	throw logic_error("ERR: Empty input string!");
}

int PostficsCalc::stringCheck(const std::string& inputString) {
	bool digit{ false }, op{ false }, ws{ false };
	int numBracket{};
	for (int i = 0; i < inputString.size(); ++i) {
		if (inputString[i] == ' ') {
			ws = true;
			continue;
		}
		else if (isdigit(inputString[i])) {
			if (digit == true && ws == true) {
				throw logic_error("ERR: Two numbers in a row");
				return i + 1;
			}

			digit = true;
			op = false;
			ws = false;
		}
		else if (isOperator(inputString[i])) {
			if (op == true && ws == true || (i > 0 && isOperator(inputString[i - 1]))) {
				throw logic_error("ERR: Two operators in a row");
				return i + 1;
			}

			digit = false;
			op = true;
			ws = false;
		}
		else if (inputString[i] == ')' || inputString[i] == '(') {
			if (inputString[i] == ')') {
				--numBracket;
			}
			else ++numBracket;
		}
		else {
			throw logic_error("ERR: unknown symbol in string");
			return i + 1;
		}
	}
	if (numBracket != 0) {
		throw logic_error("ERR: not equal num of brackets");
		return numBracket;
	}
	return 0;
}

std::string PostficsCalc::addWS(const std::string& inputString) {
	string editedString;

	for (int i = 0; i < inputString.size(); ++i) {
		if (i > 0 && inputString[i - 1] != ' ') {
			if (isdigit(inputString[i]) && !isdigit(inputString[i - 1])) {
				editedString += ' ';
			}
			else if (isOperator(inputString[i])) {
				editedString += ' ';
			}
			else if (inputString[i] == '(') {
				editedString += ' ';
			}
			else if (inputString[i] == ')') {
				editedString += ' ';
			}
		}

		editedString += inputString[i];
	}

	return editedString;
}

int PostficsCalc::fromPostfics(const string& inputString) {
	if (inputString.empty()) {
		err_empty_istring();
		return 0;
	}

	stringstream inputBuffer;	
	inputBuffer << inputString;
	List numBuffer;

	string currFragment;
	while (inputBuffer >> currFragment) {
		if (isdigit(currFragment[0])) {
			numBuffer.push_back(stoi(currFragment));
		}
		else if (isOperator(currFragment[0])) {
			if (numBuffer.size() < 2 && !isPlusMinus(currFragment[0]) || numBuffer.size() < 1) {
				err_incorrect_postfix_istring();
				return 0;
			}
			int a = numBuffer.pop_back();
			int b {};
			if (numBuffer.size() > 0) b = numBuffer.pop_back();
			int c{};

			switch (currFragment[0]) {
			case '+': c = b + a; break;
			case '-': c = b - a; break;
			case '*': c = b * a; break;
			case '/': c = b / a; break;
			}

			numBuffer.push_back(c);
		}
	}

	if (numBuffer.size() != 1) {
		err_incorrect_postfix_istring();
		return 0;
	}
	else return numBuffer.pop_back();
}

std::string PostficsCalc::toPostfics(const std::string& inputString) {
	if (inputString.empty()) {
		err_empty_istring();
		return inputString;
	}
	if (stringCheck(inputString)) {
		return inputString;
	}

	string inString = addWS(inputString);
	string outString;
	stringstream inputBuffer;
	inputBuffer << inString;
	List operatorBuffer;

	string currFragment;
	while (inputBuffer >> currFragment) {
		if (isdigit(currFragment[0])) {
			outString += currFragment += " ";
		}
		else if (currFragment[0] == '(') {
			operatorBuffer.push_back(static_cast<int>('('));
		}
		else if (currFragment[0] == ')') {
			while (operatorBuffer.back() != static_cast<int>('(')) {
				outString += static_cast<char>(operatorBuffer.pop_back());
				outString += ' ';
			}
			operatorBuffer.pop_back();
		}
		else if (isOperator(currFragment[0])) {
			if (isMultDiv(currFragment[0])) {
				while (operatorBuffer.size() > 0 && isMultDiv(static_cast<char>(operatorBuffer.back()))) {
					outString += static_cast<char>(operatorBuffer.pop_back());
					outString += ' ';
				}
				operatorBuffer.push_back(static_cast<int>(currFragment[0]));
			}
			else {
				while (operatorBuffer.size() > 0 && isOperator(static_cast<char>(operatorBuffer.back()))) {
					outString += static_cast<char>(operatorBuffer.pop_back());
					outString += ' ';
				}
				operatorBuffer.push_back(static_cast<int>(currFragment[0]));
			}
		}
	}

	while (operatorBuffer.size() != 0) {
		outString += static_cast<char>(operatorBuffer.pop_back());
		outString += ' ';
	}

	return outString;
}

int PostficsCalc::fromNormal(const std::string& inputString) {
	return fromPostfics(toPostfics(inputString));
}