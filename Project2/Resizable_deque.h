/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

template<typename Type>
class Resizable_deque {
    public:
        Resizable_deque(int = 3);
        Resizable_deque(Resizable_deque const &);
        Resizable_deque(Resizable_deque &&);
        ~Resizable_deque();

        Type front() const;
        Type back() const;
        int size() const;
        bool empty() const;
        int capacity() const;

        void swap(Resizable_deque &);
        Resizable_deque &operator=(Resizable_deque const &);
        Resizable_deque &operator=(Resizable_deque &&);
        void push_front(Type const &);
        void push_back(Type const &);
        void pop_front();
        void pop_back();
        void clear();

    private:
        // Your member variables
        int initial_array_capacity;
        int array_capacity;
        Type *array;
        int ifront;
        int iback;
        int deque_size;
        // Any private member functions
        //   - helper functions for resizing your array?
        void double_array_size();
        void half_array_size();
        void copy_ori_array(int);


        // Friends

        template<typename T>
        friend std::ostream &operator<<(std::ostream &, Resizable_deque<T> const &);


};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template<typename Type>
Resizable_deque<Type>::Resizable_deque(int n)
// Your initalization list
{
    // Enter your implementation here
    initial_array_capacity = std::max(3, n);
    array_capacity = initial_array_capacity;
    array = new Type[initial_array_capacity];
    ifront = -1;
    iback = -1;
    deque_size = 0;
}

// Copy Constructor
template<typename Type>
Resizable_deque<Type>::Resizable_deque(Resizable_deque const &deque)
// Your initalization list
{
    // Enter your implementation here
    initial_array_capacity = deque.initial_array_capacity;
    array_capacity = deque.array_capacity;
    deque_size = deque.deque_size;
    ifront = deque.ifront;
    iback = deque.iback;
    array = new Type[array_capacity];
    for (int i = 0; i < array_capacity; i++) {
        array[i] = deque.array[i];
    }

}

// Move Constructor
template<typename Type>
Resizable_deque<Type>::Resizable_deque(Resizable_deque &&deque)
// Your initalization list
{
    // Enter your implementation here
    array = new Type[array_capacity];
    swap(deque);
    delete(deque);
}

// Destructor
template<typename Type>
Resizable_deque<Type>::~Resizable_deque() {
    // Enter your implementation here
    delete[](array);
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template<typename Type>
int Resizable_deque<Type>::size() const {
    // Enter your implementation here
    return deque_size;
}

template<typename Type>
int Resizable_deque<Type>::capacity() const {
    // Enter your implementation here
    return array_capacity;
}

template<typename Type>
bool Resizable_deque<Type>::empty() const {
    // Enter your implementation here
    return deque_size == 0;
}

template<typename Type>
Type Resizable_deque<Type>::front() const {
    // Enter your implementation here
    if(deque_size == 0)
        throw underflow();
    return array[ifront];
}

template<typename Type>
Type Resizable_deque<Type>::back() const {
    // Enter your implementation here
    if(deque_size == 0)
        throw underflow();
    return array[iback];
}

template<typename Type>
void Resizable_deque<Type>::swap(Resizable_deque<Type> &deque) {
    // Swap the member variables
    //     std::swap( variable, deque.variable );

    // Enter your implementation here

    std::swap(initial_array_capacity, deque.initial_array_capacity);
    std::swap(array_capacity, deque.array_capacity);
    std::swap(array, deque.array);
    std::swap(ifront, deque.ifront);
    std::swap(iback, deque.iback);
    std::swap(deque_size, deque.deque_size);
}

template<typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=(Resizable_deque<Type> const &rhs) {
    // This is done for you...
    Resizable_deque<Type> copy(rhs);
    swap(copy);
    return *this;
}

template<typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=(Resizable_deque<Type> &&rhs) {
    // This is done for you...
    swap(rhs);
    return *this;
}

template<typename Type>
void Resizable_deque<Type>::push_front(Type const &obj) {
    // Enter your implementation here
    if (deque_size == array_capacity)
        double_array_size();

    // if ifront is already on 0th, move it to the end. else, ifront move forward
    ifront--;
    if (ifront < 0)
        ifront = array_capacity - 1;

    // if the deque is empty, initialize ifront and iback
    if (empty())
        ifront = iback = 0;

    array[ifront] = obj;

    deque_size++;

}

template<typename Type>
void Resizable_deque<Type>::push_back(Type const &obj) {
    // Enter your implementation here
    if (deque_size == array_capacity)
        double_array_size();

    // if ifront is already on 0th, move it to the end. else, ifront move forward
    iback++;
    if (iback == array_capacity)
        iback = 0;

    // if the deque is empty, initialize ifront and iback
    if (empty())
        ifront = iback = 0;

    array[iback] = obj;

    deque_size++;
}

template<typename Type>
void Resizable_deque<Type>::pop_front() {
    // Enter your implementation here
    if(deque_size == 0)
        throw underflow();
    if( deque_size == 1){
        ifront = iback = -1;
        deque_size = 0;
        return;
    }

    ifront++;
    if (ifront == array_capacity)
        ifront = 0;
    deque_size--;
    if (deque_size <= 0.25 * array_capacity || array_capacity > initial_array_capacity)
        half_array_size();
}

template<typename Type>
void Resizable_deque<Type>::pop_back() {
    // Enter your implementation here
    if(deque_size == 0)
        throw underflow();
    if(deque_size == 1){
        ifront = iback = -1;
        deque_size = 0;
        return;
    }
    iback --;
    if(iback <0)
        iback = array_capacity - 1;
    deque_size --;
    if (deque_size <= 0.25 * array_capacity || array_capacity > initial_array_capacity)
        half_array_size();
}

template<typename Type>
void Resizable_deque<Type>::clear() {
    // Enter your implementation here
    delete[](array);
    array = new Type[initial_array_capacity];
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here

template<typename Type>
void Resizable_deque<Type>::copy_ori_array(int new_array_capacity) {

    Type *new_array = new Type[new_array_capacity];

    int end = (ifront > iback) ? array_capacity : iback + 1;
    for (int i = ifront; i < end; i++)
        *(new_array++) = array[i];


    if (ifront > iback)
        for (int i = 0; i <= iback; i++)
            *(new_array++) = array[i];

    ifront = 0;
    iback = deque_size - 1;

    new_array -= deque_size;
    array_capacity = new_array_capacity;
    std::swap(array, new_array);
//    new_array = nullptr;
    delete[](new_array);
}


template<typename Type>
void Resizable_deque<Type>::double_array_size() {
    std::cout << "double array!" << std::endl;
    copy_ori_array(array_capacity * 2);
}


template<typename Type>
void Resizable_deque<Type>::half_array_size() {
    std::cout << "half array!" << std::endl;
    copy_ori_array(array_capacity / 2);
}



/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template<typename T>
std::ostream &operator<<(std::ostream &out, Resizable_deque<T> const &list) {
    if(list.empty())
        return out;

    int end = (list.ifront > list.iback) ? list.array_capacity : list.iback + 1;

    for (int i = list.ifront; i < end; i++)
        out << list.array[i] << "_f ";

    if (list.ifront > list.iback) {
        for (int i = 0; i <= list.iback; i++)
            out << list.array[i] << "_b ";
    }

    return out;
}


//int main() {
//    Resizable_deque<int> d;
//    d.push_front(1);
//    d.push_front(2);
//    d.push_front(3);
//    d.push_front(4);
//    Resizable_deque<int> dd;
//    dd = d;
//    std::cout<<d.front();
//    return 0;
//}


#endif
