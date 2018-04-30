#pragma once
#ifndef PIC10B_VECTOR_H
#define PIC10B_VECTOR_H
#include <iostream>
#include <string>

/*
PIC10C, Homework1
Author: Qingxia Guo
Date: 4/29/2018
*/


using std::string;

namespace Pic10b {

	template<typename T>
	class vector {
	private:
		T* the_data;
		int the_size;
		int the_capacity;

		static const int INIT_CAP = 10;


	public:
		// The big 4 
		vector();
		vector(const vector&);
		vector& operator=(const vector&);
		~vector();

		// Other members [public]
		bool empty() const;
		int size() const;
		int capacity() const;
		T front() const;
		T back() const;
		T at(int index) const;
		T& operator[](int index);
		T operator[](int index) const;
		void dump_data_to(std::ostream& out) const;
		void dump_data() const;
		void push_back(T new_value);
		void push_front(T new_value);
		void pop_back();


		//required from assignment description
		vector<T> operator*(T n); // multiply every element by the value n
		vector<T>& operator+=(const vector<T>&); // increment update

	private:
		//Other members [private]
		void reserve(int new_capacity);

	}; // end Pic10b::vector


	   /** ************************* THE BIG 4 ************************* **/
	template<typename T>
	vector<T>::vector()
		: the_data(nullptr), the_size(0), the_capacity(INIT_CAP) {

		the_data = new T[the_capacity];
	}

	template <typename T>
	vector<T>::vector(const vector& source)
		: the_data(nullptr), the_size(source.the_size),
		the_capacity(source.the_capacity) {

		the_data = new T[the_capacity];

		// Deep copy of internal array
		for (int i = 0; i < the_size; ++i) {
			the_data[i] = source.the_data[i];
		}
	}

	template <typename T>
	vector<T>& vector<T>::operator=(const vector<T>& rhs) {
		if (this != &rhs) {     // Self-assignment?
								// Release old memory and request more 
			delete[] the_data;
			the_data = new T[rhs.the_capacity];

			// Shallow copy non-pointers
			the_size = rhs.the_size;
			the_capacity = rhs.the_capacity;

			// Deep copy internal array
			for (int i = 0; i < the_size; ++i)
				the_data[i] = rhs.the_data[i];
		}
		return *this;
	}
	template<typename T>
	vector<T>::~vector() {
		delete[] the_data;
	}

	/** *********************** OTHER MEMBERS *********************** **/

	template<typename T>
	bool vector<T>::empty() const {
		return the_size == 0;
	}

	template<typename T>
	int vector<T>::size() const {
		return the_size;
	}

	template<typename T>
	int vector<T>::capacity() const {
		return the_capacity;
	}

	template<typename T>
	T vector<T>::front() const {
		return *the_data;
	}

	template<typename T>
	T vector<T>::back() const {
		return *(the_data + the_size - 1);
	}

	template<typename T>
	T vector<T>::at(int index) const {
		if (index < the_size)
			return the_data[index];
		return the_data[0];
	}

	template<typename T>
	T& vector<T>::operator[](int index) {
		return the_data[index];
	}

	template<typename T>
	T vector<T>::operator[](int index) const {
		return the_data[index];
	}

	template<typename T>
	void vector<T>::dump_data_to(std::ostream& out) const {
		out << "Vector (dump): ";
		for (int i = 0; i < the_capacity; ++i)
			out << the_data[i] << ' ';
		out << '\n';
	}

	template<typename T>
	void vector<T>::dump_data() const {
		dump_data_to(std::cout);
	}

	template<typename T>
	void vector<T>::push_back(T new_value) {
		if (the_size == the_capacity)
			reserve(the_capacity + 1);     // `the_data` is reassigned

		the_data[the_size++] = new_value;
	}
// push front feature added
        template <typename T>
	void vector<T>::push_front(T new_value){
	if (the_size==the_capacity)
		reserve(the_capacity+1);
	the_size++;
	for(int i=the_size-1;i>0;i--)
		the_data[i]=i;

	the_data[0]=new_value;
	}


	// This implementation does not shrink the vector (ever)

	template<typename T>
	void vector<T>::pop_back() {
		if (the_size > 0)
			--the_size;
	}

