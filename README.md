# homework_1

Author: Qingxia Guo


Goal: 
The Goal of this project is to formulate a vector class that would be used similarly to <vector> in standard library.

Introduction:

The PIC10b namespace:

By writing the declaration and definition within the namespace Pic10b, users can call the Pic10b::vector<type> in their main function, as opposed to std::vector<type>. 

An example might look like:

namespace Pic10b {

    template <typename T>
    class vector {
    
  definiation and declartion of the vectors...
    
    };


}


Variable Description

the_data: a pointer that point to the location of firts element in vector
the_size: the size of the vector
the_capacity: the capacity of vector
INIT CAP: a constant capacity used to initialize the vector capacity


Dynamic Memory Allocation: 

Since this class takes advantage of heap memory, The copy constructor, assignment operator and destructor should be specified in order to avoid shallow copying. 

the example might look like :

template <typename T>
vecotr<T>::vector (const vector<T> & v)
{

     first ask for new memory location
     for (....)
     *(the new memory loaction)=*(the old memory location);

     the_capacity=v.the_capacity;
     the_size=v.the_size;
}
Similarly to assignment operator.







Member Functions:
All the member function are similar to standard vector class. However, there are a few different

front():
return the first value in vector.

back():
return the last value in vector.

at(int index):
return the value at the index position.

dump_data() const:
store the value that deleted or changed.

push_front(T new_value): 
adding the new_value to the front of the vector.




Special Requirement from Assignment Description:


operator * :
Performs the dot product for int and double types.
Performs different for string.



operator <<:
prints out each element in vectors.


boolean operator:
compares the length of int and double vectors.
cannot be called for string vectors.




