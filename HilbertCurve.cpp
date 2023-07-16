/*
 * HilbertCurve.c
 *
 *  Created on: Jul 15, 2023
 *      Author: Nathan
 */
#include <cmath>

#include "HilbertCurve.h"

using namespace std;

namespace priori{

	template<class T>
	HilbertCurve<T>::HilbertCurve(int length) : length(length){
		int size = 1;
		while(size*size < length)
			size *= 2;

		matrix = new T*[size];
		for(int i = 0; i < size; i++)
			matrix[i] = new T[size];

		order = log2(size);
	}

	template<class T>
	HilbertCurve<T>::HilbertCurve(T* arr, int length) : HilbertCurve(length){
		auto it = begin();
		for(int i = 0; i < length; i++)
			*it++ = arr[i];
	}

	template<class T>
	HilbertCurve<T>::~HilbertCurve(){
		int size = pow(2, order);
		for(int i = 0; i < size; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	template<class T>
	HilbertIterator<T> HilbertCurve<T>::begin(){
		return HilbertIterator<T>{this, 0};
	}

	template<class T>
	HilbertIterator<T> HilbertCurve<T>::end(){
		return HilbertIterator<T>{this, length};
	}

	std::pair<int, int> getHilbertPosition(unsigned int position, int order){
		auto out = make_pair(0, 0);
		while(order > 0){
			int orderSize = pow(2, order-1);
			int orderPos = position&3;

			switch(orderPos){
			case 2:
				out.first += orderSize;
				//no break
			case 1:
				out.second += orderSize;
				break;
			case 0:
				swap(orderPos, orderSize);
			}

			order--;
			position >>= 2;
		}

		return out;
	}

	template<class T>
	T& HilbertCurve<T>::get(int pos){

	}

	template<class T>
	T& HilbertCurve<T>::operator[](int pos){
		return get(pos);
	}

	template<class T>
	HilbertIterator<T>::HilbertIterator() : curve(nullptr), pos(0){}

	template<class T>
	HilbertIterator<T>::HilbertIterator(HilbertCurve<T>* curve, unsigned int pos) : curve(curve), pos(pos){}

	template<class T>
	T& HilbertIterator<T>::operator*() const{
		return curve->get(pos);
	}

	template<class T>
	T* HilbertIterator<T>::operator->(){
		return &curve->get(pos);
	}

	template<class T>
	T& HilbertIterator<T>::operator[](int n){
		return curve->get(pos+n);
	}

	template<class T>
	HilbertIterator<T>& HilbertIterator<T>::operator++(){
		pos++;
		return *this;
	}

	template<class T>
	HilbertIterator<T>& HilbertIterator<T>::operator++(int){
		HilbertIterator<T> temp = *this;
		pos++;
		return temp;
	}

	template<class T>
	HilbertIterator<T>& HilbertIterator<T>::operator--(){
		pos--;
		return *this;
	}

	template<class T>
	HilbertIterator<T>& HilbertIterator<T>::operator--(int){
		HilbertIterator<T> out = *this;
		pos--;
		return out;
	}

	template<class T>
	HilbertIterator<T> HilbertIterator<T>::operator+(int n){
		HilbertIterator<T> out = *this;
		out.pos += n;
		return out;
	}

	template<class T>
	HilbertIterator<T> operator+(int n, const HilbertIterator<T> it){
		HilbertIterator<T> out = it;
		out.pos += n;
		return out;
	}

	template<class T>
	HilbertIterator<T>& HilbertIterator<T>::operator+=(int n){
		pos += n;
		return *this;
	}

	template<class T>
	HilbertIterator<T> HilbertIterator<T>::operator-(int n){
		HilbertIterator<T> out = *this;
		out.pos -= n;
		return out;
	}

	template<class T>
	HilbertIterator<T> operator-(int n, const HilbertIterator<T> it){
		HilbertIterator<T> out = it;
		out.pos -= n;
		return out;
	}

	template<class T>
	HilbertIterator<T>& HilbertIterator<T>::operator-=(int n){
		pos -= n;
		return *this;
	}

}
