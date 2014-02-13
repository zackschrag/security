/*
*	Zack Schrag
*	CS356
*	2-13-2014
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef signed char schar;
typedef signed short sshort;
typedef signed int sint;
typedef signed long slong;

template <typename ELEMENT>
class Matrix {
public:
	Matrix(int w, int h);	
	~Matrix();
	Matrix(const Matrix &oldMatrix);
	Matrix& operator=(const Matrix& oldMatrix);

	void print();
	void add(ELEMENT i);
	void clear();

	/*** Potentially use these to make the correlation faster ***/
	//void pushRightCol(ELEMENT a[]);
	void pushRow(ELEMENT a[]);
	void deleteRightCol();
	void deleteLeftCol();

	ELEMENT at(int row, int col) const;
	void set(int row, int col, ELEMENT newEl) const;
	ELEMENT get(int index) const;
	ELEMENT sumWindow(ulong w, ulong h, ulong row, ulong col, ELEMENT n);
	ELEMENT meanWindow(ulong w, ulong h, ulong row, ulong col, ELEMENT n);

	int size() const;
	int width() const;
	int height() const;

//private:
	ELEMENT* data;
	ELEMENT** row_ptr;
	ELEMENT** col_ptr;
	//ELEMENT* temp_ptr;
	

	int _width;
	int _height;
	int _size;	// current number of values in matrix
};

template <typename ELEMENT>
Matrix<ELEMENT>::Matrix(int w, int h) {
	_width = w;
	_height = h;
	_size = 0;
	
	data = new ELEMENT[_width*_height];
	row_ptr = new ELEMENT*[_height];
//	col_ptr = new ELEMENT*[_width];
//	col_ptr = new Matrix<ELEMENT>(1, _height);


	ELEMENT* temp_ptr = &data[0];

	for (int i = 0; i < _height; i++) {
		row_ptr[i] = temp_ptr;
		temp_ptr += _width;
	}

	for (int i = 0; i < _width; i++) {
//		col_ptr[i] = &row_ptr[0][i];	
	}
}

template <typename ELEMENT>
Matrix<ELEMENT>::~Matrix() {
	delete [] data;
	delete [] row_ptr;
//	delete [] col_ptr;
	data = NULL;
	row_ptr = NULL;
//	col_ptr = NULL;
}

// Copies data from m into data
template <typename ELEMENT>
Matrix<ELEMENT>::Matrix(const Matrix& m) {
	_width = m.width();
	_height = m.height();
	_size = m.size();

	data = new ELEMENT[m.size()];
	for (int i = 0; i < m.size(); i++) {
		data[i] = m.get(i);
	}
}

template <typename ELEMENT>
Matrix<ELEMENT>& Matrix<ELEMENT>::operator=(const Matrix& m) { 
	_width = m.width();
	_height = m.height();
	_size = m.size();

	data = new ELEMENT[m.size()];
	for (int i = 0; i < m.size(); i++) {
		data[i] = m.get(i);
	}
	return *this;	
}

template <typename ELEMENT>
void Matrix<ELEMENT>::print() { 
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			cout << at(i,j) << " ";
		}
		cout << endl;
	}
}

template <typename ELEMENT>
void Matrix<ELEMENT>::add(ELEMENT i) {
	if ( !(_size < _width*_height && _size >= 0) ) {
		//cout << "size: " << _size << endl;
		//cout << "pos: " << 
		cout << "size: " << _size << endl;
		throw std::out_of_range("Error in Matrix class: invalid add() operation");
	}
	else {
		data[_size] = i;
		_size++;
	}
}

// a must be same height as matrix
template <typename ELEMENT>
void Matrix<ELEMENT>::pushRow(ELEMENT* a) {
	for (int i = 0; i < _height-1; i++) {
		row_ptr[i] = row_ptr[i+1];
	}
	row_ptr[_height-1] = a;
}

template <typename ELEMENT>
void Matrix<ELEMENT>::clear() {
	for (int i = 0; i < _size; i++) {
		data[i] = 0;
	}
	_size = 0;
}

template <typename ELEMENT>
ELEMENT Matrix<ELEMENT>::at(int row, int col) const {
	if ( !(row < _height && col < _width && row >= 0 && col >= 0) ) {
		throw std::out_of_range("Matrix: Out of bounds access in at()");
	}
	return row_ptr[row][col];
}

template <typename ELEMENT>
void Matrix<ELEMENT>::set(int row, int col, ELEMENT newEl) const {
	if ( !(row < _height && col < _width && row >= 0 && col >= 0) ) {
		throw std::out_of_range("Matrix: Out of bounds access in at()");
	}
	row_ptr[row][col] = newEl;
}

template <typename ELEMENT>
ELEMENT Matrix<ELEMENT>::get(int index) const {
	if (index >= _size || index < 0) {
		throw std::out_of_range("Matrix: Out of bounds access in get()");
	}
	return data[index];
}

template <typename ELEMENT>
ELEMENT Matrix<ELEMENT>::meanWindow(ulong w, ulong h, ulong row, ulong col, ELEMENT n) {
	ELEMENT sum = sumWindow(w,h,row,col,n);
	
	return sum/( ((ELEMENT) w)*((ELEMENT) h) );
}

template <typename ELEMENT>
ELEMENT Matrix<ELEMENT>::sumWindow(ulong w, ulong h, ulong row, ulong col, ELEMENT n) {
	ELEMENT sum = 0;
	for (ulong i = row; i < row+h; i++) {
		for (ulong j = col; j < col+w; j++) {
			sum += at(i,j);
		}
	}
	return sum;
}

template <typename ELEMENT>
int Matrix<ELEMENT>::size() const {return _size;}
template <typename ELEMENT>
int Matrix<ELEMENT>::width() const {return _width;}
template <typename ELEMENT>
int Matrix<ELEMENT>::height() const {return _height;}

#endif











