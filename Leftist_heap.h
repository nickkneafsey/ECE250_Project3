

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
 *    -Alex Lui, Tewoldebrhan Hagos, Khachatur Mirijanyan
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		Leftist_heap( Leftist_heap const & );
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		Leftist_heap &operator=( Leftist_heap );

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;
        void inorder(Leftist_node<Type> *root, Type e, int &count) const;
        void inorder2(Leftist_node<Type> *root);

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}

template <typename Type>
Leftist_heap<Type>::Leftist_heap( Leftist_heap const &heap ):
root_node( nullptr ),
heap_size( 0 ) {
	// Traverses through the argument heap and pushes the entries
	// into this heap--you may use whatever traversal you want
    inorder2(heap.root_node);
}

template <typename Type>
void Leftist_heap<Type>::inorder2(Leftist_node<Type> *root) 
{
    
    if (root)
    {
        inorder2(root->left());
        const Type x=root->retrieve();
        push(x);
        inorder2(root->right());
    }
    
}

template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}



template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

template <typename Type>
Leftist_heap<Type> &Leftist_heap<Type>::operator=( Leftist_heap<Type> rhs ) {
	swap( rhs );

	return *this;
}

// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
// 
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

template <typename Type>
bool Leftist_heap<Type>::empty() const{
    return heap_size==0;
}
template <typename Type>
int Leftist_heap<Type>::size() const{
    return heap_size;
}
template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
    int npl;
    
    npl = root_node->null_path_length();
    
    return npl;
}
template <typename Type>
Type Leftist_heap<Type>::top() const{
    if (heap_size==0)
        throw underflow();
    else
        return root_node->retrieve();
}
template <typename Type>
int Leftist_heap<Type>::count( Type const &e ) const{
    
    //Leftist_node<Type> *traverser=root_node;
    int count=0;
    inorder(root_node, e, count);
    return count;
}
template <typename Type>
void Leftist_heap<Type>::inorder(Leftist_node<Type> *root, Type e, int &count) const
{
    
    if (root)
    {
        inorder(root->left(),e, count);
        if (root->retrieve()==e)
        {
            count++;
        }
        inorder(root->right(),e, count);
        
    }
    
}



template <typename Type>
void Leftist_heap<Type>::push( Type const &e ){
    if ( empty() ) {
        root_node = new Leftist_node<Type>( e );
        heap_size = 1;
        return;
    }
    
    root_node->push( new Leftist_node<Type>( e ), root_node );
    ++heap_size;
}
template <typename Type>
Type Leftist_heap<Type>::pop(){
    if ( empty() ) {
        throw underflow();
    }
    
    Type tmp = root_node->retrieve();
    
    if ( size() == 1 ) {
        heap_size = 0;
        delete root_node;
        root_node = 0;
        return tmp;
    }
    
    Leftist_node<Type> *old = root_node;
    
    if ( root_node->left() == 0 || root_node->right() == 0 ) {
        root_node = (root_node->left() != 0) ? root_node->left() : root_node->right();
    } else {
        Leftist_node<Type> *other = 0;
        
        if ( root_node->left()->retrieve() <= root_node->right()->retrieve() ) {
            other = root_node->right();
            root_node = root_node->left();
        } else {
            other = root_node->left();
            root_node = root_node->right();
        }
        
        root_node->push( other, root_node );
    }
    
    delete old;
    --heap_size;
    
    return tmp;
}
template <typename Type>
void Leftist_heap<Type>::clear(){
    if ( !empty() ) {
        root_node->clear();
        root_node = 0;
        heap_size = 0;
    }
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
