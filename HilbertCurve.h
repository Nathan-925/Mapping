/*
 * HilbertCurve.h
 *
 *  Created on: Jul 15, 2023
 *      Author: Nathan
 */

#ifndef PRIORI_MAPPING_HILBERTCURVE_H_
#define PRIORI_MAPPING_HILBERTCURVE_H_

#include <iterator>
#include <cmath>

namespace priori{

	std::pair<int, int> getHilbertPosition(unsigned int position, int order){
		auto out = std::make_pair(0, 0);
		for(int i = 0; i < order; i++){
			int orderSize = pow(2, i);
			int orderPos = position&3;

			switch(orderPos){
			case 2:
				out.first += orderSize;
				//no break
			case 1:
				out.second += orderSize;
				break;
			case 3:
				out.first = orderSize-1-out.first;
				out.second = 2*orderSize-1-out.second;
				//no break
			case 0:
				std::swap(out.first, out.second);
			}
			position >>= 2;
		}

		return out;
	}

	template<class T>
	struct HilbertIterator;

	template<class T>
	class HilbertCurve{
	public:
		T** matrix;
		unsigned int length, order;

		HilbertCurve(int length) : length(length){
			int size = 1;
			while(size*size < length)
				size *= 2;

			matrix = new T*[size];
			for(int i = 0; i < size; i++)
				matrix[i] = new T[size];

			order = log2(size);
		}

		HilbertCurve(T* arr, int length) : HilbertCurve(length){
			auto it = begin();
			for(int i = 0; i < length; i++){
				*it = arr[i];
				it++;
			}
		}

		~HilbertCurve(){
			int size = pow(2, order);
			for(int i = 0; i < size; i++)
				delete[] matrix[i];
			delete[] matrix;
		}

		HilbertIterator<T> begin(){
			return HilbertIterator<T>{this, 0};
		}

		HilbertIterator<T> end(){
			return HilbertIterator<T>{this, length};
		}

		T& get(int pos){
			auto coord = getHilbertPosition(pos, order);
			return matrix[coord.first][coord.second];
		}

		T& operator[](int pos){
			return get(pos);
		}
	};

	template<class T>
	struct HilbertIterator{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = int;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		HilbertCurve<T>* curve;
		unsigned int pos;

		HilbertIterator() : curve(nullptr), pos(0){}
		HilbertIterator(HilbertCurve<T>* curve, unsigned int pos) : curve(curve), pos(pos){}

		T& operator*() const{
			return curve->get(pos);
		}

		T* operator->(){
			return &curve->get(pos);
		}

		T& operator[](int n){
			return curve->get(pos+n);
		}

		bool operator==(const HilbertIterator<T> &other) const{
			return curve == other.curve && pos == other.pos;
		}

		bool operator!=(const HilbertIterator<T> &other) const{
			return curve != other.curve && pos != other.pos;
		}

		bool operator<(const HilbertIterator<T> &other) const{
			return curve == other.curve && pos < other.pos;
		}

		bool operator<=(const HilbertIterator<T>& other) const{
			return curve == other.curve && pos <= other.pos;
		}

		bool operator>(const HilbertIterator<T> &other) const{
			return curve == other.curve && pos > other.pos;
		}

		bool operator>=(const HilbertIterator<T>& other) const{
			return curve == other.curve && pos >= other.pos;
		}

		HilbertIterator<T>& operator++(){
			pos++;
			return *this;
		}

		HilbertIterator<T>& operator++(int){
			HilbertIterator<T> temp = *this;
			pos++;
			return temp;
		}

		HilbertIterator<T>& operator--(){
			pos--;
			return *this;
		}

		HilbertIterator<T>& operator--(int){
			HilbertIterator<T> out = *this;
			pos--;
			return out;
		}

		HilbertIterator<T> operator+(int n){
			HilbertIterator<T> out = *this;
			out.pos += n;
			return out;
		}

		friend HilbertIterator<T> operator+(int n, const HilbertIterator<T> it){
			HilbertIterator<T> out = it;
			out.pos += n;
			return out;
		}

		HilbertIterator<T>& operator+=(int n){
			pos += n;
			return *this;
		}

		HilbertIterator<T> operator-(int n){
			HilbertIterator<T> out = *this;
			out.pos -= n;
			return out;
		}

		friend HilbertIterator<T> operator-(int n, const HilbertIterator<T> it){
			HilbertIterator<T> out = it;
			out.pos -= n;
			return out;
		}

		HilbertIterator<T>& operator-=(int n){
			pos -= n;
			return *this;
		}
	};

}

#endif /* PRIORI_MAPPING_HILBERTCURVE_H_ */
