#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class List {
	struct elem {
		T data; // list data
		elem* next; // pointer to the next element
	};
	elem* head; // head of the list
	int number_of_elements; // item count
public:
	List() : head(nullptr), number_of_elements(0) {} // class constructor
	~List() { clear(); } // class destructor
	bool isEmpty() const; // check list for void
	void push_front(const T& var); // add item to the begining of list
	void push_back(const T& var); // add item to end of list
	void pop_front(); // remove item from the beginning of the list
	void pop_back(); // remove item from the end of the list
	void insert(const T& var, const int num); // insert item into list by index
	void remove(const int num); // delete item by index
	void set(const T& var, const int num); // replacing item by index
	T at(const int num); // getting item by index
	void clear(); // delete all list items
	int get_size()const; // getting the number of list items
	T& getminimaldata();
	template <typename T> friend ostream& operator << (ostream& output_stream, List<T>& OBJECT); // list operator overload
	List& operator=(const List& obj);
};

template <class T>
bool List<T>::isEmpty() const {
	return(head == nullptr ? true : false); // if the list is empty return true
}

template <class T>
T& List<T>::getminimaldata()
{
	elem* temp_ptr = head;
	T temp = temp_ptr->data;
	while (temp_ptr->next != nullptr)
	{
		if (temp_ptr->data < temp)
			temp = temp_ptr->data;
		temp_ptr = temp_ptr->next;
	}
	return temp;
}

template <class T>
void List<T>::push_front(const T & var) {
	elem* object; // create a pointer to a class object 
	object = new elem; // allocate memory
	object->data = var; // write data in the data field of the list
	if (head == nullptr) {
		object->next = nullptr; // if the list is empty then the next item pointer is zero
		head = object; // new item becomes head of the list
		number_of_elements++; // increasing the number of elements
	}
	else {
		object->next = head; // if the list isn't empty then move the head
		head = object; // new item becomes head of the list
		number_of_elements++; // increasing the number of elements
	}
}

template <class T>
void List<T>::push_back(const T & var)
{
	elem* object; // create a pointer to a class object
	object = new elem; // allocate memory
	object->data = var; // write data in the data field of the list
	object->next = nullptr; // the next item pointer is zero

	if (head == nullptr) {
		head = object; // if the list is empty then new item becomes head of the list
		number_of_elements++; // increasing the number of elements
	}
	else {
		elem* temp = head; // create a new pointer to the head
		while (temp->next != nullptr) { // go to the end of the list
			temp = temp->next; // move to the next item
		}
		temp->next = object; // insert new item at the end
		number_of_elements++; // increasing the number of elements
	}
}

template <class T>
void List<T>::pop_front()
{
	if (isEmpty()) {
		throw logic_error("Sorry, can't remove item from empty list");
	}
	else {
		elem* temp = head; // create a new pointer to the head
		head = head->next; // move the head
		delete temp; // delete first element
		number_of_elements--; // reduce the number of elements
	}
}

template <class T>
void List<T>::pop_back()
{
	if (isEmpty()) {
		throw logic_error("Sorry, can't remove item from empty list");
	}
	else {
		elem* temp, * temp2; // create two new pointers to the beginning of the list
		temp2 = temp = head;
		while (temp->next != nullptr) { // go to the last (temp) and penultimate (temp2) elements
			temp2 = temp;
			temp = temp->next;
		}
		temp2->next = nullptr; // the penultimate element points to nullptr
		if (temp == temp2)
			head = nullptr; // when deleting the first element, head is zero
		delete temp; // delete last item
		number_of_elements--; // reduce the number of elements
	}
}

template <class T>
void List<T>::insert(const T & var, const int num)
{
	if (isEmpty()) {
		throw logic_error("Sorry, can't insert item in empty list");
	}
	if (num < 0 || number_of_elements < num) {
		throw out_of_range("Sorry, there is no element with such an index");
	}
	elem* temp = head; // create a new pointer to the head
	elem* tmp = new elem; // create a temporary pointer and allocate memory
	tmp->data = var; // write data in the data field of the list
	if (num != 1) {
		for (int i = 2; i < num; i++) // go to the previous element
			temp = temp->next;
		tmp->next = temp->next; // we shift an element instead of which it is necessary to put new item
		temp->next = tmp; // pasted item
	}
	else {
		tmp->next = temp; // move the head
		head = tmp; // new item became head
	}
	number_of_elements++; // increasing the number of elements
}

template <class T>
void List<T>::remove(const int num)
{
	if (isEmpty()) {
		throw logic_error("Sorry, can't remove item from empty list");
	}
	if (num < 0 || number_of_elements < num) {
		throw out_of_range("Sorry, there is no element with such an index");
	}
	elem* temp, * temp2; // create two new pointers
	temp = head; // new pointer to the head
	if (num != 1) {
		for (int i = 2; i < num; i++) // go to the previous element
			temp = temp->next;
		temp2 = temp->next; // temp2 indicates the item to be removed
		temp->next = temp->next->next; // move to the next item after deleting
		delete temp2; // delete element
	}
	else {
		head = temp->next; // if we remove the first element, move the head
		delete temp; // delete first element
	}
	number_of_elements--; // reduce the number of elements
}

template <class T>
void List<T>::set(const T & var, const int num)
{
	if (isEmpty()) {
		throw logic_error("Sorry, can't set item in empty list");
	}
	if (num < 0 || number_of_elements < num) {
		throw out_of_range("Sorry, there is no element with such an index");
	}
	elem* temp = head; // create a new pointer to the head
	for (int i = 1; i < num; i++) // go to the element with an index equal to num
		temp = temp->next;
	temp->data = var; // replace the item with a new one
}

template <class T>
T List<T>::at(const int num)
{
	if (isEmpty()) {
		throw logic_error("Sorry, can't receive item from empty list");
	}
	if (num < 0 || number_of_elements < num) {
		throw out_of_range("Sorry, there is no element with such an index");
	}
	elem* temp = head; // create a new pointer to the head
	for (int i = 1; i < num; i++)
		temp = temp->next; // go to the element with an index
	return(temp->data); // return item by index
}

template <class T>
void List<T>::clear()
{
	elem* temp = head; // create a new pointer to the head
	while (head != nullptr) {
		temp = head; // assign a value to a temporary variable
		head = head->next; // go to the next element
		delete temp; // delete element
	}
	number_of_elements = 0; // reset the count of the number of items
	head = nullptr; // head reset
}

template<class T>
int List<T>::get_size() const {
	return number_of_elements; // return the number of elements
}

template<class T>
 List<T>& List<T>::operator=(const List<T>& obj)
{
	 number_of_elements = obj.number_of_elements;
	 elem* temp = obj.head;
	 while (temp->next != nullptr)
	 {
		 push_back(temp->data);
		 temp = temp->next;
	 }
}

template <class T>
ostream& operator << (ostream & output_stream, List<T> & OBJECT)
{
	int element_number = 0; // item counter
	List<T> OBJ; // create class object
	OBJ.head = OBJECT.head; // copy the pointer to the head in a temporary object
	while (OBJ.head != nullptr) {
		element_number++; // current item number
		output_stream << "Element #" << element_number << ": " << OBJ.head->data << endl; // output list element
		OBJ.head = OBJ.head->next; // go to the next element
	}
	return output_stream;
}