//--------------------------------------------
// NAME: Ivo Stratev
// CLASS: XIb
// NUMBER: 16
// PROBLEM: #2
// FILE NAME: vector.cc
// FILE PURPOSE:
// Make an implementation of the abstract class Vector.
//---------------------------------------------
#include <iostream>  // In order to use the standart input, outupt and error streams of c++.
#include <stdexcept> // In order to throw standart exceptions such as the base class exception and the class out_of_range
// wich inherites from exception.
#include <cstdlib>  // In order to conver command line arguments from strings to integers.
using namespace std; // Using std in order to avoid writing std:: before cout, out_of_range
// and all other things defined under the std scope.

template<typename T> class Vector {
	T* data_; // A private member that stores the Vector value in the heap (the dynamic memory)
	// wich allows the value to change it's size.
	size_t capacity_; // A private member used to hold the size of memory block of the template argument
	// currrently alocated for the coresponding instance.
	size_t size_; // A private member used to indicate the current size of the coresponding instance.
	template <typename Type> friend ostream& operator<<(ostream&, const Vector<Type>&);
public:
    //--------------------------------------------
	// FUNCTION: VEctor
	// Inicializate new blank instance of the class by inicializating capacity_ with capacity,
	// size_ with 0 and allocates new memory block of the template argument, capacity for data_.
	// Also used as default constructor of the class with the default value of the argument equal 1
	// so memory blocks of the class can be created wich requires a default constructor to be done.
	// PARAMETERS:
	// capacity
	// capacity is used to determinate the memory block size.
	//----------------------------------------------
	Vector(size_t capacity = 1)
	: size_(0), capacity_(capacity), data_(new T[capacity]) // Inicializating capacity_ with capacity (not with capacity_
	// since if it was with capacity_ it would throw bad_alloc simply because the inicializating order is the one in wich 
	// non static members are declared),
    // size_ with 0 and allocates new memory block of the tempalte argument for data_ capacity long.
	{}
	//--------------------------------------------
	// FUNCTION: Vecotr (overloaded constructor)
	// Creates ne instance of the class with values in the range [first, last), inicializates size_ with the size of the range
	// and capacity with one more than size_, data_ with new memory block of the tempalte argument, capacity_ long and inicializate it.
	// PARAMETERS:
	// first and last
	// first is used as starting value and last is used to indicate the alst value for the object.
	//----------------------------------------------
	Vector(const T& first, const T& last) 
	: size_(0), capacity_(0) { // Seting starting values for size_ adn capacity_ = 0 so they can be change later..
		for(T count = first;count < last;++count) // Loop througth first and last the template argument must have 
		// valid prefix operator++!
			size_++; // Increment size_ for each element.
		capacity_ = size_ + 1; // Seting capacity_ to one more than size_.
		data_ = new T[capacity_]; // Allocating new memory block, capacity_ long for data_ from the template argment type.
		size_t i = 0; // Defining a counter i and inicializating it with 0.
		for(T count = first;count < last;++count)  // Looping once again througth first and last.
			data_[i++] = count; //Inicializating the element with ofset i from data_.
	}	
	//--------------------------------------------
	// FUNCTION: Vector (overloaded constructor wich is also the copy-constructor of the class)
	// Defining valid copy-constructor for the class, because it's using dinamyc memory to store the value
	// and if it's not a valid one when inicializating new instance of the class with allready created one
	// both will point the same memory block.
	// PARAMETERS:
	// vector
	// A read-only reference to an object of the class wich is going to be used
	// to inicializate new instance as a copy of the passed object.
	//----------------------------------------------
	Vector(const Vector& vector)
	: capacity_(vector.capacity_), size_(vector.size_), data_(new T[vector.capacity_]) { // Inicializates capacity_ and size_
	// with  the passed object capacity_ and size_ and allocates capacity_ long memory block of the tempalte argument for data_.

		for(size_t i = 0;i < size_;++i) // Copying the value of the passed argument into newly created instance.
			data_[i] = vector.data_[i];
	}
	//--------------------------------------------
	// FUNCTION: ~Vector (destructor)
	// Used to destory an instance of the class when is no longer needed or goes out of scope by deallocating
	// he memory used for data_ because the destructor generated by the compilator isn't valid since dynamic memory
	// is used for storing data_.
	// PARAMETERS:
	// None.
	//----------------------------------------------
	~Vector() {
		delete [] data_; // Dealocating the memory used to store the instance value into data_. 
	}
	//--------------------------------------------
	// FUNCTION: size
	// Returns size_ value.
	// PARAMETERS:
	// None.
	//----------------------------------------------
	size_t size() const {
		return size_; // Returning size_.
	}
	//--------------------------------------------
	// FUNCTION: capacity
	// Returns capacity_ value.
	// PARAMETERS:
	// None.
	//----------------------------------------------
	size_t capacity() const {
		return capacity_; // Returning capacity_.
	}
	//--------------------------------------------
	// FUNCTION: empty
	// Returns true if the insance of the class is empty (with size_ that equals 0) else returns false.
	// PARAMETERS:
	// None.
	//----------------------------------------------
	bool empty() const {
		return (size_ == 0); // Returning does size_ equals 0.
	}
//--------------------------------------------
	// FUNCTION: clear
	// Clears the instance by setting size_ to 0, capacity_ to 1 and making data_ point to new dynamic char.
	// PARAMETERS:
	// None.
	//----------------------------------------------
	void clear() {
		delete [] data_; // Deallocating the memory block used for storing data_.
		size_ = 0;  // Resets size_.
		capacity_ = 1;  // Setting capacity_ to one.
		data_ = new T;   // Allocate new type of the tempalte argument for data_.
	}
	//--------------------------------------------
	// FUNCTION: operator=
	// If the operand on the left side is defirent than the one on the rigth assigns
	// the value of the one on the rigth to the one on the left because the class is using
	// dynamic memory block to store it's value and the operator generated by the compilator isn't valid.
	// PARAMETERS:
	// vector.
	// vector is used for the assigment.
	//----------------------------------------------
	Vector& operator=(const Vector& vector) {
		if(this != &vector) { //If the operant on the left is deferent from the one on the rigth
		// (avoiding string = string) simply because if this check inst' perfore the data_ will be
		// dealocated and afther a try for copying htat same data_ will be made and an error will ocure.
			delete [] data_; // Deallocating the meomory block that stores the value of the class in data_.
			size_ = vector.size_; // Copying the argument's size_.
			capacity_ = vector.capacity_; // Alse copying it's capacity_ since a direct copy is requested.
			data_ = new T[capacity_]; // Allocating new memory block for data_ capacity_ long.
			for(size_t i = 0;i < size_;++i) // Coppying the values for the argument to the current instance.
				data_[i] = vector.data_[i];
		}
		return *this; // And returning reference to the current object.
	}
	//--------------------------------------------
	// FUNCTION: operator[]
	// Return the value with ofset the argument index from data_ if index is less than size_ else throws
	// standtart out_of_range exception.
	// PARAMETERS:
	// index
	// index is used to return the element on that index.
	//----------------------------------------------
	T& operator[](size_t index) {
		if(index >= size_)  // If index isn't valid index throws standart out_of_range exception.
			throw out_of_range("Invalid index"); // Throws standart out_of_range exception.
		return data_[index]; // If the program control isn't redirected to out_of_range returns data_[index].
	}
	//--------------------------------------------
	// FUNCTION: operator[] (overloaded)
	// Return the value with ofset the argument index from data_ if index is less than size_ else throws
	// standtart out_of_range exception this is and overloaded version of operator[] that returns constandt reference
	// and it's used to constant instances of the class only (the desision is made by the compilator during compilation time).
	// PARAMETERS:
	// index
	// index is used to return the element on that index.
	//----------------------------------------------
	const T& operator[](size_t index) const{
		return operator[](index);
	}
	//--------------------------------------------
	// FUNCTION: front
	// Returns reference to the first element of an instance.
	// PARAMETERS:
	// None.
	//--------------------------------------------
	T& front() {
		return *data_;  // Dereferencing the memory that data_ points to.
	}
	//--------------------------------------------
	// FUNCTION: front (overloaded)
	// Returns  constant reference to the first element of an instance this method is used only on
	// constant objects.
	// PARAMETERS:
	// None.
	//--------------------------------------------
	const T& front() const{
		return front(); // Retrunting a constant reference to what the non-cosnt variant returns
		// the magic is this that if the object is cosntant the non-const method will get a constant
		// value and it will return a reference to that wich will than be converted to constant reference.
	}
	//--------------------------------------------
	// FUNCTION: back
	// Returns reference to the last element of an instance.
	// PARAMETERS:
	// None.
	//--------------------------------------------
	T& back() {
		return *(data_ + size_ - 1); // Dereferencing the memory that data_ with an ofset (size_ + 1) points to.
	}
	//--------------------------------------------
	// FUNCTION: back (overloaded)
	// Returns  constant reference to the first element of an instance this method is used only on
	// constant objects.
	// PARAMETERS:
	// None.
	//--------------------------------------------
	const T& back() const{
		return back(); //Same trick made as front() but returning a constant reference to the last element.
	}
	//--------------------------------------------
	// FUNCTION: ensure_capacity
	// Checks if the requested increase of the block is avalible or not and if isn't it makes it.
	// number
    // number is used to request the increasment.
	//----------------------------------------------
	void ensure_capacity(size_t number = 1) {
		int check = capacity_ - (size_ + number); // Performing a calcolation to see how much space isn't avalible.
		if(check < 0) { // Performing a check to see if some space isn't avalible.
			T* old_data = data_; // Copy the starting adress of data_.
			capacity_ += (check *= -1); // Increase capacity with the space  that isn't avalible.
			data_ = new T[capacity_]; // Allocating new momory block for data_ capacity_ long.
			for(size_t i = 0; i < size_;++i) // Saving the old value again to data_.
				data_[i] = old_data[i];
			delete [] old_data; // Deallocating the old memory block used to store data_.
		}
	}
	// FUNCTION: push_back
	// Adding an element at the end of the trace of data_ by efectivly incrising the container size with 1.
	// PARAMETERS:
	// val
	// val is the value that's gonna be added to the current object.
	//----------------------------------------------
	void push_back(const T& val) {
		ensure_capacity(); // Check does 1 space is avalible if not add one.
		data_[size_++] = val; // Add val at the end and increment size_.
	}
	// FUNCTION: push_back
	// Removing the last element by efectivly decrasing the container size with 1.
	// PARAMETERS:
	// None
	void pop_back() {
		if(empty()) // If no values can be poped throws a standart base class from wich all other
		// eception classes inherit from: exception.
			throw exception();
		size_--; // Reduce size with one.
	}
	class Iterator {
	protected:	T* pos_; // A protected member (protected so other iterator classes can inherit Iterator and still have acces to pos_), pointer that's gonna points to a single element of an instance.
	public:
	    //--------------------------------------------
		// FUNCTION: Iterator (constructor and default constructor of the class)
		// Inicializates where to point pos_ default value is NULL ptr or 0.
		// PARAMETERS:
		// pos
		// position is used as the position to where pos_ needs to point to.
		//----------------------------------------------
		Iterator(T* pos = 0)
		: pos_(pos) // Inicializating pos_.
		{}
		//--------------------------------------------
		// FUNCTION: operator++ (prefix)
		// Makes pos_ point to one afther where currently is pointing to.
		// PARAMETERS:
		// None.
		//----------------------------------------------
		Iterator operator++() {
			pos_++; // Increment pos_.
			return *this; // and returning the current object afther the repostition.
		}
		//--------------------------------------------
		// FUNCTION: operator++ (postfix)
		// Makes pos_ point to one afther where currently is pointing to but returning 
		// the current position by memory copying the object.
		// PARAMETERS:
		// None (a fictive one just so the compilator knows wich one operator to predifine).
		//----------------------------------------------
		Iterator operator++(int) {
			Iterator result(pos_); // Memory copying the current instance.
			pos_++; // Increment pos_.
			return result; // Returning the copy.
		}
		//--------------------------------------------
		// FUNCTION: operator==
		// Compeare two instances and returns does they are equal.
		// PARAMETERS:
		// iterator
		// iterator is the object with wich the comparearsion is made.
		//----------------------------------------------
		bool operator==(const Iterator& iterator) const{
			return (pos_ == iterator.pos_); // Returning does the operand on left is equal to 
			// the one on rigth.
		}
		//--------------------------------------------
		// FUNCTION: operator!=
		// Compear two instances and returns does they aren't equal.
		// PARAMETERS:
		// iterator
		// iterator is the object with wich the comparearsion is made.
		//----------------------------------------------
		bool operator!=(const Iterator& iterator) const{
			return !(operator==(iterator)); // Returning does the operand on left isn't equal to 
			// the one on rigth by inverting the result from performing operator==.
		}
		//--------------------------------------------
		// FUNCTION: operator*
		// Returns the value at wich the instance is pointing to at an instance of Vector.
		// PARAMETERS:
		// None
		//----------------------------------------------
		char& operator*() {
			return *pos_; // Return the value by dereferencing position_.
		}
		//--------------------------------------------
		// FUNCTION: operator->
		// Returns the pointer at wich the instance is pointing to at an instance of Vector.
		// PARAMETERS:
		// None
		//----------------------------------------------
		T* operator->() {
			return pos_; // Return pos_.
		}
	};
	class Const_Iterator: public Vector::Iterator {
	public:
	    //--------------------------------------------
		// FUNCTION: Const_Iterator (constructor and default constructor of the class)
		// Inicializates where to point pos_ default value is NULL ptr or 0 by using Iterator's constructor.
		// PARAMETERS:
		// pos
		// position is used as the position to where pos_ needs to point to.
		//----------------------------------------------
		Const_Iterator(T* pos = 0)
		: Iterator(pos)
		{}
		const T& operator*() {
			return *(Iterator::pos_);
		}
		const T* operator->() {
			return *(Iterator::pos_);
		}
	};
	class Reverse_Iterator: public Vector::Iterator {
	public:
	     //--------------------------------------------
		// FUNCTION: Reverse_Iterator (constructor and default constructor of the class)
		// Inicializates where to point pos_ default value is NULL ptr or 0 by using Iterator's constructor.
		// PARAMETERS:
		// pos
		// position is used as the position to where pos_ needs to point to.
		//----------------------------------------------
		Reverse_Iterator(T* pos = 0)
		: Iterator(pos)
		{}
		Reverse_Iterator operator++() {
			Iterator::pos_--;
			return *this;
		}
		Reverse_Iterator operator++(int) {
			Reverse_Iterator res(Iterator::pos_);
			Iterator::pos_--;
			return res;
		}
	};
	class Const_Reverse_Iterator: public Vector::Const_Iterator, public Vector::Reverse_Iterator {
	public:
	    //--------------------------------------------
		// FUNCTION: Const_Reverse_Iterator (constructor and default constructor of the class)
		// Inicializates where to point pos_ default value is NULL ptr or 0 by using Reverse_Iterator's and Const_Iterator's constructors.
		// PARAMETERS:
		// pos
		// position is used as the position to where pos_ needs to point to.
		//----------------------------------------------
		Const_Reverse_Iterator(T* pos)
		: Reverse_Iterator(pos)
		{}	
		using Const_Iterator::operator*;
		using Const_Iterator::operator->;
	};
	Iterator begin() {
		return Iterator(data_);
	}
	Iterator end() {
		return Iterator(data_ + size_);
	}
	Const_Iterator begin() const{
		return Const_Iterator(data_);
	}
	Const_Iterator end() const{
		return Const_Iterator(data_ + size_);
	}
	Reverse_Iterator rbegin() {
		return Reverse_Iterator(data_ + (size_ - 1));
	}
	Reverse_Iterator rend() {
		return Reverse_Iterator(data_ - 1);
	}
	Const_Reverse_Iterator rbegin() const{
		return Const_Reverse_Iterator(data_ + (size_ - 1));
	}
	Const_Reverse_Iterator rend() const{
		return Const_Reverse_Iterator(data_ - 1);
	}
	Iterator insert(Iterator pos, const T& val) {
		T* old_data = data_;
		if(capacity_ == size_)
			capacity_++;
		data_ = new T[capacity_];
		size_t i;
		for(i = 0;old_data + i != pos.operator->();++i)
			data_[i] = old_data[i];
		data_[i] = val;
		Iterator res(data_ + i);
		for(;i < size_;++i)
			data_[i + 1] = old_data[i];
		size_++;
		delete [] old_data;
		return res; 
	}
	Iterator erase(Iterator pos) {
		 size_t i = 0;
		 int new_pos = -1;
	    for(Iterator it = begin();it != end();++it) {
	        if(it != pos) {
    	        data_[i] = *it;
    	        ++i;
    	   } else
    	        new_pos = i;
	   }
	   size_--;
	   if(new_pos == -1)
	    return end();
	    return Iterator(data_ + new_pos);
	}
	Iterator erase(Iterator first, Iterator last) {
	    size_t i = 0;
	    for(Iterator it = begin();it != first;++it) {
	        data_[i] = *it;
	        ++i;
	   }
	   size_t pos = i;
	   for(Iterator it2(last.operator->());it2 != end;++it2) {
	        data_[i] = *it2;
	        ++i;
	   }
	   size_ = i;
	    return Iterator(data_ + pos);
	}
};

