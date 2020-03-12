#pragma once
#include <string>
#include "Dlist.h"

class PostficsCalc
{
private:
	/*
		Проверяет, является ли данный символ оператором
		(если нет, то возвращает 0, иначе возвращает символ оператора)
	*/
	char isOperator(char symbol);

	/*
		Проверяет, является ли символ плюсом или минусом
		(если нет, то возвращает 0, иначе возвращает символ оператора)
	*/
	char isPlusMinus(char symbol);

	/*
		Проверяет, является ли символ умножением или делением
		(если нет, то возвращает 0, иначе возвращает символ оператора)
	*/
	char isMultDiv(char symbol);

	/*
		Проверяет, допущены ли в строке ошибки
		(если нет, возвращает 0, иначе position + 1 - место ошибки)
	*/
	int stringCheck(const std::string& inputString);

	/*
		Добавляет дополнительные пробелы к входной строке
	*/
	std::string addWS(const std::string& inputString);

	/*
		Добавляет дополнительные нули к входной строке
		(добавляет нули к дробным числам, нули при унарных операторах)
	*/
	std::string addZeros(const std::string& inputString);

	/*
		Меняет запятые на точки в строке
	*/
	std::string comToDot(const std::string& inputString);

	/*
		Добавляет опущенные знаки умножения 
		[ (2+5)(1+3) -> (2+5) * (1+3) ]
	*/
	std::string addSkippedMult(const std::string& inputString);

public:
	/*
		Получает строку в постфиксной форме и возвращает готовый ответ
	*/
	double fromPostfics(const std::string& inputString);

	/*
		Получает строку в нормальной форме и возвращает готовый ответ
	*/
	double fromNormal(const std::string& inputString);

	/*
		Переводит строку из обычной формы в постфиксную
	*/
	std::string toPostfics(const std::string& inputString);

	/*
		Переводит строку из постфискной формы в обычную
	*/
	// std::string toNormal(const std::string& inputString);
};

