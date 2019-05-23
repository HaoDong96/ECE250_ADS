/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( new Double_node() ),
list_tail( new Double_node() ),
list_size( 0 )
{
	// Enter your implementation here
	list_head->next_node = list_tail;
	list_tail->previous_node = list_head;

}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( new Double_node() ),
list_tail( new Double_node() ),
list_size( 0 )
{
	// Enter your implementation here
    list_head->next_node = list_tail;
    list_tail->previous_node = list_head;
    for ( auto *ptr = list.begin(); ptr != list.end(); ptr = ptr->next() ) {
        push_back(ptr->node_value);
    }
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( new Double_node() ),
list_tail( new Double_node() ),
list_size( 0 )
{
	// Enter your implementation here
    list_head->next_node = list_tail;
    list_tail->previous_node = list_head;
    swap(list);
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// Enter your implementation here
	while( !empty()){
	    pop_front();
	}
	delete(list_head);
	delete(list_tail);
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	// Enter your implementation here
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// Enter your implementation here
	return list_size == 0;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// Enter your implementation here
	if(size() == 0)
	    throw underflow();
	return list_head->next()->value();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// Enter your implementation here
    if(size() == 0)
        throw underflow();
    return list_tail->previous()->value();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	// Enter your implementation here
    return list_head->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	// Enter your implementation here
	return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	// Enter your implementation here
	return list_tail->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	// Enter your implementation here
	return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	// Enter your implementation here
	auto* ptr = begin();
	while(ptr->value()!=obj && ptr != end()){
	    ptr = ptr->next();
	}
	return ptr;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// Enter your implementation here
	int counter = 0;
    for ( auto *ptr = begin(); ptr != end(); ptr = ptr->next() ) {
        if(ptr->value() == obj)
            counter++;
    }
	return counter;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
	auto newNode = new Double_node(obj, list_head, list_head->next());
	list_head->next_node = newNode;
    newNode->next_node->previous_node = newNode;
	list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
    auto newNode = new Double_node(obj, list_tail->previous_node, list_tail);
    list_tail->previous_node = newNode;
    newNode->previous_node->next_node = newNode;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// Enter your implementation here
	if( list_size == 0 )
	    throw underflow();
	Double_node* oriFront = begin();
	list_head->next_node = oriFront->next_node;
	oriFront->next_node->previous_node = list_head;
	delete(oriFront);
	list_size --;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	// Enter your implementation here
    if( list_size == 0 )
        throw underflow();
    Double_node* oriBack = rbegin();
    list_tail->previous_node = oriBack->previous_node;
    oriBack->previous_node->next_node = list_tail;
    delete(oriBack);
    list_size --;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// Enter your implementation here
	Double_node* nextPtr;
	int counter = 0;
    for( auto* ptr = begin(); ptr != end(); ){
        nextPtr = ptr -> next_node;
        if(ptr->value() == obj){
            ptr->previous_node->next_node = nextPtr;
            nextPtr->previous_node = ptr->previous_node;
            delete(ptr);
            list_size--;
            counter++;
        }
        ptr = nextPtr;
    }
	return counter;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( nv), // This assigns 'node_value' the default value of Type
previous_node( pn ),
next_node( nn )
{
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
	return node_value; // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
