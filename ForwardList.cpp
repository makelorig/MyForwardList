
#include <iostream>
using namespace std;

template<typename T>
class MyForList {
private:
	int size = 0;

	class Node {
	public:
		T elem;
		Node* next;
		Node(const T& value) :elem(value), next(nullptr) {};
	};
	Node* head;
public:
	MyForList() :head(nullptr) {};
	MyForList(const MyForList& otherlist) {
		if (otherlist.empty())return;
		Node* ocur = otherlist.head;
		this->push_back(ocur->elem);
		for (; ocur->next != nullptr;) {
			ocur = ocur->next;
			this->push_back(ocur->elem);
		}
		this->push_back(ocur->elem);
	}
	void push_front(const T& value) {
		Node* newNode = new Node(value);
		newNode->next = head;
		head = newNode;
		size--;
	}
	bool empty() const {
		return head == nullptr;
	}
	void pop_front() {
		if (empty()) throw out_of_range("Пусто, прямо как в твоей голове...");
		Node* buf = this->head->next;
		delete this->head;
		this->head = buf;
		size--;
	}
	void show() {
		Node* cur = head;
		if (empty()) throw out_of_range("Пусто, прямо как в твоей голове...");
		for (; cur->next != nullptr;) {
			cout << cur->elem << " ";
			cur = cur->next;
		}
		cout << cur->elem << endl;
	}
	void push_back(const T& value) {
		if (empty()) {
			head = new Node(value);
			return;
		}
		Node* cur = head;
		for (; cur->next != nullptr;) {
			cur = cur->next;
		}
		cur->next = newNode(value);
		size++;
	}
	void pop_back() {
		if (empty()) throw out_of_range("Пусто, прямо как в твоей голове...");
		Node* cur = head;
		for (; cur->next->next != nullptr;)cur = cur->next;
		delete cur->next;
		cur->next = nullptr;
		size--;
	}
	/*void indInsert(int index) {
		if (empty()) throw out_of_range("Пусто, прямо как в твоей голове...");
		Node* cur = head;
		for (; cur->next->next != nullptr;)cur = cur->next;
	}*/
	void insert_after(int index, const T& value) {
		if (empty() || index < 0) throw out_of_range("Пусто, прямо как в твоей голове...");
		Node* cur = head;
		for (int i = 0; i < index; i++)
		{
			if (cur->next == nullptr)throw out_of_range("Пусто, прямо как в твоей голове...");
			cur = cur->next;
		}
		Node* buf = cur->next;
		cur->next = new Node(value);
		cur->next->next = buf;
	}
	void emplace(int index, T& value) {
		if (empty() || index < 0) throw out_of_range("Пусто, прямо как в твоей голове...");
		Node* cur = head;
		for (int i = 0; i < index; i++)
		{
			if (cur->next == nullptr)throw out_of_range("Пусто, прямо как в твоей голове...");
		}
		cur->elem = value;
	}
	void clear() {
		if (empty())return;
		Node* cur = head;
		Node* buf = cur->next;
		for (; cur->next != nullptr;) {
			delete cur;
			cur = buf;
			buf = buf->next;
		}
		head = nullptr;
	}
	T& front() {
		return head->elem;
	}
	bool operator ==(const MyForList& otherlist) {
		Node* cur = this->head;
		Node* ocur = otherlist->head;
		for (; true;) {
			if ((cur == nullptr && ocur != nullptr) ||
				(cur != nullptr && ocur == nullptr)) return 0;
			else if (cur == nullptr && ocur == nullptr)break;
			else if (cur->elem != ocur->elem)return 0;

			cur = cur->next;
			ocur = ocur->next;
		}
		return true;
	}
	bool operator !=(const MyForList& otherlist) {
		return !(*this == otherlist);
	}

	MyForList& operator =(const MyForList& otherlist) {
		this->clear;
		if (otherlist.empty()) {
			Node* ocur = otherlist.head;
			this->push_back(ocur->elem);
			for (; ocur->next != nullptr;) {
				ocur = ocur->next;
				this->push_back(ocur->elem);
			}
			this->push_back(ocur->elem);
		}
		return *this;
	}
	class Iterator {
	private:
		Node* ptr;
	public:
		Iterator(Node* ptr) :ptr(ptr) {}
		T& operator *() const {
			return ptr->elem;
		}
		Iterator& operator++() {
			ptr=ptr->next;
			return *this;
		}
		Iterator& operator =(const Iterator& other) {
			ptr = other.ptr;
		}
		bool operator ==(const Iterator& other) {
			return this->ptr == other.ptr;
		}
		bool operator !=(const Iterator& other) {
			return this->ptr != other.ptr;
		}
		~Iterator() {
			delete ptr;
		}
	};
	Iterator begin() {
		return Iterator(head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}

	~MyForList() {
		if (empty())return;
		Node* cur = head;
		Node* buf = cur->next;
		for (; cur->next != nullptr;) {
			delete cur;
			cur = buf;
			buf = buf->next;
		}
	}
};
int main()
{
	setlocale(LC_ALL, "rus");
	MyForList<int> bigger;
	MyForList<int> igger;
	bigger.push_front(9);
	bigger.push_front(52);
	bigger.push_front(89);
	bigger.push_front(14);
	bigger.push_front(65);
	bigger.show();
	/*delete bigger;*/
	/*igger = bigger;*/
	bigger.show();
	cout << endl;
	/*igger.show();*/
	for (auto el: bigger) {
		cout << el << " ";
	}
}