template <typename Type> ostream& operator<<(ostream& out, const Vector<Type>& vector) {
	cout << '{';
	for(size_t i = 0;i < vector.size_;++i)
		cout << vector.data_[i] << ", ";
	cout << '}';
	return out;
}

int main(int argc, char** argv) {
	Vector<int> v1(atoi(argv[1]), atoi(argv[2]));
	Vector<int> v2(atoi(argv[3]), atoi(argv[4]));
	cout << "v1: " << v1 << endl;
	cout << "v2: " << v2 << endl;
	size_t count = 0;
	for(Vector<int>::Iterator it1 = v1.begin();it1 != v1.end();++it1) {
		for(Vector<int>::Iterator it2 = v2.begin();it2 != v2.end();++it2) {
			if(*it1 == *it2) {
				count++;
				break;
			}
		}
	}
	cout << "equal element in v1 and v2: " << count << endl;
	v1.push_back(-100);
	v2.push_back(-100);
	cout << "v1: " << v1 << endl;
	cout << "v2: " << v2 << endl;
	Vector<int> v(v2);
	cout << "v: " << v << endl;
	for(Vector<int>::Reverse_Iterator rit = v1.rbegin();rit != v1.rend();++rit)
		v.insert(v.begin(), *rit);
	cout << "v: " << v << endl;
	Vector<int>::Iterator bit = v.begin();
	for(;bit != v.end();++bit) {
		if(*bit == -100)
			break;
	}
	v.erase(bit, v.end());
	v.erase(++++v.begin());
	cout << "v: " << v << endl;
	return 0;
}
