#include "PostficsCalc.h"
#include <sstream>
using namespace std;

char PostficsCalc::isOperator(char symbol) {
	switch (symbol) {
	case '+':									// begin Fallfrow
	case '-':
	case '*':
	case '/':	return symbol;					// end Fallthrow
	default:	return 0;
	}
}

char PostficsCalc::isPlusMinus(char symbol) {
	switch (symbol) {
	case '+':						//begin Fallthrow
	case '-':	return symbol;		//end Fallthrow
	default:	return 0;
	}
}

char PostficsCalc::isMultDiv(char symbol) {
	switch (symbol) {
	case '*':						//begin Fallthrow
	case '/':	return symbol;		//end Fallthrow
	default:	return 0;
	}
}

int PostficsCalc::stringCheck(const string& inputString) {
	bool digit{ false }, op{ false }, ws{ false };
	int numBracket{};
	for (int i = 0; i < inputString.size(); ++i) {
		if (inputString[i] == ' ') {
			ws = true;
			continue;
		}
		else if (isdigit(inputString[i]) || inputString[i] == '.' || inputString[i] == ',') {
			if (digit == true && ws == true) {
				string error = "ERR: Two numbers in a row at " + to_string(i);
				throw logic_error(error);
				return i + 1;
			}

			digit = true;
			op = false;
			ws = false;
		}
		else if (isOperator(inputString[i])) {
			if (op == true && ws == true && isMultDiv(inputString[i])) {
				string error = "ERR: Two operators in a row at " + to_string(i);
				throw logic_error(error);
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
			digit = false;
			op = false;
		}
		else {
			string error = "ERR: unknown symbol in string at " + to_string(i);
			throw logic_error(error);
			return i + 1;
		}
	}
	if (numBracket != 0) {
		string error = "ERR: not equal count of brackets (" + to_string(numBracket) + ")";
		throw logic_error(error);
		return numBracket;
	}
	return 0;
}

string PostficsCalc::addWS(const string& inputString) {
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
		editedString += inputString[i];
	}

	return editedString;
}

string PostficsCalc::addZeros(const string& inputString) {
	string outputString;
	bool isPrevNum{ false }, isPrevOp{ true }, isPrevDot{ false };
	bool isPrevWS{ true }, isDouble{ false };
	
	for (int i = 0; i < inputString.size(); ++i) {
		if (inputString[i] == ' ' && isPrevDot) {
			outputString += "0";

			isPrevNum	= true;
			isPrevOp	= false;
			isPrevDot	= false;
			isPrevWS	= true;
			isDouble	= false;
		}
		else if (inputString[i] == ' ') {
			isPrevWS	= true;
			isPrevDot	= false;
		}
		else if (isdigit(inputString[i])) {
			isPrevNum	= true;
			isPrevOp	= false;
			isPrevWS	= false;
			isPrevDot	= false;
		}
		else if (inputString[i] == '.' && isDouble) {
			++i;
			if (i == inputString.size()) break;
		}
		else if (inputString[i] == '.' && (isPrevWS || isPrevOp)) {
			outputString += " 0";

			isPrevNum	= true;
			isPrevOp	= false;
			isPrevDot	= true;
			isPrevWS	= false;
			isDouble	= true;
		}
		else if (inputString[i] == '.') {
			isDouble	= true;
		}
		else if (isPlusMinus(inputString[i]) && isPrevOp && !isPrevNum) {
			if (!isPrevWS) outputString += ' ';
			outputString += "0 ";

			isPrevNum	= false;
			isPrevOp	= true;
			isPrevDot	= false;
			isPrevWS	= false;
		}
		else if (isOperator(inputString[i])) {
			if (isPrevOp) throw logic_error("ERR: Too many multiply or division operators in a row");

			isPrevNum	= false;
			isPrevOp	= true;
			isPrevDot	= false;
			isPrevWS	= false;
			isDouble	= false;
		}
		outputString += inputString[i];
	}

	return outputString;
}

string PostficsCalc::comToDot(const string& inputString) {
	string outString;
	for (auto& elem : inputString) {
		if (elem == ',') outString += '.';
		else outString += elem;
	}

	return outString;
}

string PostficsCalc::addSkippedMult(const string& inputString) {
	string outputString;
	bool isPrevNum{}, isPrevBracket{};

	for (int i = 0; i < inputString.size(); ++i) {
		if (isdigit(inputString[i])) {
			isPrevNum = true;
			if (isPrevBracket) {
				outputString += "* ";
				isPrevBracket = false;
			}
		}
		else if (isOperator(inputString[i])) {
			isPrevNum = false;
			isPrevBracket = false;
		}
		else if (inputString[i] == ')') {
			isPrevBracket = true;
		}
		else if (inputString[i] == '(' && isPrevNum) {
			outputString += "* ";
			isPrevBracket = false;
			isPrevNum = false;
		}

		outputString += inputString[i];
	}
	return outputString;
}

double PostficsCalc::fromPostfics(const string& inputString) {
	if (inputString.empty()) {
		throw logic_error("ERR: Empty input string!");
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
			if (numBuffer.size() < 2) {
				throw logic_error("ERR: incorrect postfics input string!");
				return 0;
			}
			double a = numBuffer.pop_back();
			double b = numBuffer.pop_back();
			double c{};

			switch (currFragment[0]) {
			case '+': c = b + a; break;
			case '-': c = b - a; break;
			case '*': c = b * a; break;
			case '/': 
				if (a == 0) throw logic_error("ERR: division by zero!");
				c = b / a;
				break; 
			}
			numBuffer.push_back(c);
		}
	}
	if (numBuffer.size() != 1) {
		throw logic_error("ERR: incorrect postfics input string!");
		return 0;
	}
	else return numBuffer.pop_back();
}

string PostficsCalc::toPostfics(const string& inputString) {
	if (inputString.empty()) {
		throw logic_error("ERR: Empty input string!");
		return inputString;
	}
	if (stringCheck(inputString)) {
		return inputString;
	}

	string inString = comToDot(inputString);
	inString = addWS(inString);
	inString = addSkippedMult(inString);
	inString = addZeros(inString);

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

double PostficsCalc::fromNormal(const string& inputString) {
	return fromPostfics(toPostfics(inputString));
}