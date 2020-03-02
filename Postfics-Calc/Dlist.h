#pragma once
#include <iostream>

template<typename T>
inline void swap(T& first, T& second) {
	T tmp = first;
	first = second;
	second = tmp;
}

enum class Mode {
	LIST = 0,
	LIST_ADRESS = 1,
	LIST_ADR_FULL = 2,
	LIST_NUMBER = 3,
	LIST_NUM_ADR = 4,
	LIST_NUM_ADR_FULL = 5,
	NO_OUT = 6
};
template<typename T>
class Dlist {
private:
	class Node {
	public:
		T data{};
		Node* next{};
		Node* prev{};
	};

	Node* m_front{};
	Node* m_back{};

	int m_listSize{};

	/* ����� ������ ������ � ������� */
	class OutClass {
	private:
		Dlist* m_object{};			// �������� � ������� ������
		Mode m_mode{ Mode::LIST };	// ����� ������

	public:
		OutClass(Dlist* object) {
			m_object = object;
		}

		const int defaultLength = 15;		// ���������� ������, ��������� � ������ �� ���������
		int lineLength{ defaultLength };	// ���������� ������, ��������� � ������

		/* ������ ��������� ������ ������ */
		void mode(Mode newMode) { m_mode = newMode; }
		Mode mode(void) { return m_mode; }

		/* ����� ������ ������ ��������� (0, size - 1) */
		bool operator() (void) const {
			if (m_mode != Mode::NO_OUT && !m_object->isEmpty()) {
				Node* currentMember = m_object->m_front;
				std::cout << std::endl;
				for (int i = 0; i < m_object->m_listSize; ++i) {
					if (m_mode == Mode::LIST_NUMBER || m_mode == Mode::LIST_NUM_ADR ||
						m_mode == Mode::LIST_NUM_ADR_FULL) {
						std::cout << i << ")\t";
					}

					std::cout << currentMember->data << "\t";
					if (m_mode == Mode::LIST_ADRESS || m_mode == Mode::LIST_ADR_FULL ||
						m_mode == Mode::LIST_NUM_ADR || m_mode == Mode::LIST_NUM_ADR_FULL) {
						std::cout << "�����: [" << currentMember << "]\t";
					}
					if (m_mode == Mode::LIST_ADR_FULL || m_mode == Mode::LIST_NUM_ADR_FULL) {
						std::cout << "����������: [" << currentMember->prev << "]\t" <<
							"���������: [" << currentMember->next << "]";
					}

					if ((i + 1) % lineLength == 0 && m_mode == Mode::LIST || m_mode != Mode::LIST) std::cout << std::endl;
					currentMember = currentMember->next;
				}
				std::cout << std::endl;
				return true;
			}
			else return false;
		}

		/* ����� ������ ������ ���������� ��������� */
		bool operator() (int start, int end) {
			if (start > end) swap(start, end);
			if (start < 0) return 0;
			if (end >= m_object->m_listSize) return 0;

			if (m_mode != Mode::NO_OUT && !m_object->isEmpty()) {
				Node* currentMember = m_object->listSearch(start);
				std::cout << std::endl;
				for (int i = start; i <= end; ++i) {
					if (m_mode == Mode::LIST_NUMBER || m_mode == Mode::LIST_NUM_ADR ||
						m_mode == Mode::LIST_NUM_ADR_FULL) {
						std::cout << i << ")\t";
					}

					std::cout << currentMember->data << "\t";
					if (m_mode == Mode::LIST_ADRESS || m_mode == Mode::LIST_ADR_FULL ||
						m_mode == Mode::LIST_NUM_ADR || m_mode == Mode::LIST_NUM_ADR_FULL) {
						std::cout << "�����: [" << currentMember << "]\t";
					}
					if (m_mode == Mode::LIST_ADR_FULL || m_mode == Mode::LIST_NUM_ADR_FULL) {
						std::cout << "����������: [" << currentMember->prev << "]\t" <<
							"���������: [" << currentMember->next << "]";
					}

					if ((i + 1) % lineLength == 0 && m_mode == Mode::LIST || m_mode != Mode::LIST) std::cout << std::endl;
					currentMember = currentMember->next;
				}
				std::cout << std::endl;
				return true;
			}
			else return false;
		}
	};

	void listCheck() const {
		Node* member = m_front;
		for (int i = 0; i < m_listSize; ++i) {
			if (member == nullptr) {
				std::cerr << "ERR: error in resize list";
				throw std::logic_error("ERR: error in resize list");
			}
			member = member->next;
		}
	}

