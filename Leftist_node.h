
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -Alex Lui,Tewoldebrhan Hagos,Khachatur Mirijanyan
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
#include "ece250.h"
#include "Exception.h"
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
private:
    Type element;
    Leftist_node *left_tree;
    Leftist_node *right_tree;
    int heap_null_path_length;
    
public:
    Leftist_node( Type const & );
    
    Type retrieve() const;
    bool empty() const;
    Leftist_node *left() const;
    Leftist_node *right() const;
    int count( Type const & ) const;
    int null_path_length() const;
    
    void push( Leftist_node *, Leftist_node *& );
    void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
    // does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
    return ( this == nullptr );
}

// You must implement everything
template <typename Type>
Type Leftist_node<Type>::retrieve() const
{
    return element;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const
{
    return left_tree;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const
{
    return right_tree;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const
{
//    return empty()? -1: 1+std::min(left()->null_path_length, right()->null_path_length);
    return empty()? -1:heap_null_path_length;
}
template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this )
{
    if ( new_heap == 0 ) {
        return;
    }
    
    if ( this == 0 ) {
        ptr_to_this = new_heap;
    }
    
    // If the this contains a larger element, we will swap the
    // two heaps and instead merge this heap with the argument.
    
    if ( element > new_heap->element ) {
        ptr_to_this = new_heap;
        new_heap->push( this, ptr_to_this );
        return;
    }
    
    if ( right_tree == 0 ) {
        right_tree = new_heap;
    } else {
        right_tree->push( new_heap, right_tree );
    }
    
    heap_null_path_length = std::min( 1 + left_tree->null_path_length(), 1 + right_tree->null_path_length() );
    
    if ( left_tree->null_path_length() < right_tree->null_path_length() ) {
        Leftist_node *tmp = left_tree;
        left_tree = right_tree;
        right_tree = tmp;
    }
}

template <typename Type>
void Leftist_node<Type>::clear()
{
    if (this==nullptr)
        return;
    if ( left_tree != 0 ) {
        left_tree->clear();
    }
    
    if ( right_tree != 0 ) {
        right_tree->clear();
    }
    
    delete this;
}



#endif