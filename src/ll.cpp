#include "ll.h"
#include <vector>

using namespace std;
namespace snakelinkedlist {
	//MODIFIERS

	//given during lecture:  https://courses.engr.illinois.edu/cs126/sp2018/slides/L20-Big5Lists.pdf
	//using given code for : push_front, pop_front, and pop_back
	void LinkedList::push_front(SnakeBodySegment value) {
		ListNode *new_node = new ListNode(value);
		new_node->next_ = head_;
		head_ = new_node;
		length++;
	}

	void LinkedList::push_back(SnakeBodySegment value) {
		if (!head_) {
			push_front(value);
		}
		else {
			ListNode *tail = head_;
			while (tail->next_) {
				tail = tail->next_;
			}
			ListNode *new_node = new ListNode(value);
			tail->next_ = new_node;
			length++;
		}
	}

	void LinkedList::pop_front() {
		if (!head_) {
			return;
		}
		ListNode *tmp = head_;
		if (!head_->next_) {
			head_ = nullptr;
		}
		else {
			length--;
			head_ = head_->next_;
		}
		delete tmp;
	}

	void LinkedList::pop_back() {
		if (!head_) {
			return;
		}
		ListNode *remove_next = head_;
		while (remove_next->next_ && remove_next->next_->next_) {
			remove_next = remove_next->next_;
		}
		delete remove_next->next_;
		remove_next = nullptr;
		length--;
	}

	void LinkedList::RemoveNth(int n) {
		if (n == 0) {
			pop_front();
		}
		else if (n == size() - 1) {
			pop_back();
		}
		else if (n < 0 || n >= size()) {
			return;
		}
		else {
			ListNode *current = head_;

			//iterate to get current to the nth node
			for (int counter = n - 1; counter > 0; counter--) {
				current = current->next_;
			}
			//now point previous to the next of the current and take the nth element out
			ListNode *link = current->next_->next_;
			delete current->next_;
			current->next_ = link;
			length--;
		}
	}

	void LinkedList::clear() {
		ListNode *current = head_;
		ListNode *next;
		while (current != nullptr) {
			next = current->next_;
			delete current;
			current = next;
		}
		length = 0;
	}

	//ACCESSORS

	SnakeBodySegment LinkedList::front() const {
		if (size() == 0) {
			return SnakeBodySegment();
		}
		return SnakeBodySegment(head_->data_);
	}

	SnakeBodySegment LinkedList::back() const {
		if (size() == 0) {
			return SnakeBodySegment();
		}

		ListNode *current = head_;
		while (current->next_ != nullptr) {
			current = current->next_;
		}
		return current->data_;
	}

	int LinkedList::size() const {
		return length;
	}

	std::vector<SnakeBodySegment> LinkedList::GetVector() const {
		ListNode *current = head_;
		vector<SnakeBodySegment> snake_data;
		while (current != nullptr) {
			snake_data.push_back(current->data_);
			current = current->next_;
		}
		return snake_data;
	}

	bool LinkedList::empty() const {
		if (size() == 0) {
			return true;
		}
		return false;
	}

	std::ostream &operator<<(std::ostream &os, const LinkedList &list) {
		ListNode *current = list.head_;
		if (list.size() == 1) {
			os << current->data_;
		}
		else {
			while (current && current->next_) {
				os << current->data_ << ", ";
				current = current->next_;
			}
			if (list.size() > 1) {
				os << current->data_;
			}
		}
		return os;
	}


	bool LinkedList::operator==(const LinkedList &rhs) const {
		ListNode *current = rhs.head_->next_;
		while (current != nullptr) {
			if (rhs.head_ != current) {
				delete current;
				return false;
			}
			current = current->next_;
		}
		return true;
	}

	bool operator!=(const LinkedList &lhs, const LinkedList &rhs) {
		if (rhs == lhs) {
			return false;
		}
		return true;
	}

	//DEFAULT CONSTRUCTOR
	LinkedList::LinkedList() : head_(NULL), length(0) {};

	//INITALIZE FROM VECTOR
	LinkedList::LinkedList(const std::vector<SnakeBodySegment> &values) : LinkedList() {
		if (values.size() > 0) {
			for (int i = 0; i < values.size(); i++) {
				push_back(values.at(i));
			}
		}
	}

	//BIG 5
	//Delete LinkedList
	LinkedList::~LinkedList() {
		clear();
		head_ = nullptr;
	}

	//Deep copy: used this link for inspiration:  https://stackoverflow.com/questions/40320856/linked-list-deep-copy-constructor
	LinkedList::LinkedList(const LinkedList &source) : LinkedList() {
		if (source.head_) {
			head_ = new ListNode(*source.head_);
			ListNode *current = head_;
			ListNode *original = source.head_;

			while (original->next_) {
				//current->next_ = new ListNode(original->data_);
				original = original->next_;
				current->next_ = original;
				current = current->next_;
			}
		}
		else {
			head_ = nullptr;
		}
	}

	//Move constructor
	LinkedList::LinkedList(LinkedList &&source) noexcept : LinkedList() {
		length = source.length;
		head_ = source.head_;
		head_ = nullptr;
		source.length = 0;
	}

	//Copy assignment operator
	LinkedList &LinkedList::operator=(const LinkedList &source) {
		if (this == &source) {
			return *this;
		}
		else {
			head_ = source.head_;
			ListNode *current = head_;
			ListNode *original = source.head_;

			while (original->next_) {
				current->next_ = new ListNode(original->data_);
				original = original->next_;
				current = current->next_;
			}
			return *this;
		}
	}


	//Move assignment operator
	LinkedList &LinkedList::operator=(LinkedList &&source) noexcept {
		if (this == &source) {
			return *this;
		}
		else {
			delete head_;
			head_ = source.head_;
			source.head_ = nullptr;
			return *this;
		}
	}

} // namespace snakelinkedlist
