#include "List.h"

void List::listCheck() {
	Node* member = m_front;
	for (int i = 0; i < m_listSize; i++) {
		if (member == nullptr) throw std::logic_error("ERR: error in resize list");
		member = member->next;
	}
}

List::Node* List::listSearch(int pos) const {
	if (pos >= m_listSize)		throw std::logic_error("ERR: out of range");
	if (pos < 0)				return nullptr;
	if (pos == 0)				return m_front;
	if (pos == m_listSize - 1)	return m_back;

	Node* member = m_front;

	for (int i = 0; i < pos; i++) {
		member = member->next;
	}

	return member;
}

void List::clear() {
	if (!isEmpty()) {
		Node* member = m_front;
		Node* nextMember;
		for (int i = 0; i < m_listSize; i++) {
			nextMember = member->next;
			delete member;
			member = nextMember;
		}
		m_front = nullptr;
		m_back = nullptr;
		m_listSize = 0;
	}
}

void List::resize(int newListSize) {
	m_listSize = newListSize;

	if (!isEmpty()) {
		if (m_front == nullptr) { m_front = new Node; }

		Node* member = m_front;
		Node* nextMember = m_front->next;
		for (int i = 1; i < m_listSize; i++) {
			if (nextMember == nullptr) {
				member->next = new Node;
				nextMember = member->next;
			}
			member = nextMember;
			nextMember = member->next;
		}
		m_back = member;

		while (nextMember != nullptr) {
			member = nextMember;
			nextMember = member->next;
			delete member;
		}

		listCheck();
	}
}

List& List::push(int pos, int date) {
	Node tmpNode{ 0, m_front };									// Звено, предшествующее первому звену 
	Node* member = (pos == -1) ? &tmpNode : listSearch(pos);	// Звено, предшествующее новому звену	
	Node* nextMember = member->next;

	member->next = new Node;
	member->next->date = date;

	member->next->next = nextMember;
	if (nextMember == nullptr) { m_back = member->next; }
	if (pos < 0) { m_front = member->next; }
	++m_listSize;

	return (*this);
}

int List::remove(int pos) {
	if (isEmpty()) {
		throw std::logic_error("ERR list is empty!");
		return 0;
	}
	Node* prevMember = listSearch(pos - 1);
	if (prevMember != nullptr) {				// Если нужное звено находится не в начале
		Node* member = prevMember->next;
		int date = member->date;

		prevMember->next = member->next;
		delete member;

		if (pos == m_listSize - 1) m_back = prevMember;
		--m_listSize;

		return date;
	}
	else {										//	if (prevMember != nullptr)									
		int date = m_front->date;
		Node* nextMember = m_front->next;
		delete m_front;

		m_front = nextMember;
		--m_listSize;

		return date;
	}
}