	Node* listSearch(int pos) const {
		if (pos >= m_listSize) {
			std::cerr << "ERR: out of range";
			throw std::logic_error("ERR: out of range");
			return nullptr;
		}
		if (pos < 0)				return nullptr;
		if (pos == 0)				return m_front;
		if (pos == m_listSize - 1)	return m_back;

		Node* member{};
		if (pos <= m_listSize / 2) {
			member = m_front;

			for (int i = 0; i < pos; ++i) {
				member = member->next;
			}
		}
		else {
			member = m_back;

			for (int i = m_listSize - 1; i > pos; --i) {
				member = member->prev;
			}
		}

		return member;
	}

public:
	Dlist() {

	}
	~Dlist() {
		clear();
	}

	/* ����� ������ ������ */
	OutClass out{ this };

	/* ������� ��� ����� ������ */
	void clear() {
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

	/* ������� �������� ������ � ������� pos (������) */
	T& pos_back(int pos) {
		Node* member = listSearch(pos);
		return member->data;
	}
	/* ������� �������� ������ � ������� pos (������) */
	T& operator[] (int pos) {
		return pos_back(pos);
	}

	/* ���������� ������������� �������� ������ � ������� pos */
	Dlist& set(int pos, T data) {
		Node* member = listSearch(pos);
		member->data = data;
		return (*this);
	}

	/* �������� ����� ���� ������ ����� ������� pos */
	Dlist& push(int pos, T data = 0) {
		Node tmpNode{ T{}, m_front };								// �����, �������������� ������� ����� 
		Node* member = (pos == -1) ? &tmpNode : listSearch(pos);	// �����, �������������� ������ �����	
		Node* nextMember = member->next;

		member->next = new Node;
		member->next->prev = (pos == -1) ? (nullptr) : (member);
		member->next->data = data;

		member->next->next = nextMember;
		if (nextMember == nullptr) { m_back = member->next; }
		if (pos < 0) { m_front = member->next; }
		++m_listSize;

		return (*this);
	}

	/* ������� ���� ������ �� �������� ������� pos */
	T remove(int pos) {
		if (isEmpty()) {
			throw std::logic_error("ERR: list is empty!");
			return 0;
		}
		Node* prevMember = listSearch(pos - 1);
		if (prevMember != nullptr) {				// ���� ������ ����� ��������� �� � ������
			Node* member = prevMember->next;
			T data = member->data;

			prevMember->next = member->next;
			if (pos != m_listSize - 1) member->next->prev = member->prev;
			delete member;

			if (pos == m_listSize - 1) m_back = prevMember;
			--m_listSize;

			return data;
		}
		else {										//	if (prevMember != nullptr)									
			T data = m_front->data;
			Node* nextMember = m_front->next;
			delete m_front;

			m_front = nextMember;
			if (m_listSize > 1) m_front->prev = nullptr;
			--m_listSize;

			return data;
		}
	}

	/* ���������� ������ ������ */
	unsigned int size() const { return m_listSize; }

	/* ����������, ������ �� ������ ��� ��� */
	bool isEmpty() const { return m_listSize == 0; }

	/* ��������� ����� ����� � ������ ������ */
	Dlist& push_front(T data = 0) { return push(-1, data); }

	/* ��������� ����� ����� � ����� ������ */
	Dlist& push_back(T data = 0) { return push(m_listSize - 1, data); }

	/* ���������� �������� � ��������� ����� ������ (������) */
	T& back() { return pos_back(m_listSize - 1); }

	/* ���������� �������� � ������ ����� ������ (������) */
	T& front() { return pos_back(0); }

	/* ������� ��������� ����� ������ */
	T pop_back() { return remove(m_listSize - 1); }

	/* ������� ������ ����� ������ */
	T pop_front() { return remove(0); }

	/* ������ ��� ����� ������ ������� (��� �����������) */
	bool swap(int pos1, int pos2) {
		if (pos1 == pos2)			return true;
		if (pos1 > pos2)			swap(pos1, pos2);
		if (pos2 >= m_listSize)		return false;

		Node* elem1 = listSearch(pos1);
		Node* elem2 = listSearch(pos2);
		Node* prev1 = elem1->prev;
		Node* next1 = elem1->next;
		Node* prev2 = elem2->prev;
		Node* next2 = elem2->next;

		elem1->next = next2;
		elem1->prev = prev2;

		elem2->next = next1;
		elem2->prev = prev1;

		if (prev1) prev1->next = elem2;
		else m_front = elem2;
		next1->prev = elem2;

		if (next2) next2->prev = elem1;
		else m_back = elem1;
		prev2->next = elem1;

		return true;
	}
};