	template<typename T>
	void vector<T>::reserve(int new_capacity) {
		if (new_capacity > the_capacity) {
			if (new_capacity <= 2 * the_capacity)
				new_capacity = 2 * the_capacity;

			T* old_location = the_data;

			the_data = new T[new_capacity];
			the_capacity = new_capacity;

			for (int i = 0; i < the_size; ++i)
				the_data[i] = old_location[i];

			delete old_location;
		}
	}

	//for vector<int>/<double> * int/double
	template<typename T>
	vector<T> vector<T>::operator*(T n)
	{
		for (int i = 0; i <the_size; ++i)
			the_data[i] *= n;
		return *this;
	}

	//specifically for string calculation
	vector<string> vector<string>::operator*(string s)
	{
		for (int i = 0; i <the_size; ++i)
			the_data[i] += " " + s;

		return *this;
	}

	//for incrementation
	template <typename T>
	vector<T>& vector<T>::operator+=(const vector<T>&v)
	{
		if (the_size == v.size()) //check if the size matches
		{
			for (int i = 0; i < v.size(); ++i)
				the_data[i] += v[i];


			return *this;
		}
	}

} // end Pic10b namespace



  /** ************************ OTHER FUNCTIONS ************************ **/

template<typename T>
std::ostream& operator<<(std::ostream& out, const Pic10b::vector<T>& v) {
	for (size_t i = 0; i < v.size(); ++i)
		out << v[i] << ' ';
	return out;
}

template<typename T>
void print_vector(const Pic10b::vector<T>& v) {
	if (v.empty())
		std::cout << "Vector is empty\n";
	else
		std::cout << "Vector (contents): " << v << '\n';
}

//required from assignment description
//dot product for int and double
template<typename T>
T operator*(const Pic10b::vector<T>&v1, const Pic10b::vector<T>&v2)
{
	T sum = 0;
	if (v1.size() == v2.size())
	{
		for (int i = 0; i < v1.size(); ++i)
			sum += v1[i] * v2[i];
		return sum;
	}
}

//vector + vector
// two copy constructors called
template <typename T>
Pic10b::vector<T> operator+(const Pic10b::vector<T>& v1, Pic10b::vector<T>v2)// one of them pass by val
{
	v2 += v1;
	return v2; // will not affect the actual since v2 is passed by value
}

template <typename T>
Pic10b::vector<T> operator*(T n, Pic10b::vector<T>& v)
{
	return v * n;// output will be the same as v*n
}

Pic10b::vector<string> operator*(string s, Pic10b::vector<string> v1)
{
	for (int i = 0; i < v1.size(); ++i)
	{
		v1[i] = s + " " + v1[i];
	}
	return v1;// returning v1 wont affect actual object v1 since this is passed by val
}



//boolean operator

template<typename T>
//for comparing the length of two vectors
//wont apply to string
bool operator<=(const Pic10b::vector<T>&v1, const Pic10b::vector<T>&v2)
{
	return (sqrt(v1*v1) <= sqrt(v2*v2));
}

template<typename T>
bool operator<(const Pic10b::vector<T>&v1, const Pic10b::vector<T>&v2)
{
	return (sqrt(v1*v1) <sqrt(v2*v2));
}

template<typename T>
bool operator>(const Pic10b::vector<T>&v1, const Pic10b::vector<T>&v2)
{
	return(!(v1 <= v2));
}

template<typename T>
bool operator>=(const Pic10b::vector<T>&v1, const Pic10b::vector<T>&v2)
{
	return(!(v1 < v2));
}

// comparing if the two vectors are identical
//will apply to string type
template<typename T>
bool operator==(const Pic10b::vector<T>&v1, const Pic10b::vector<T>&v2)
{
	if (v1.size() == v2.size())
	{
		for (int i = 0; i < v1.size(); ++i)
		{
			if (v1[i] == v2[i])
				continue;
			else
				return false;
		}
		return true;
	}
	return false;
}

template<typename T>
bool operator!=(const Pic10b::vector<T>& v1, const Pic10b::vector<T>&v2)
{
	return (!(v1 == v2));
}



#endif 
