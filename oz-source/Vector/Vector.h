//
//  array.h
//  ModelVis
//
//  Created by Murphy M Stein on 10/17/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#ifndef __OZ__VECTOR_H
#define __OZ__VECTOR_H

#include <iostream>
#include <sstream>

using namespace std;

typedef uint32_t idx_t;	

template<typename T>
class Vector {

public:

        Vector(std::initializer_list<T> l) {
                _capacity = l.size();
                _size = l.size();
                _data = new T[_size];
                for (int i = 0; i < _size; i++) {
                        _data[i] = l.begin()[i];
                }
        }

        Vector(char* src, size_t num_elements) {
                _capacity = num_elements;
                _size = num_elements;
                _data = reinterpret_cast<T*>(src);
                _owns_memory = true;
        }

        Vector(size_t n=0, size_t k=1) {
                if (k < n) {
                        k = n;
                }
                _capacity = k;
                _size = n;
                _data = new T[_capacity];
                _owns_memory = true;
        }

        Vector(const Vector& copyFrom) {
                _size = copyFrom.size();
                if (_size == 0) {
                        _capacity = 1;
                } else {
                        _capacity = _size;
                }
                _data = new T[_capacity];
                std::copy(copyFrom.begin(), copyFrom.end(), _data);
                _owns_memory = true;
        }

        ~Vector() {
                if (_owns_memory) {
                        delete [] _data;
                }
        };

        size_t capacity() const { return _capacity; };
        size_t size() const { return _size; };

        size_t sizeInBytes() const { return _size * sizeof(T); };

        T& operator[](const size_t i) {
                return _data[i];
        }

	const T& operator[](const size_t i) const {
		return _data[i];
	}

	void push_back(T el) {
		if (_size == _capacity) {
			recapacity(_capacity * 2 + 1);
		}
		at(_size) = el;
		_size = _size + 1;
	}

	void appendCopyFrom(Vector<T> other) {
		idx_t orig_size = size();
		idx_t other_size = other.size();
		resize(orig_size + other_size);
		for (size_t i = orig_size, j = 0; i < size(); i++, j++) {
			_data[i] = other[j];
		}
	}

	void resize(size_t new_size) {
		if (_capacity < new_size ) {
			T* new_data = new T[new_size];
			std::copy(_data, _data + size(), new_data);
			delete [] _data;
			_data = new_data;
			_capacity = new_size;
		}
		_size = new_size;
	}

	void recapacity(size_t new_capacity) {
		T* new_data = new T[new_capacity];
		std::copy(_data, _data + size(), new_data);
		delete [] _data;
		_data = new_data;
		_capacity = new_capacity;
	}

	void compactify() {
		recapacity(size());
	}

	void fill(T val = 0) {
		for (int i = 0; i < _size; i++) {
			_data[i] = val;
		}
	}

	T* begin() const { return _data; }
	T* end() const { return _data + _size; }

	void print() {
		for (int i = 0; i < _size; i++) {
			cout << _data[i] << " ";
		}
		cout << endl;
	}

	T& at(size_t i) {
		return _data[i];
	}

	Vector& duplicate(T* src, size_t num) {
		resize(num);
		memcpy(raw(), reinterpret_cast<T*>(src), sizeInBytes());
	}

	Vector& operator=(const Vector &rhs) {

		// Only do assignment if RHS is a different object from this.
		if (this != &rhs) {
			delete [] _data;
			_capacity = rhs.size();
			_size = _capacity;
			_data = new T[_capacity];
			std::copy(rhs.begin(), rhs.end(), _data);
		}

		return *this;
	}

	char* raw() {
		return reinterpret_cast<char*>(_data);
	}

	T* underlying() {
		return _data;
	}

	Vector& become(char* raw, size_t num_elements) {
		if (_owns_memory) {
			delete [] _data;
		}
		_data = reinterpret_cast<T*>(raw);
		_size = num_elements;
		_capacity = num_elements;
		_owns_memory = true;
	}

	Vector& becomeView(char* raw, size_t num_elements) {
		if (_owns_memory) {
			delete [] _data;
		}
		_data = reinterpret_cast<T*>(raw);
		_size = num_elements;
		_capacity = num_elements;
		_owns_memory = false;
	}

	//========================================================================
	// STATIC METHODS ////////////////////////////////////////////////////////
	//========================================================================

	static Vector range(T from, T upto_and_excl, T count_by = 1) {
		Vector a(upto_and_excl - from);
		T* ptr = a.begin();
		T val = from;
		while (ptr != a.end()) {
			*ptr = val;
			val += count_by;
			ptr++;
		}
		return a;
	}

	static Vector& wrap(char* src, size_t num_elements) {
		Vector a = new Vector(src, num_elements);
		return a;
	}
	//========================================================================

	//========================================================================
	// FRIEND METHODS ////////////////////////////////////////////////////////
	//========================================================================
	friend ostream& operator<< (ostream& os, const Vector& d) {
		stringstream ss;
		for (size_t i = 0; i < d.size(); i++) {
			ss << d[i] << ", ";
		}
		return os << ss.str();
	}


protected:
        size_t _size;
        size_t _capacity;
        bool _owns_memory;
        T* _data;

};

#endif /* defined(__ModelVis__array__) */
