#pragma once
#include <iostream>

class List
{
public:
	struct Node {
		int	date{};
		Node* next{ nullptr };
	};

private:
	Node* m_front{ nullptr };
	Node* m_back{ nullptr };

	int m_listSize{ };

	void listCheck();

	Node* listSearch(int pos) const;

public:
	List() {

	}
	List(unsigned int listSize) {
		resize(listSize);
	}
	~List() {
		clear();
	}

	/* Удаляет все члены списка */
	void clear();

	/* Изменить полный размер списка */
	void resize(int newListSize);

	/* Вернуть целочисленное значение списка в позиции pos */
	int pos_back(int pos) const {
		Node* member = listSearch(pos);
		return member->date;
	}

	/* Установить целочисленное значение списка в позиции pos */
	List& set(int pos, int date) {
		Node* member = listSearch(pos);
		member->date = date;
		return (*this);
	}

	/* Вставить новый член списка после позиции pos */
	List& push(int pos, int date = 0);

	/* Удалить член списка из заданной позиции pos */
	int remove(int pos);

	/* Возвращает размер списка */
	unsigned int size() const { return m_listSize; }

	/* Возвращает, пустой ли список или нет */
	bool isEmpty() const { return m_listSize == 0; }

	/* Добавляет новое звено в начало списка */
	List& push_front(int date = 0) { return push(-1, date); }

	/* Добавляет новое звено в конец списка */
	List& push_back(int date = 0) { return push(m_listSize - 1, date); }

	/* Возвращает значение в последнем звене списка */
	int back() const { return pos_back(m_listSize - 1); }

	/* Возвращает значение в первом звене списка */
	int front() const { return pos_back(0); }

	/* Удаляет последнее звено списка */
	int pop_back() { return remove(m_listSize - 1); }

	/* Удаляет первое звено списка */
	int pop_front() { return remove(0); }
};

