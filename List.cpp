#include <iostream>
#include <exception>
#include <cstdlib>
using namespace std;

template <class T> class List {
	struct Node {
		T val_;
		Node* prev_;
		Node* next_;
		Node(Node* p = 0, Node* n = 0)
		: prev_(p), next_(n)
		{}
		Node(const T& v, Node* p = 0, Node* n = 0)
		: val_(v), prev_(p), next_(n)
		{}
	};
	Node* head_;
	Node* tail_;
	template <class t> friend ostream& operator<<(ostream&, const List<t>&);
public:
	List()
	: head_(0), tail_(0)
	{}
	List(const T& first, const T& last) 
	: head_(0), tail_(0) {
		for(T i = first;i < last;++i)
			push_back(i);
	}
	List(const List& l)
	: head_(0), tail_(0) {
		append(l);
	}
	~List() {
		clear();
	}
	class Iterator {
	protected: Node* pos_;
	public:
			Iterator(Node* pos = 0) 
			: pos_(pos)
			{}
			Iterator operator++() {
				pos_ = pos_->next_;
				return *this;
			}
			Iterator operator++(int) {
				Iterator res = *this;
				operator++();
				return res;
			}
			bool operator==(const Iterator& it) const{
				return (pos_ == it.pos_);
			}
			bool operator!=(const Iterator& it) const{
				return !operator==(it);
			}
			T& operator*() {
				return pos_->val_;
			}
			T* operator->() {
				return &operator*();
			}
			Node* node() {
				return pos_;
			}
	};
	class Const_Iterator: public Iterator {
	public:
		Const_Iterator(Node* pos = 0)
		: Iterator(pos)
		{}
		const T& operator*() {
			return Iterator::operator*();
		}
		const T* operator->() {
			return &operator*();
		}
	};
	class Reverse_Iterator: public Iterator {
	public:
			Reverse_Iterator(Node* pos = 0)
			: Iterator(pos)
			{}
			Reverse_Iterator operator++() {
				Iterator::pos_ = Iterator::pos_->prev_;
				return *this;
			}
			Reverse_Iterator operator++(int) {
				Reverse_Iterator res = *this;
				operator++();
				return res;
			}
	};
	class Const_Reverse_Iterator: public Reverse_Iterator, public Const_Iterator {
	public:
		Const_Reverse_Iterator(Node* pos = 0)
		: Reverse_Iterator(pos)
		{}
		using Reverse_Iterator::operator++;
		using Const_Iterator::operator*;
		using Const_Iterator::operator->;
	};
	Iterator begin() {
		return Iterator(head_);
	}
	Const_Iterator begin() const{
		return Const_Iterator(head_);
	}
	Iterator end() {
		return Iterator();
	}
	Const_Iterator end() const{
		return Const_Iterator();
	}
	Reverse_Iterator rbegin() {
		return Reverse_Iterator(tail_);
	}
	Const_Reverse_Iterator rbegin() const{
		return Const_Reverse_Iterator(tail_);
	}
	Reverse_Iterator rend() {
		return Reverse_Iterator();
	}
	Const_Reverse_Iterator rend() const{
		return Const_Reverse_Iterator();
	}
	bool empty() const {
		return tail_ == NULL;
	}
	size_t size() const {
		size_t i = 0;
		for(Const_Iterator it = begin();it != end();++it) 
			i++;
		return i;
	}
	void push_back(const T& val) {
		insert(end(), val);
	}
	void push_front(const T& val) {
		insert(begin(), val);
	}
	void pop_back() {
		erase(rbegin());
	}
	void pop_front() {
		erase(begin());
	}
	Iterator insert(Iterator it, const T& val) {
		if(it == end()) {
			if(empty()) {
				Node* node = new Node(val);
				head_ = node;
				tail_ = node;
				return Iterator(node);
			}
			Node* node = new Node(val, tail_);
			tail_->next_ = node;
			tail_ = node;
			return Iterator(node);
		}
		Node* aft = it.node();
		Node* bef = aft->prev_;
		Node* node = new Node(val, bef, aft);
		aft->prev_ = node;
		if(bef == 0)
			head_ = node;
		else
			bef->next_ = node;
		return Iterator(node);
	}
	Iterator erase(Iterator it) {
		if(empty())
			throw exception();
		Node* rm = it.node();
		Node* bef = rm->prev_;
		Node* aft = rm->next_;
		if(rm == head_)
			head_ = aft;
		else
			bef->next_ = aft;
		if(rm == tail_)
			tail_ = bef;
		else
			aft->prev_ = bef;
		delete rm;
		return Iterator(aft);
	}
	Iterator erase(Iterator first, Iterator last) {
		for(;first != last;)
			first = erase(first);
		return first;
	}
	T& front() {
		return head_->val_;
	}
	const T& front() const {
		return front();
	}
	T& back() {
		return head_->val_;
	}
	const T& back() const {
		return back();
	}
	void clear() {
		while(!empty())
			pop_back();
	}
	void append(const List& l) {
		for(Const_Iterator it = l.begin();it != l.end();++it)
			push_back(*it);
	}
	List& operator=(const List& l) {
		if(this != &l) {
			clear();
			append(l);
		}
		return *this;
	}
	void swap(List& l) {
		List tmp = l;
		l = *this;
		*this = tmp;
	}
};

template <class t> ostream& operator<<(ostream& out, const List<t>& l) {
	out << '{';
	for(typename List<t>::Const_Iterator it = l.begin();it != l.end();++it) 
		out << *it << ',';
	out << '}';
	return out;
}

int main (int argc, char** argv) {
	List<int> l1(atoi(argv[1]), atoi(argv[2]));
	List<int> l2(atoi(argv[3]), atoi(argv[4]));
	cout << "l1: " << l1 << endl << "l2: " << l2 << endl;	
	size_t c = 0;
	for(List<int>::Iterator it1 = l1.begin();it1 != l1.end();++it1) {
		for(List<int>::Iterator it2 = l2.begin();it2 != l2.end();++it2) {
			if(*it1 == *it2) {
				c++;
				break;
			}
		}
	}
	cout << "equal element in l1 and l2: " << c << endl;
	l1.push_back(-100);
	l2.push_back(-100);
	cout << "l1: " << l1 << endl << "l2: " << l2 << endl;	
	List<int> l(l2);
	cout << "l: " << l << endl;
	for(List<int>::Reverse_Iterator r = l1.rbegin();r != l1.rend();++r)
		l.insert(l.begin(), *r);
	cout << "l: " << l << endl;
	List<int>::Iterator bit;
	for(bit = l.begin();bit != l.end();++bit) {
		if(*bit == -100)
			break;
	}
	l.erase(bit, l.end());
	cout << "l: " << l << endl;
	return 0;
}
