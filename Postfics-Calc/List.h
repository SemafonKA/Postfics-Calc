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

	/* ������� ��� ����� ������ */
	void clear();

	/* �������� ������ ������ ������ */
	void resize(int newListSize);

	/* ������� ������������� �������� ������ � ������� pos */
	int pos_back(int pos) const {
		Node* member = listSearch(pos);
		return member->date;
	}

	/* ���������� ������������� �������� ������ � ������� pos */
	List& set(int pos, int date) {
		Node* member = listSearch(pos);
		member->date = date;
		return (*this);
	}

	/* �������� ����� ���� ������ ����� ������� pos */
	List& push(int pos, int date = 0);

	/* ������� ���� ������ �� �������� ������� pos */
	int remove(int pos);

	/* ���������� ������ ������ */
	unsigned int size() const { return m_listSize; }

	/* ����������, ������ �� ������ ��� ��� */
	bool isEmpty() const { return m_listSize == 0; }

	/* ��������� ����� ����� � ������ ������ */
	List& push_front(int date = 0) { return push(-1, date); }

	/* ��������� ����� ����� � ����� ������ */
	List& push_back(int date = 0) { return push(m_listSize - 1, date); }

	/* ���������� �������� � ��������� ����� ������ */
	int back() const { return pos_back(m_listSize - 1); }

	/* ���������� �������� � ������ ����� ������ */
	int front() const { return pos_back(0); }

	/* ������� ��������� ����� ������ */
	int pop_back() { return remove(m_listSize - 1); }

	/* ������� ������ ����� ������ */
	int pop_front() { return remove(0); }
};

