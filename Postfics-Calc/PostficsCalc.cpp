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

inline void PostficsCalc::err_incorrect_postfix_istring() {
	cerr << "ERR: incorrect postfics input string!" << endl;
	throw logic_error("ERR: incorrect postfics input string!");
}
inline void PostficsCalc::err_empty_istring() {
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
		else if (isdigit(inputString[i]) || inputString[i] == '.') {
			if (digit == true && ws == true) {
				cerr << "ERR: Two numbers in a row" << endl;
				throw logic_error("ERR: Two numbers in a row");
				return i + 1;
			}

			digit = true;
			op = false;
			ws = false;
		}
		else if (isOperator(inputString[i])) {
			if (op == true && ws == true || (i > 0 && isOperator(inputString[i - 1]))) {
				cerr << "ERR: Two operators in a row" << endl;
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
			cerr << "ERR: unknown symbol in string" << endl;
			throw logic_error("ERR: unknown symbol in string");
			return i + 1;
		}
	}
	if (numBracket != 0) {
		cerr << "ERR: not equal num of brackets" << endl;
		throw logic_error("ERR: not equal num of brackets");
		return numBracket;
	}
	return 0;
}

std::string PostficsCalc::addWS(const std::string& inputString) {
	string editedString;

	for (int i = 0; i < inputString.size(); ++i) {
		if (i > 0 && inputString[i - 1] != ' ' && inputString[i] != ' ') {
			if (isdigit(inputString[i]) && !isdigit(inputString[i - 1]) && inputString[i - 1] != '.') {
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
		if ((i == 0 || !isdigit(inputString[i - 1])) && inputString[i] == '.') {
			editedString += " 0";
		}
		editedString += inputString[i];
	}

	return editedString;
}

double PostficsCalc::fromPostfics(const string& inputString) {
	if (inputString.empty()) {
		err_empty_istring();
		return 0;
	}

	stringstream inputBuffer;	
	inputBuffer << inputString;
	Dlist<double> numBuffer;

	string currFragment;
	while (inputBuffer >> currFragment) {
		if (isdigit(currFragment[0])) {
			numBuffer.push_back(stod(currFragment));
		}
		else if (isOperator(currFragment[0])) {
			if (numBuffer.size() < 2 && !isPlusMinus(currFragment[0]) || numBuffer.size() < 1) {
				err_incorrect_postfix_istring();
				return 0;
			}
			double a = numBuffer.pop_back();
			double b {};
			if (numBuffer.size() > 0) b = numBuffer.pop_back();
			double c{};

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
		err_incorrect_postfix_istring();		//ERROR_MESSAGE incorrect postfix istring
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
	Dlist<char> operatorBuffer;

	string currFragment;
	while (inputBuffer >> currFragment) {
		if (isdigit(currFragment[0])) {
			outString += currFragment += " ";
		}
		else if (currFragment[0] == '(') {
			operatorBuffer.push_back('(');
		}
		else if (currFragment[0] == ')') {
			while (operatorBuffer.back() != '(') {
				outString += operatorBuffer.pop_back();
				outString += ' ';
			}
			operatorBuffer.pop_back();
		}
		else if (isOperator(currFragment[0])) {
			if (isMultDiv(currFragment[0])) {
				while (operatorBuffer.size() > 0 && isMultDiv(operatorBuffer.back())) {
					outString += operatorBuffer.pop_back();
					outString += ' ';
				}
				operatorBuffer.push_back(currFragment[0]);
			}
			else {
				while (operatorBuffer.size() > 0 && isOperator(operatorBuffer.back())) {
					outString += operatorBuffer.pop_back();
					outString += ' ';
				}
				operatorBuffer.push_back(currFragment[0]);
			}
		}
	}

	while (operatorBuffer.size() != 0) {
		outString += operatorBuffer.pop_back();
		outString += ' ';
	}

	return outString;
}

double PostficsCalc::fromNormal(const std::string& inputString) {
	return fromPostfics(toPostfics(inputString));
}