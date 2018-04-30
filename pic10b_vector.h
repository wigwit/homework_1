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
#include <iostream>   // std::ostream, std::cout


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
		T at(size_t index) const;
		T& operator[](size_t index);
		T operator[](size_t index) const;
		void dump_data_to(std::ostream& out) const;
		void dump_data() const;
		void push_back(T new_value);
		void pop_back();

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
	T vector::back() const {
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
	double vector::operator[](int index) const {
		return the_data[index];
	}

	void vector::dump_data_to(std::ostream& out) const {
		out << "Vector (dump): ";
		for (size_t i = 0; i < the_capacity; ++i)
			out << the_data[i] << ' ';
		out << '\n';
	}
	void vector::dump_data() const {
		dump_data_to(std::cout);
	}


	void vector::push_back(double new_value) {
		if (the_size == the_capacity)
			reserve(the_capacity + 1);     // `the_data` is reassigned

		the_data[the_size++] = new_value;
	}

	// This implementation does not shrink the vector (ever)
	void vector::pop_back() {
		if (the_size > 0)
			--the_size;
	}


	void vector::reserve(size_t new_capacity) {
		if (new_capacity > the_capacity) {
			if (new_capacity <= 2 * the_capacity)
				new_capacity = 2 * the_capacity;

			double* old_location = the_data;

			the_data = new double[new_capacity];
			the_capacity = new_capacity;

			for (size_t i = 0; i < the_size; ++i)
				the_data[i] = old_location[i];

			delete old_location;
		}
	}

} // end Pic10b namespace



  /** ************************ OTHER FUNCTIONS ************************ **/
std::ostream& operator<<(std::ostream& out, const Pic10b::vector& v) {
	for (size_t i = 0; i < v.size(); ++i)
		out << v[i] << ' ';
	return out;
}


void print_vector(const Pic10b::vector& v) {
	if (v.empty())
		std::cout << "Vector is empty\n";
	else
		std::cout << "Vector (contents): " << v << '\n';
}


#endif 
